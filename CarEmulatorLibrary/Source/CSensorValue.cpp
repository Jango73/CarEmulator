
#include "CSensorValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorValue::CSensorValue()
    : m_bIsValid(true)
{
}

CSensorValue::~CSensorValue()
{
}

bool CSensorValue::isValid() const
{
    return m_bIsValid;
}
