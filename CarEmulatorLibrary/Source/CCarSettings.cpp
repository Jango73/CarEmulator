
#include "CCar.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCarSettings::CCarSettings()
{
    m_dWeightKG = 1200.0;
}

CCarSettings::~CCarSettings()
{
}

void CCarSettings::setWeightKG(double dValue)
{
    m_dWeightKG = dValue;
}

double CCarSettings::weightKG() const
{
    return m_dWeightKG;
}
