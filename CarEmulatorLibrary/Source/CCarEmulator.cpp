
#include "CCarEmulator.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCarEmulator::CCarEmulator(CCar* pVehicle)
{
    _TorqueTable << CInterpolator<double>::InterpolatorValue(0, 0.0);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(5, 0.4);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(10, 0.6);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(16, 1.0);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(45, 2.0);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(75, 2.5);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(103, 1.8);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(133, 0.4);
    _TorqueTable << CInterpolator<double>::InterpolatorValue(150, 0.0);
}

CCarEmulator::~CCarEmulator()
{
}

void CCarEmulator::Process(double DeltaTimeMillis)
{
    // Get parameters from settings and sensors
    double DeltaTimeSeconds = CUtils::MillisToSeconds(DeltaTimeMillis);
    double EngineRPS = CUtils::RPMToRPS(_Vehicle.Sensors().CurrentRPM().Value());
    double IdleEngineRPS = CUtils::RPMToRPS(_Vehicle.EngineSettings().IdleRPM());
    double BreakDownRPS = CUtils::RPMToRPS(_Vehicle.EngineSettings().BreakDownRPM());
    double CarSpeedMS = CUtils::KMHToMS(_Vehicle.Sensors().CurrentSpeedKMH().Value());
    double ClutchRange = _Vehicle.EngineSettings().ClutchFullEngaged() - _Vehicle.EngineSettings().ClutchContact();
    double GearRatio = _Vehicle.GearBox().CurrentRatio();
    double CurrentEngineTempC = _Vehicle.Sensors().CurrentEngineTempC().Value();
    double MaxTemperatureC = _Vehicle.EngineSettings().MaxTemperatureC();
    double BreakDownTemperatureC = _Vehicle.EngineSettings().BreakDownTemperatureC();
    double FuelLevelL = _Vehicle.Sensors().CurrentFuelLevelL().Value();

    // Compute the actual clutch level using contact point and full engage point
    _ClutchLevel.setValue((_Vehicle.ClutchPedal().Value() - _Vehicle.EngineSettings().ClutchContact()) / ClutchRange);

    // Compute fuel consumption
    double FuelGasFactor = _Vehicle.GasPedal().Value();
    if (FuelGasFactor < 0.05) FuelGasFactor = 0.05;

    // Compute torque transfer factor
    double TorqueTransferFactor = _ClutchLevel.Value();
    if (TorqueTransferFactor > 1.0) TorqueTransferFactor = 1.0;
    if (GearRatio == 0.0) TorqueTransferFactor = 0.0;

    // Bring car speed value up to RPM
    CarSpeedMS *= CEngineSettings::SpeedMSToRPS;

    // Compute wheel circumference
    double WheelCircM = 2.0 * CEngineSettings::WheelRadiusM * M_PI;
    _WheelRPS = CarSpeedMS / WheelCircM;

    // Compute raw force produced by engine
    double RawEngineTorqueRPS = EngineRPS * FuelGasFactor;

    // Slow down the engine RPS using limit RPM
    RawEngineTorqueRPS = (RawEngineTorqueRPS * ((BreakDownRPS - RawEngineTorqueRPS) / BreakDownRPS)) * 4;

    double EngineDrag = ((BreakDownRPS - EngineRPS) / BreakDownRPS);

    // Apply the engine drag (reaching limit RPM) to the engine RPM
    EngineRPS += (((RawEngineTorqueRPS * (1 - TorqueTransferFactor)) * EngineDrag) * DeltaTimeSeconds) * 1.5;

    // Bring back engine to minimum RPS according to torque transfer factor and fuel flow
    double IdlePower = (EngineRPS - IdleEngineRPS) / (IdleEngineRPS / 15.0);

    EngineRPS -= ((IdlePower * (1.0 - TorqueTransferFactor) * (1.0 - FuelGasFactor)) * DeltaTimeSeconds) * 1.5;

    // Compute the force from the wheels applied to the engine by the clutch
    double WheelRPSToEngine = 0.0;

    if (GearRatio != 0.0)
    {
        WheelRPSToEngine = ((_WheelRPS - (EngineRPS / GearRatio)) * TorqueTransferFactor) * 8.0;
    }

    // Apply the wheel force to the engine
    EngineRPS += WheelRPSToEngine * DeltaTimeSeconds;

    if (EngineRPS < 0) EngineRPS = 0;
    if (EngineRPS > BreakDownRPS) EngineRPS = BreakDownRPS;

    // Compute the engine power
    _EnginePowerRPS = (_TorqueTable.getValue(EngineRPS) * 8) * FuelGasFactor;

    double CarSpeedDivider = CarSpeedMS * 0.05;
    if (CarSpeedDivider < 1.0) CarSpeedDivider = 1.0;

    // Add power to engine when starting up
    _EnginePowerRPS += (EngineRPS * (1.0 - TorqueTransferFactor)) / CarSpeedDivider;

    // Compute engine break
    // TODO

    // Compute acceleration
    double AccelRPS = _EnginePowerRPS * TorqueTransferFactor;

    // Compute car speed
    _WheelRPS += AccelRPS * DeltaTimeSeconds;

    // Check speed limits
    if (_WheelRPS < 0) _WheelRPS = 0;

    CarSpeedMS = _WheelRPS * WheelCircM;

    // Compute ground drag
    double GroundDrag = CarSpeedMS / -5000.0;
    if (GroundDrag > -2) GroundDrag = -2;

    // Compute air drag
    double AirDrag = (CarSpeedMS * CarSpeedMS) / -5000.0;
    if (AirDrag > -2) AirDrag = -2;

    // Compute total drag
    double TotalDrag = GroundDrag + AirDrag;

    // Add drags to speed
    CarSpeedMS += (TotalDrag * DeltaTimeSeconds);

    // Add break to speed
    CarSpeedMS += (_Vehicle.BreakPedal().Value() * -60) * DeltaTimeSeconds;

    // Compute wheel RPS
    _WheelRPS = (CarSpeedMS / WheelCircM) / CEngineSettings::SpeedMSToRPS;

    // Compute fuel consumption
    double FuelCons = (((TotalDrag * -1.0) + AccelRPS) * CEngineSettings::RPSToL) * FuelGasFactor;

    FuelLevelL -= FuelCons * DeltaTimeSeconds;
    if (FuelLevelL < 0.0) FuelLevelL = 0.0;

    // Compute engine temperature
    double TemperatureChangeCS = ((EngineRPS / BreakDownRPS) * (EngineRPS / BreakDownRPS)) * 5;
    TemperatureChangeCS *= (BreakDownTemperatureC - CurrentEngineTempC) / BreakDownTemperatureC;

    CurrentEngineTempC += TemperatureChangeCS * DeltaTimeSeconds;

    // Compute engine cooling
    double EngineTemperatureCoolingCS = (CurrentEngineTempC - MaxTemperatureC) * 0.01;
    if (EngineTemperatureCoolingCS < 0.0) EngineTemperatureCoolingCS = 0.0;
    EngineTemperatureCoolingCS *= -1.0;

    CurrentEngineTempC += EngineTemperatureCoolingCS * DeltaTimeSeconds;

    // Compute natural temperature loss
    if (TemperatureChangeCS < 0.01)
    {
        CurrentEngineTempC -= 0.05 * DeltaTimeSeconds;
    }

    // Bring car speed value down from RPM
    CarSpeedMS /= CEngineSettings::SpeedMSToRPS;

    // Assign new engine RPM
    _Vehicle.Sensors().CurrentRPM().setValue(CUtils::RPSToRPM(EngineRPS));

    // Assign new speed
    _Vehicle.Sensors().CurrentSpeedKMH().setValue(CUtils::MSToKMH(CarSpeedMS));

    // Assign new engine temperature
    _Vehicle.Sensors().CurrentEngineTempC().setValue(CurrentEngineTempC);

    // Assign new fuel level
    _Vehicle.Sensors().CurrentFuelLevelL().setValue(FuelLevelL);
}
