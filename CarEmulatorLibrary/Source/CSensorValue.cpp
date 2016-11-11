
#include "CSensorValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorValue::CSensorValue(double dValue)
    : m_bIsValid(true)
    , m_dValue(dValue)
{
}

CSensorValue::~CSensorValue()
{
}

void CSensorValue::setValue(double dValue)
{
    m_dValue = dValue;
}

bool CSensorValue::isValid() const
{
    return m_bIsValid;
}

double CSensorValue::value() const
{
    return m_dValue;
}
