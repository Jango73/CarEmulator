
#include "CSensorValue.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensorValue::CSensorValue(double dValue)
    : _IsValid(true)
    , _Value(dValue)
{
}

CSensorValue::~CSensorValue()
{
}

void CSensorValue::setValue(double dValue)
{
    _Value = dValue;
}

bool CSensorValue::IsValid() const
{
    return _IsValid;
}

double CSensorValue::Value() const
{
    return _Value;
}
