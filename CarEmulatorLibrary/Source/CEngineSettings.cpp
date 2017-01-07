
#include "CEngineSettings.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

const double CEngineSettings::SpeedMSToRPS = 9.0;
const double CEngineSettings::RPSToL = 0.0005;
const double CEngineSettings::WheelRadiusM = 0.4;

//-------------------------------------------------------------------------------------------------

CEngineSettings::CEngineSettings()
    : m_dStallRPM(500.0)
    , m_dIdleRPM(800.0)
    , m_dMaxRPM(3000.0)
    , m_dBreakDownRPM(6000.0)
    , m_dMaxTemperatureC(90.0)
    , m_dBreakDownTemperatureC(120.0)
    , m_dMaxSpeedKMH(180.0)
    , m_dClutchContact(0.3)
    , m_dClutchFullEngaged(0.8)
    , m_dGasPedalEpsilon(0.02)
    , m_dStartupEndSpeedKMH(5.0)
{
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(0, 0.0);         //
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(5, 3.2);         // 300 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(10, 4.8);        // 600 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(16, 8.0);        // 960 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(45, 16.0);       // 2700 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(75, 20.0);       // 4500 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(103, 14.4);      // 6180 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(133, 3.2);       // 7980 RPM
    m_iTorqueTable << CInterpolator<double>::InterpolatorValue(150, 0.0);       // 9000 RPM
}

//-------------------------------------------------------------------------------------------------

CEngineSettings::~CEngineSettings()
{
}

//-------------------------------------------------------------------------------------------------

double CEngineSettings::stallRPM() const
{
    return m_dStallRPM;
}

double CEngineSettings::idleRPM() const
{
    return m_dIdleRPM;
}

double CEngineSettings::maxRPM() const
{
    return m_dMaxRPM;
}

double CEngineSettings::breakDownRPM() const
{
    return m_dBreakDownRPM;
}

double CEngineSettings::maxTemperatureC() const
{
    return m_dMaxTemperatureC;
}

double CEngineSettings::breakDownTemperatureC() const
{
    return m_dBreakDownTemperatureC;
}

double CEngineSettings::maxSpeedKMH() const
{
    return m_dMaxSpeedKMH;
}

double CEngineSettings::clutchContact() const
{
    return m_dClutchContact;
}

double CEngineSettings::clutchFullEngaged() const
{
    return m_dClutchFullEngaged;
}

double CEngineSettings::gasPedalEpsilon() const
{
    return m_dGasPedalEpsilon;
}

double CEngineSettings::startupEndSpeedKMH() const
{
    return m_dStartupEndSpeedKMH;
}

CInterpolator<double>& CEngineSettings::torqueTable()
{
    return m_iTorqueTable;
}

const CInterpolator<double>& CEngineSettings::torqueTable() const
{
    return m_iTorqueTable;
}

void CEngineSettings::applyParameters(CXMLNode xParams)
{
    CXMLNode xTorqueTable = xParams.getNodeByTagName(PARAM_NAME_TORQUETABLE);

    if (xTorqueTable.isEmpty() == false)
    {
        m_iTorqueTable.clear();

        QVector<CXMLNode> xTorqueSteps = xParams.getNodesByTagName(PARAM_NAME_TORQUESTEP);

        foreach (CXMLNode xTorque, xTorqueSteps)
        {
            double dRoundsPerSecond = xTorque.attributes()[PARAM_NAME_ROUNDSPERSECOND].toDouble();
            double dFactor = xTorque.attributes()[PARAM_NAME_FACTOR].toDouble();

            m_iTorqueTable << CInterpolator<double>::InterpolatorValue(dRoundsPerSecond, dFactor);
        }
    }
}
