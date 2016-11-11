
#include "CCarEmulator.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCarEmulator::CCarEmulator()
{
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(0, 0.0);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(5, 0.4);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(10, 0.6);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(16, 1.0);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(45, 2.0);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(75, 2.5);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(103, 1.8);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(133, 0.4);
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(150, 0.0);
}

CCarEmulator::~CCarEmulator()
{
}

void CCarEmulator::process(double dDeltaTimeMillis)
{
    m_cVehicle.process(dDeltaTimeMillis);

    // Get parameters from settings and sensors
    double dDeltaTimeSeconds = CUtils::MillisToSeconds(dDeltaTimeMillis);
    double dEngineRPS = CUtils::RPMToRPS(m_cVehicle.sensors().currentRPM().value());
    double dIdleEngineRPS = CUtils::RPMToRPS(m_cVehicle.engineSettings().idleRPM());
    double dBreakDownRPS = CUtils::RPMToRPS(m_cVehicle.engineSettings().breakDownRPM());
    double dCarSpeedMS = CUtils::KMHToMS(m_cVehicle.sensors().currentSpeedKMH().value());
    double dClutchRange = m_cVehicle.engineSettings().clutchFullEngaged() - m_cVehicle.engineSettings().clutchContact();
    double dGearRatio = m_cVehicle.gearBox().currentRatio();
    double dCurrentEngineTempC = m_cVehicle.sensors().currentEngineTempC().value();
    double dMaxTemperatureC = m_cVehicle.engineSettings().maxTemperatureC();
    double dBreakDownTemperatureC = m_cVehicle.engineSettings().breakDownTemperatureC();
    double dFuelLevelL = m_cVehicle.sensors().currentFuelLevelL().value();

    // Compute the actual clutch level using contact point and full engage point
    m_iClutchLevel.setValue((m_cVehicle.clutchPedal().Value() - m_cVehicle.engineSettings().clutchContact()) / dClutchRange);

    // Compute fuel consumption
    double dFuelGasFactor = m_cVehicle.gasPedal().Value();
    if (dFuelGasFactor < 0.05) dFuelGasFactor = 0.05;

    // Compute torque transfer factor
    double dTorqueTransferFactor = m_iClutchLevel.Value();
    if (dTorqueTransferFactor > 1.0) dTorqueTransferFactor = 1.0;
    if (dGearRatio == 0.0) dTorqueTransferFactor = 0.0;

    // Bring car speed value up to RPM
    dCarSpeedMS *= CEngineSettings::SpeedMSToRPS;

    // Compute wheel circumference
    double dWheelCircM = 2.0 * CEngineSettings::WheelRadiusM * M_PI;
    m_dWheelRPS = dCarSpeedMS / dWheelCircM;

    // Compute raw force produced by engine
    double dRawEngineTorqueRPS = dEngineRPS * dFuelGasFactor;

    // Slow down the engine RPS using limit RPM
    dRawEngineTorqueRPS = (dRawEngineTorqueRPS * ((dBreakDownRPS - dRawEngineTorqueRPS) / dBreakDownRPS)) * 4;

    double dEngineDrag = ((dBreakDownRPS - dEngineRPS) / dBreakDownRPS);

    // Apply the engine drag (reaching limit RPM) to the engine RPM
    dEngineRPS += (((dRawEngineTorqueRPS * (1 - dTorqueTransferFactor)) * dEngineDrag) * dDeltaTimeSeconds) * 1.5;

    // Bring back engine to minimum RPS according to torque transfer factor and fuel flow
    double dIdlePower = (dEngineRPS - dIdleEngineRPS) / (dIdleEngineRPS / 15.0);

    dEngineRPS -= ((dIdlePower * (1.0 - dTorqueTransferFactor) * (1.0 - dFuelGasFactor)) * dDeltaTimeSeconds) * 1.5;

    // Compute the force from the wheels applied to the engine by the clutch
    double dWheelRPSToEngine = 0.0;

    if (dGearRatio != 0.0)
    {
        dWheelRPSToEngine = ((m_dWheelRPS - (dEngineRPS / dGearRatio)) * dTorqueTransferFactor) * 8.0;
    }

    // Apply the wheel force to the engine
    dEngineRPS += dWheelRPSToEngine * dDeltaTimeSeconds;

    if (dEngineRPS < 0) dEngineRPS = 0;
    if (dEngineRPS > dBreakDownRPS) dEngineRPS = dBreakDownRPS;

    // Compute the engine power
    m_dEnginePowerRPS = (m_iTorqueTable.getValue(dEngineRPS) * 8) * dFuelGasFactor;

    double dCarSpeedDivider = dCarSpeedMS * 0.05;
    if (dCarSpeedDivider < 1.0) dCarSpeedDivider = 1.0;

    // Add power to engine when starting up
    m_dEnginePowerRPS += (dEngineRPS * (1.0 - dTorqueTransferFactor)) / dCarSpeedDivider;

    // Compute engine break
    // TODO

    // Compute acceleration
    double dAccelRPS = m_dEnginePowerRPS * dTorqueTransferFactor;

    // Compute car speed
    m_dWheelRPS += dAccelRPS * dDeltaTimeSeconds;

    // Check speed limits
    if (m_dWheelRPS < 0) m_dWheelRPS = 0;

    dCarSpeedMS = m_dWheelRPS * dWheelCircM;

    // Compute ground drag
    double dGroundDrag = dCarSpeedMS / -5000.0;
    if (dGroundDrag > -2) dGroundDrag = -2;

    // Compute air drag
    double dAirDrag = (dCarSpeedMS * dCarSpeedMS) / -5000.0;
    if (dAirDrag > -2) dAirDrag = -2;

    // Compute total drag
    double dTotalDrag = dGroundDrag + dAirDrag;

    // Add drags to speed
    dCarSpeedMS += (dTotalDrag * dDeltaTimeSeconds);

    // Add break to speed
    dCarSpeedMS += (m_cVehicle.breakPedal().Value() * -60) * dDeltaTimeSeconds;

    // Compute wheel RPS
    m_dWheelRPS = (dCarSpeedMS / dWheelCircM) / CEngineSettings::SpeedMSToRPS;

    // Compute fuel consumption
    double dFuelCons = (((dTotalDrag * -1.0) + dAccelRPS) * CEngineSettings::RPSToL) * dFuelGasFactor;

    dFuelLevelL -= dFuelCons * dDeltaTimeSeconds;
    if (dFuelLevelL < 0.0) dFuelLevelL = 0.0;

    // Compute engine temperature
    double dTemperatureChangeCS = ((dEngineRPS / dBreakDownRPS) * (dEngineRPS / dBreakDownRPS)) * 5;
    dTemperatureChangeCS *= (dBreakDownTemperatureC - dCurrentEngineTempC) / dBreakDownTemperatureC;

    dCurrentEngineTempC += dTemperatureChangeCS * dDeltaTimeSeconds;

    // Compute engine cooling
    double dEngineTemperatureCoolingCS = (dCurrentEngineTempC - dMaxTemperatureC) * 0.01;
    if (dEngineTemperatureCoolingCS < 0.0) dEngineTemperatureCoolingCS = 0.0;
    dEngineTemperatureCoolingCS *= -1.0;

    dCurrentEngineTempC += dEngineTemperatureCoolingCS * dDeltaTimeSeconds;

    // Compute natural temperature loss
    if (dTemperatureChangeCS < 0.01)
    {
        dCurrentEngineTempC -= 0.05 * dDeltaTimeSeconds;
    }

    // Bring car speed value down from RPM
    dCarSpeedMS /= CEngineSettings::SpeedMSToRPS;

    // Assign new engine RPM
    m_cVehicle.sensors().currentRPM().setValue(CUtils::RPSToRPM(dEngineRPS));

    // Assign new speed
    m_cVehicle.sensors().currentSpeedKMH().setValue(CUtils::MSToKMH(dCarSpeedMS));

    // Assign new engine temperature
    m_cVehicle.sensors().currentEngineTempC().setValue(dCurrentEngineTempC);

    // Assign new fuel level
    m_cVehicle.sensors().currentFuelLevelL().setValue(dFuelLevelL);
}
