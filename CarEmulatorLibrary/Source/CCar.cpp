
#include "CCar.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCar::CCar()
{
}

CCar::~CCar()
{
}

CCarSettings& CCar::Settings()
{
    return _Settings;
}

CEngineSettings& CCar::EngineSettings()
{
    return _EngineSettings;
}

CSensors& CCar::Sensors()
{
    return _Sensors;
}

CGearBox& CCar::GearBox()
{
    return _GearBox;
}

CNormalizedInput& CCar::GasPedal()
{
    return _GasPedal;
}

CNormalizedInput& CCar::BreakPedal()
{
    return _BreakPedal;
}

CNormalizedInput& CCar::ClutchPedal()
{
    return _ClutchPedal;
}

void CCar::Process(double DeltaTimeMillis)
{
    _Sensors.Process(DeltaTimeMillis);
}
