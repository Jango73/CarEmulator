
#include "CGearBox.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CGearBox::CGearBox()
    : _NumGears(6)
    , _CurrentGear(0)
    , _TargetGear(0)
{
    _Ratios << 0.0;
    _Ratios << 2.20;
    _Ratios << 1.20;
    _Ratios << 0.75;
    _Ratios << 0.60;
    _Ratios << 0.50;

    _MaxSpeedKMH << 0.0;
    _MaxSpeedKMH << 10.0;
    _MaxSpeedKMH << 25.0;
    _MaxSpeedKMH << 45.0;
    _MaxSpeedKMH << 65.0;
    _MaxSpeedKMH << 200.0;

    _MinSpeedKMH << 0.0;
    _MinSpeedKMH << 5.0;
    _MinSpeedKMH << 10.0;
    _MinSpeedKMH << 20.0;
    _MinSpeedKMH << 40.0;
    _MinSpeedKMH << 60.0;

    _Timer.setInterval(1000);

    connect(&_Timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

CGearBox::~CGearBox()
{
}

int CGearBox::NumGears() const
{
    return _NumGears;
}

int CGearBox::CurrentGear() const
{
    return _CurrentGear;
}

int CGearBox::TargetGear() const
{
    return _TargetGear;
}

double CGearBox::CurrentRatio() const
{
    return _Ratios[_CurrentGear];
}

double CGearBox::CurrentMaxSpeedKMH() const
{
    return _MaxSpeedKMH[_CurrentGear];
}

double CGearBox::CurrentMinSpeedKMH() const
{
    return _MinSpeedKMH[_CurrentGear];
}

void CGearBox::onTimeout()
{
    _Timer.stop();
    _CurrentGear = _TargetGear;
}

bool CGearBox::SetNeutralGear()
{
    if (_CurrentGear != 0)
    {
        _TargetGear = 0;
        _Timer.start();
    }
    return true;
}

bool CGearBox::SetHighestGear()
{
    if (_CurrentGear < _NumGears - 1)
    {
        _TargetGear = _NumGears - 1;
        _Timer.start();
    }
    return true;
}

bool CGearBox::Up()
{
    if (_CurrentGear == _NumGears - 1) return false;
    _TargetGear = _CurrentGear + 1;
    _Timer.start();
    return true;
}

bool CGearBox::Down()
{
    if (_CurrentGear == 0) return false;
    _TargetGear = _CurrentGear - 1;
    _Timer.start();
    return true;
}
