
#include "CCar.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCar::CCar(bool bSoundOn)
    : m_pSound(NULL)
    , m_bEngineOn(false)
    , m_dWheelRPS(0.0)
    , m_dEnginePowerRPS(0.0)
    , m_dTorqueTransferFactor(0.0)
{
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(0, 0.0);         //
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(5, 0.4);         // 300 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(10, 0.6);        // 600 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(16, 1.0);        // 960 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(45, 2.0);        // 2700 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(75, 2.5);        // 4500 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(103, 1.8);       // 6180 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(133, 0.4);       // 7980 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(150, 0.0);       // 9000 RPM

    if (bSoundOn)
    {
        m_pSound = new CEngineSound(this);
    }

    connect(&m_gGearBox, SIGNAL(gearChanged()), this, SLOT(onGearChanged()));
}

//-------------------------------------------------------------------------------------------------

CCar::~CCar()
{
    if (m_pSound != NULL)
    {
        delete m_pSound;
    }
}

//-------------------------------------------------------------------------------------------------

void CCar::setGearValue(int iValue)
{
    m_gGearBox.setCurrentGear(iValue);
}

//-------------------------------------------------------------------------------------------------

void CCar::setGasPedalValue(double dValue)
{
    m_iGasPedal.setValue(dValue);
    emit gasPedalChanged();
}

//-------------------------------------------------------------------------------------------------

void CCar::setBreakPedalValue(double dValue)
{
    m_iBreakPedal.setValue(dValue);
    emit breakPedalChanged();
}

//-------------------------------------------------------------------------------------------------

void CCar::setClutchPedalValue(double dValue)
{
    m_iClutchPedal.setValue(dValue);
    emit clutchPedalChanged();
}

//-------------------------------------------------------------------------------------------------

CCarSettings& CCar::settings()
{
    return m_sSettings;
}

//-------------------------------------------------------------------------------------------------

CEngineSettings& CCar::engineSettings()
{
    return m_sEngineSettings;
}

//-------------------------------------------------------------------------------------------------

CSensors& CCar::sensors()
{
    return m_sSensors;
}

//-------------------------------------------------------------------------------------------------

CGearBox& CCar::gearBox()
{
    return m_gGearBox;
}

//-------------------------------------------------------------------------------------------------

CNormalizedInput& CCar::gasPedal()
{
    return m_iGasPedal;
}

//-------------------------------------------------------------------------------------------------

CNormalizedInput& CCar::breakPedal()
{
    return m_iBreakPedal;
}

//-------------------------------------------------------------------------------------------------

CNormalizedInput& CCar::clutchPedal()
{
    return m_iClutchPedal;
}

//-------------------------------------------------------------------------------------------------

CNormalizedInput& CCar::steering()
{
    return m_iSteering;
}

//-------------------------------------------------------------------------------------------------

int CCar::gearValue() const
{
    return m_gGearBox.currentGear();
}

//-------------------------------------------------------------------------------------------------

double CCar::gasPedalValue() const
{
    return m_iGasPedal.value();
}

//-------------------------------------------------------------------------------------------------

double CCar::breakPedalValue() const
{
    return m_iBreakPedal.value();
}

//-------------------------------------------------------------------------------------------------

double CCar::clutchPedalValue() const
{
    return m_iClutchPedal.value();
}

//-------------------------------------------------------------------------------------------------

double CCar::engineRPM() const
{
    return m_sSensors.currentRPM().value();
}

//-------------------------------------------------------------------------------------------------

double CCar::enginePowerHP() const
{
    return m_dEnginePowerRPS;
}

//-------------------------------------------------------------------------------------------------

double CCar::engineTorqueNM() const
{
    return m_dEnginePowerRPS;
}

//-------------------------------------------------------------------------------------------------

double CCar::speedKMH() const
{
    return m_sSensors.currentSpeedKMH().value();
}

//-------------------------------------------------------------------------------------------------

double CCar::fuelPercent() const
{
    return m_sSensors.currentFuelLevelPercent().value();
}

//-------------------------------------------------------------------------------------------------

