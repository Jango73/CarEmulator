
#include "CGearBox.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CGearBox::CGearBox()
    : m_iNumGears(6)
    , m_iCurrentGear(0)
    , m_iTargetGear(0)
{
    m_vRatios << 0.0;
    m_vRatios << 2.20;
    m_vRatios << 1.20;
    m_vRatios << 0.75;
    m_vRatios << 0.60;
    m_vRatios << 0.50;

    m_vMaxSpeedKMH << 0.0;
    m_vMaxSpeedKMH << 10.0;
    m_vMaxSpeedKMH << 25.0;
    m_vMaxSpeedKMH << 45.0;
    m_vMaxSpeedKMH << 65.0;
    m_vMaxSpeedKMH << 200.0;

    m_vMinSpeedKMH << 0.0;
    m_vMinSpeedKMH << 5.0;
    m_vMinSpeedKMH << 10.0;
    m_vMinSpeedKMH << 20.0;
    m_vMinSpeedKMH << 40.0;
    m_vMinSpeedKMH << 60.0;

    m_tTimer.setInterval(1000);

    connect(&m_tTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

CGearBox::~CGearBox()
{
}

int CGearBox::numGears() const
{
    return m_iNumGears;
}

int CGearBox::currentGear() const
{
    return m_iCurrentGear;
}

int CGearBox::targetGear() const
{
    return m_iTargetGear;
}

double CGearBox::currentRatio() const
{
    return m_vRatios[m_iCurrentGear];
}

double CGearBox::currentMaxSpeedKMH() const
{
    return m_vMaxSpeedKMH[m_iCurrentGear];
}

double CGearBox::currentMinSpeedKMH() const
{
    return m_vMinSpeedKMH[m_iCurrentGear];
}

void CGearBox::onTimeout()
{
    m_tTimer.stop();
    m_iCurrentGear = m_iTargetGear;
}

bool CGearBox::setNeutralGear()
{
    if (m_iCurrentGear != 0)
    {
        m_iTargetGear = 0;
        m_tTimer.start();
    }
    return true;
}

bool CGearBox::setHighestGear()
{
    if (m_iCurrentGear < m_iNumGears - 1)
    {
        m_iTargetGear = m_iNumGears - 1;
        m_tTimer.start();
    }
    return true;
}

bool CGearBox::up()
{
    if (m_iCurrentGear == m_iNumGears - 1) return false;
    m_iTargetGear = m_iCurrentGear + 1;
    m_tTimer.start();
    return true;
}

bool CGearBox::down()
{
    if (m_iCurrentGear == 0) return false;
    m_iTargetGear = m_iCurrentGear - 1;
    m_tTimer.start();
    return true;
}
