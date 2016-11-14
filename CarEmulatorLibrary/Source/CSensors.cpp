
#include "CSensors.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensors::CSensors()
    : m_vCurrentRPM(CSensorDoubleValue(0.0))
    , m_vCurrentSpeedKMH(CSensorDoubleValue(0.0))
    , m_vCurrentEngineTempC(CSensorDoubleValue(80.0))
    , m_vAccelerationKMHS(CSensorDoubleValue(0.0))
    , m_vEngineAccelerationRPSS(CSensorDoubleValue(0.0))
    , m_vCurrentFuelLevelL(CSensorDoubleValue(60.0))
    , m_vCurrentFuelLevelPercent(CSensorDoubleValue(100.0))
    , m_vFuelConsumptionL100KM(CSensorDoubleValue(0.0))
{
    m_tFuelConsTimer.start();
}

CSensors::~CSensors()
{
}

CSensorDoubleValue& CSensors::currentRPM()
{
    return m_vCurrentRPM;
}

CSensorDoubleValue& CSensors::currentSpeedKMH()
{
    return m_vCurrentSpeedKMH;
}

CSensorDoubleValue& CSensors::currentEngineTempC()
{
    return m_vCurrentEngineTempC;
}

CSensorDoubleValue& CSensors::accelerationKMHS()
{
    return m_vAccelerationKMHS;
}

CSensorDoubleValue& CSensors::engineAccelerationRPSS()
{
    return m_vEngineAccelerationRPSS;
}

CSensorDoubleValue& CSensors::currentFuelLevelL()
{
    return m_vCurrentFuelLevelL;
}

CSensorDoubleValue& CSensors::currentFuelLevelPercent()
{
    return m_vCurrentFuelLevelPercent;
}

CSensorDoubleValue& CSensors::fuelConsumptionL100KM()
{
    return m_vFuelConsumptionL100KM;
}

void CSensors::process(double dDeltaTimeMillis)
{
    // Compute acceleration
    double dSpeedDiffKMH = m_vCurrentSpeedKMH.value() - m_vPreviousSpeedKMH;

    if (abs(dSpeedDiffKMH) < 0.0001)
    {
        m_vAccelerationKMHS.setValue(0.0);
    }
    else
    {
        m_vAccelerationKMHS.setValue(dSpeedDiffKMH / (dDeltaTimeMillis / 1000.0));
    }

    // Compute engine acceleration
    double dEngineDiffRPS = CUtils::RPMToRPS(m_vCurrentRPM.value()) - m_vPreviousRPS;

    if (abs(dEngineDiffRPS) < 0.0001)
    {
        m_vEngineAccelerationRPSS.setValue(0.0);
    }
    else
    {
        m_vEngineAccelerationRPSS.setValue(dEngineDiffRPS / (dDeltaTimeMillis / 1000.0));
    }

    // Compute fuel consumption

    if (m_tFuelConsTimer.elapsed() > 1000)
    {
        double dFuelConsTimerSeconds = CUtils::MillisToSeconds(m_tFuelConsTimer.elapsed());
        double dFuelDiff = m_vCurrentFuelLevelL.value() - m_vPreviousFuelLevelL;
        m_vPreviousFuelLevelL = m_vCurrentFuelLevelL.value();

        if (m_vCurrentSpeedKMH.value() > 3.0)
        {
            double dFuelConsumptionLS = (dFuelDiff * dFuelConsTimerSeconds) * -1.0;
            // m_vFuelConsumptionL100KM.setValue(FuelConsumptionLS);
            double dSecondsFor100KM = CUtils::HoursToSeconds(100.0 / m_vCurrentSpeedKMH.value());
            m_vFuelConsumptionL100KM.setValue(dFuelConsumptionLS * dSecondsFor100KM);
        }
        else
        {
            m_vFuelConsumptionL100KM.setValue(0.0);
        }

        m_tFuelConsTimer.restart();
    }

    m_vPreviousSpeedKMH = m_vCurrentSpeedKMH.value();
    m_vPreviousRPS = CUtils::RPMToRPS(m_vCurrentRPM.value());
}