double CCar::engineTemperatureC() const
{
    return m_sSensors.currentEngineTempC().value();
}

//-------------------------------------------------------------------------------------------------

double CCar::engineWaterTemperatureC() const
{
    return m_sSensors.currentEngineTempC().value();
}

//-------------------------------------------------------------------------------------------------

double CCar::torqueTransferFactor() const
{
    return m_dTorqueTransferFactor;
}

//-------------------------------------------------------------------------------------------------

void CCar::startEngine()
{
    m_bEngineOn = true;
}

//-------------------------------------------------------------------------------------------------

void CCar::stopEngine()
{
    m_bEngineOn = false;
}

//-------------------------------------------------------------------------------------------------

void CCar::gearUp()
{
    m_gGearBox.up();
}

//-------------------------------------------------------------------------------------------------

void CCar::gearDown()
{
    m_gGearBox.down();
}

//-------------------------------------------------------------------------------------------------

void CCar::process(double dDeltaTimeMillis)
{
    // Get parameters from settings and sensors
    double dDeltaTimeSeconds = CUtils::millisToSeconds(dDeltaTimeMillis);
    double dEngineRPS = CUtils::RPMToRPS(m_sSensors.currentRPM().value());
    double dIdleEngineRPS = CUtils::RPMToRPS(engineSettings().idleRPM());
    double dBreakDownRPS = CUtils::RPMToRPS(engineSettings().breakDownRPM());
    double dCarSpeedMS = CUtils::KMHToMS(m_sSensors.currentSpeedKMH().value());
    double dClutchRange = engineSettings().clutchFullEngaged() - engineSettings().clutchContact();
    double dGearRatio = gearBox().currentRatio();
    double dCurrentEngineTempC = m_sSensors.currentEngineTempC().value();
    double dMaxTemperatureC = engineSettings().maxTemperatureC();
    double dBreakDownTemperatureC = engineSettings().breakDownTemperatureC();
    double dFuelLevelL = m_sSensors.currentFuelLevelL().value();

    bool bReverse = dGearRatio < 0.0;

    dGearRatio = fabs(dGearRatio);

    // Actual clutch level using contact point and full engage point
    m_iClutchLevel.setValue((clutchPedal().value() - engineSettings().clutchContact()) / dClutchRange);

    // Compute fuel consumption
    double dFuelGasFactor = gasPedal().value();
    if (dFuelGasFactor < 0.02) dFuelGasFactor = 0.02;

    if (m_bEngineOn == false)
    {
        dFuelGasFactor = 0.0;
    }

    // Torque transfer factor
    m_dTorqueTransferFactor = m_iClutchLevel.value();
    if (m_dTorqueTransferFactor < 0.0) m_dTorqueTransferFactor = 0.0;
    if (m_dTorqueTransferFactor > 1.0) m_dTorqueTransferFactor = 1.0;
    if (dGearRatio == 0.0) m_dTorqueTransferFactor = 0.0;

    // Bring car speed value up to RPM
    dCarSpeedMS *= CEngineSettings::SpeedMSToRPS;

    // Wheel circumference
    double dWheelCircM = 2.0 * CEngineSettings::WheelRadiusM * M_PI;
    m_dWheelRPS = dCarSpeedMS / dWheelCircM;

    // Raw force produced by engine
    double dRawEngineTorqueRPS = dEngineRPS * dFuelGasFactor;

    // Slow down the engine RPS using limit RPM
    dRawEngineTorqueRPS = (dRawEngineTorqueRPS * ((dBreakDownRPS - dRawEngineTorqueRPS) / dBreakDownRPS)) * 4;

    double dEngineDrag = ((dBreakDownRPS - dEngineRPS) / dBreakDownRPS);

    // Apply the engine drag (reaching limit RPM) to the engine RPM
    dEngineRPS += (((dRawEngineTorqueRPS * (1.0 - m_dTorqueTransferFactor)) * dEngineDrag) * dDeltaTimeSeconds) * 1.5;

    // Bring back engine to minimum RPS according to torque transfer factor and fuel flow
    double dIdlePower = (dEngineRPS - dIdleEngineRPS) / (dIdleEngineRPS / 15.0);

    if (m_bEngineOn == false)
    {
        dIdlePower = dEngineRPS / (dIdleEngineRPS / 15.0);
    }

    dEngineRPS -= ((dIdlePower * (1.0 - m_dTorqueTransferFactor) * (1.0 - dFuelGasFactor)) * dDeltaTimeSeconds) * 1.5;

    // Compute the force from the wheels applied to the engine by the clutch
    double dWheelRPSToEngine = 0.0;

    if (dGearRatio != 0.0)
    {
        dWheelRPSToEngine = ((m_dWheelRPS - (dEngineRPS / dGearRatio)) * m_dTorqueTransferFactor) * 8.0;
    }

    // Apply the wheel force to the engine
    dEngineRPS += dWheelRPSToEngine * dDeltaTimeSeconds;

    if (dEngineRPS < 0) dEngineRPS = 0;
    if (dEngineRPS > dBreakDownRPS) dEngineRPS = dBreakDownRPS;

    // Compute the engine power
    m_dEnginePowerRPS = (m_iTorqueTable.getValue(dEngineRPS) * 8.0) * dFuelGasFactor;

    double dCarSpeedDivider = dCarSpeedMS * 0.05;
    if (dCarSpeedDivider < 1.0) dCarSpeedDivider = 1.0;

    // Add power to engine when starting up
    m_dEnginePowerRPS += (dEngineRPS * (1.0 - m_dTorqueTransferFactor)) / dCarSpeedDivider;

    // Compute engine break
    // TODO

    // Compute acceleration
    double dAccelRPS = m_dEnginePowerRPS * m_dTorqueTransferFactor;

    if (bReverse)
    {
        dAccelRPS *= -1.0;
    }

    // Compute car speed
    m_dWheelRPS += dAccelRPS * dDeltaTimeSeconds;

    if (dCarSpeedMS > 0.0)
    {
        m_dWheelRPS -= ((breakPedal().value() * 60) * dDeltaTimeSeconds) * 0.25;
    }
    else
    {
        m_dWheelRPS += ((breakPedal().value() * 60) * dDeltaTimeSeconds) * 0.25;
    }

    dCarSpeedMS = m_dWheelRPS * dWheelCircM;

    // Compute ground drag
    double dGroundDrag = dCarSpeedMS / -5000.0;
    if (dGroundDrag > -2) dGroundDrag = -2;

    // Compute air drag
    double dAirDrag = (dCarSpeedMS * dCarSpeedMS) / -5000.0;
    if (dAirDrag > -2) dAirDrag = -2;

    // Compute total drag
    double dTotalDrag = dGroundDrag + dAirDrag;

    if (dCarSpeedMS < 0.0)
    {
        dTotalDrag *= -1.0;
    }

    // Add drags to speed
    dCarSpeedMS += (dTotalDrag * dDeltaTimeSeconds);

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

    // Check stall
    // double dStallRPS = CUtils::RPMToRPS(m_sEngineSettings.stallRPM()) / 2.0;
    double dStallRPS = 1.0;

    if (dEngineRPS < dStallRPS)
    {
        m_bEngineOn = false;
    }

    // Assign new engine RPM
    m_sSensors.currentRPM().setValue(CUtils::RPSToRPM(dEngineRPS));

    // Assign new speed
    m_sSensors.currentSpeedKMH().setValue(CUtils::MSToKMH(dCarSpeedMS));

    // Assign new engine temperature
    m_sSensors.currentEngineTempC().setValue(dCurrentEngineTempC);

    // Assign new fuel level
    m_sSensors.currentFuelLevelL().setValue(dFuelLevelL);

    // Process sensors
    m_sSensors.process(dDeltaTimeMillis);

    emit engineRPMChanged();
    emit enginePowerHPChanged();
    emit engineTorqueNMChanged();
    emit speedKMHChanged();
    emit fuelPercentChanged();
    emit engineTemperatureCChanged();
    emit engineWaterTemperatureCChanged();
}

//-------------------------------------------------------------------------------------------------

void CCar::onGearChanged()
{
    emit gearChanged();
}
