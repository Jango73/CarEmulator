
#include "CSensorRealValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorDoubleValue::CSensorDoubleValue(double dValue)
    : m_bIsValid(true)
    , m_dValue(dValue)
{
}

CSensorDoubleValue::~CSensorDoubleValue()
{
}

void CSensorDoubleValue::setValue(double dValue)
{
    m_dValue = dValue;
}

bool CSensorDoubleValue::isValid() const
{
    return m_bIsValid;
}

double CSensorDoubleValue::value() const
{
    return m_dValue;
}
