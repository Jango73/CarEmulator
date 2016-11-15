
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
    , m_dMaxSpeedKMH(200.0)
    , m_dClutchContact(0.3)
    , m_dClutchFullEngaged(0.8)
    , m_dGasPedalEpsilon(0.02)
    , m_dStartupEndSpeedKMH(5.0)
{
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
