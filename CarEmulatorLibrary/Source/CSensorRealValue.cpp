
#include "CSensorRealValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorRealValue::CSensorRealValue(double dValue)
    : m_dValue(dValue)
{
}

//-------------------------------------------------------------------------------------------------

CSensorRealValue::~CSensorRealValue()
{
}

//-------------------------------------------------------------------------------------------------

void CSensorRealValue::setValue(double dValue)
{
    m_dValue = dValue;
}

//-------------------------------------------------------------------------------------------------

double CSensorRealValue::value() const
{
    return m_dValue;
}
