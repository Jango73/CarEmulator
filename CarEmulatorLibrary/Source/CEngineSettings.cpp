
#include "CEngineSettings.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

const double CEngineSettings::SpeedMSToRPS = 9.0;
const double CEngineSettings::RPSToL = 0.0005;
const double CEngineSettings::WheelRadiusM = 0.4;

//-------------------------------------------------------------------------------------------------

CEngineSettings::CEngineSettings()
    : _StallRPM(500.0)
    , _IdleRPM(800.0)
    , _MaxRPM(3000.0)
    , _BreakDownRPM(8000.0)
    , _MaxTemperatureC(90.0)
    , _BreakDownTemperatureC(120.0)
    , _MaxSpeedKMH(200.0)
    , _ClutchContact(0.3)
    , _ClutchFullEngaged(0.6)
    , _GasPedalEpsilon(0.02)
    , _StartupEndSpeedKMH(5.0)
{
}

CEngineSettings::~CEngineSettings()
{
}

double CEngineSettings::StallRPM() const
{
    return _StallRPM;
}

double CEngineSettings::IdleRPM() const
{
    return _IdleRPM;
}

double CEngineSettings::MaxRPM() const
{
    return _MaxRPM;
}

double CEngineSettings::BreakDownRPM() const
{
    return _BreakDownRPM;
}

double CEngineSettings::MaxTemperatureC() const
{
    return _MaxTemperatureC;
}

double CEngineSettings::BreakDownTemperatureC() const
{
    return _BreakDownTemperatureC;
}

double CEngineSettings::MaxSpeedKMH() const
{
    return _MaxSpeedKMH;
}

double CEngineSettings::ClutchContact() const
{
    return _ClutchContact;
}

double CEngineSettings::ClutchFullEngaged() const
{
    return _ClutchFullEngaged;
}

double CEngineSettings::GasPedalEpsilon() const
{
    return _GasPedalEpsilon;
}

double CEngineSettings::StartupEndSpeedKMH() const
{
    return _StartupEndSpeedKMH;
}
