
#include "CSensorBooleanValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorBooleanValue::CSensorBooleanValue(bool bValue)
    : m_bValue(bValue)
{
}

//-------------------------------------------------------------------------------------------------

CSensorBooleanValue::~CSensorBooleanValue()
{
}

//-------------------------------------------------------------------------------------------------

void CSensorBooleanValue::setValue(bool bValue)
{
    m_bValue = bValue;
}

//-------------------------------------------------------------------------------------------------

bool CSensorBooleanValue::value() const
{
    return m_bValue;
}
