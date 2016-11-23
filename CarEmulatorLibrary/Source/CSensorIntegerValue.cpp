
#include "CSensorIntegerValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorIntegerValue::CSensorIntegerValue(int iValue)
    : m_iValue(iValue)
{
}

//-------------------------------------------------------------------------------------------------

CSensorIntegerValue::~CSensorIntegerValue()
{
}

//-------------------------------------------------------------------------------------------------

void CSensorIntegerValue::setValue(int iValue)
{
    m_iValue = iValue;
}

//-------------------------------------------------------------------------------------------------

int CSensorIntegerValue::value() const
{
    return m_iValue;
}
