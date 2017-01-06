
#include "CSensors.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensors::CSensors()
    : m_vCurrentRPM(CSensorRealValue(0.0))
    , m_vCurrentSpeedKMH(CSensorRealValue(0.0))
    , m_vCurrentEngineTempC(CSensorRealValue(80.0))
    , m_vAccelerationKMHS(CSensorRealValue(0.0))
    , m_vEngineAccelerationRPSS(CSensorRealValue(0.0))
    , m_vMaximumFuelLevelL(CSensorRealValue(60.0))
    , m_vCurrentFuelLevelL(CSensorRealValue(60.0))
    , m_vCurrentFuelLevelPercent(CSensorRealValue(100.0))
    , m_vFuelConsumptionL100KM(CSensorRealValue(0.0))
    , m_eMainLights(eMLOff)
    , m_eSecondaryLights(eSLOff)
    , m_eBlinkLights(eBLOff)
    , m_dPreviousSpeedKMH(0.0)
    , m_dPreviousRPS(0.0)
    , m_dPreviousFuelLevelL(0.0)
{
    m_mDoorSensors[eDoorDriver] = CSensorBooleanValue(false);
    m_mDoorSensors[eDoorPassenger] = CSensorBooleanValue(false);
    m_mDoorSensors[eDoorRearLeft] = CSensorBooleanValue(false);
    m_mDoorSensors[eDoorRearRight] = CSensorBooleanValue(false);
    m_mDoorSensors[eDoorBack] = CSensorBooleanValue(false);
    m_mDoorSensors[eDoorEngine] = CSensorBooleanValue(false);

    m_tFuelConsTimer.start();
}

//-------------------------------------------------------------------------------------------------

CSensors::~CSensors()
{
}

//-------------------------------------------------------------------------------------------------

void CSensors::setMainLightsState(EMainLights eValue)
{
    m_eMainLights = eValue;
}

void CSensors::secondaryLightsState(ESecondaryLights eValue)
{
    m_eSecondaryLights = eValue;
}

void CSensors::blinkLightsState(EBlinkLights eValue)
{
    m_eBlinkLights = eValue;
}

//-------------------------------------------------------------------------------------------------

const CSensorRealValue& CSensors::currentRPM() const
{
    return m_vCurrentRPM;
}

const CSensorRealValue& CSensors::currentSpeedKMH() const
{
    return m_vCurrentSpeedKMH;
}

const CSensorRealValue& CSensors::currentEngineTempC() const
{
    return m_vCurrentEngineTempC;
}

const CSensorRealValue& CSensors::accelerationKMHS() const
{
    return m_vAccelerationKMHS;
}

const CSensorRealValue& CSensors::engineAccelerationRPSS() const
{
    return m_vEngineAccelerationRPSS;
}

const CSensorRealValue& CSensors::currentFuelLevelL() const
{
    return m_vCurrentFuelLevelL;
}

const CSensorRealValue& CSensors::currentFuelLevelPercent() const
{
    return m_vCurrentFuelLevelPercent;
}

const CSensorRealValue& CSensors::fuelConsumptionL100KM() const
{
    return m_vFuelConsumptionL100KM;
}

//-------------------------------------------------------------------------------------------------

CSensorRealValue& CSensors::currentRPM()
{
    return m_vCurrentRPM;
}

CSensorRealValue& CSensors::currentSpeedKMH()
{
    return m_vCurrentSpeedKMH;
}

CSensorRealValue& CSensors::currentEngineTempC()
{
    return m_vCurrentEngineTempC;
}

CSensorRealValue& CSensors::accelerationKMHS()
{
    return m_vAccelerationKMHS;
}

CSensorRealValue& CSensors::engineAccelerationRPSS()
{
    return m_vEngineAccelerationRPSS;
}

CSensorRealValue& CSensors::currentFuelLevelL()
{
    return m_vCurrentFuelLevelL;
}

CSensorRealValue& CSensors::currentFuelLevelPercent()
{
    return m_vCurrentFuelLevelPercent;
}

CSensorRealValue& CSensors::fuelConsumptionL100KM()
{
    return m_vFuelConsumptionL100KM;
}

QMap<CSensors::EDoorSensors, CSensorBooleanValue>& CSensors::doorSensors()
{
    return m_mDoorSensors;
}

CSensors::EMainLights CSensors::mainLightsState() const
{
    return m_eMainLights;
}

CSensors::ESecondaryLights CSensors::secondaryLightsState() const
{
    return m_eSecondaryLights;
}

CSensors::EBlinkLights CSensors::blinkLightsState() const
{
    return m_eBlinkLights;
}

//-------------------------------------------------------------------------------------------------

void CSensors::process(double dDeltaTimeMillis)
{
    double dDeltaTimeSeconds = CUtils::millisToSeconds(dDeltaTimeMillis);

    // Compute acceleration
    double dSpeedDiffKMH = m_vCurrentSpeedKMH.value() - m_dPreviousSpeedKMH;

    if (abs(dSpeedDiffKMH) < ENGINE_ESPILON)
    {
        m_vAccelerationKMHS.setValue(0.0);
    }
    else
    {
        m_vAccelerationKMHS.setValue(dSpeedDiffKMH / dDeltaTimeSeconds);
    }

    // Compute engine acceleration
    double dEngineDiffRPS = CUtils::RPMToRPS(m_vCurrentRPM.value()) - m_dPreviousRPS;

    if (abs(dEngineDiffRPS) < ENGINE_ESPILON)
    {
        m_vEngineAccelerationRPSS.setValue(0.0);
    }
    else
    {
        m_vEngineAccelerationRPSS.setValue(dEngineDiffRPS / dDeltaTimeSeconds);
    }

    // Compute fuel consumption
    if (m_tFuelConsTimer.elapsed() > 1000)
    {
        double dFuelConsTimerSeconds = CUtils::millisToSeconds(m_tFuelConsTimer.elapsed());
        double dFuelDiff = m_vCurrentFuelLevelL.value() - m_dPreviousFuelLevelL;
        m_dPreviousFuelLevelL = m_vCurrentFuelLevelL.value();

        if (m_vCurrentSpeedKMH.value() > 3.0)
        {
            double dFuelConsumptionLS = (dFuelDiff * dFuelConsTimerSeconds) * -1.0;
            // m_vFuelConsumptionL100KM.setValue(FuelConsumptionLS);
            double dSecondsFor100KM = CUtils::hoursToSeconds(100.0 / m_vCurrentSpeedKMH.value());
            m_vFuelConsumptionL100KM.setValue(dFuelConsumptionLS * dSecondsFor100KM);
        }
        else
        {
            m_vFuelConsumptionL100KM.setValue(0.0);
        }

        m_tFuelConsTimer.restart();
    }

    // Set fuel percent
    m_vCurrentFuelLevelPercent.setValue((m_vCurrentFuelLevelL.value() / m_vMaximumFuelLevelL.value()) * 100.0);

    m_dPreviousSpeedKMH = m_vCurrentSpeedKMH.value();
    m_dPreviousRPS = CUtils::RPMToRPS(m_vCurrentRPM.value());
}
