
#include "CCar.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCarSettings::CCarSettings()
{
    _WeightKG = 1200.0;
}

CCarSettings::~CCarSettings()
{
}

void CCarSettings::setWeightKG(double dValue)
{
    _WeightKG = dValue;
}

double CCarSettings::WeightKG() const
{
    return _WeightKG;
}
