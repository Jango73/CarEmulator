
#include "CNormalizedInput.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CNormalizedInput::CNormalizedInput()
    : m_bReleased(false)
    , m_dValue(0.0)
{
}

//-------------------------------------------------------------------------------------------------

CNormalizedInput::~CNormalizedInput()
{
}

//-------------------------------------------------------------------------------------------------

void CNormalizedInput::setValue(double dValue)
{
    m_dValue = qBound(-1.0, dValue, 1.0);
}

//-------------------------------------------------------------------------------------------------

double CNormalizedInput::value() const
{
    return m_dValue;
}

//-------------------------------------------------------------------------------------------------

void CNormalizedInput::Release(bool bValue)
{
    m_bReleased = bValue;
}
