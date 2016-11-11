
#include "CSensors.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CSensors::CSensors()
    : _CurrentRPM(CSensorValue(800.0))
    , _CurrentSpeedKMH(CSensorValue(0.0))
    , _CurrentEngineTempC(CSensorValue(80.0))
    , _AccelerationKMHS(CSensorValue(0.0))
    , _EngineAccelerationRPSS(CSensorValue(0.0))
    , _CurrentFuelLevelL(CSensorValue(60.0))
    , _FuelConsumptionL100KM(CSensorValue(0.0))
{
}

CSensors::~CSensors()
{
}

CSensorValue& CSensors::CurrentRPM()
{
    return _CurrentRPM;
}

CSensorValue& CSensors::CurrentSpeedKMH()
{
    return _CurrentSpeedKMH;
}

CSensorValue& CSensors::CurrentEngineTempC()
{
    return _CurrentEngineTempC;
}

CSensorValue& CSensors::AccelerationKMHS()
{
    return _AccelerationKMHS;
}

CSensorValue& CSensors::EngineAccelerationRPSS()
{
    return _EngineAccelerationRPSS;
}

CSensorValue& CSensors::CurrentFuelLevelL()
{
    return _CurrentFuelLevelL;
}

CSensorValue& CSensors::FuelConsumptionL100KM()
{
    return _FuelConsumptionL100KM;
}

void CSensors::Process(double DeltaTimeMillis)
{
    // Compute acceleration
    double SpeedDiffKMH = _CurrentSpeedKMH.Value() - _PreviousSpeedKMH;

    if (abs(SpeedDiffKMH) < 0.0001)
    {
        _AccelerationKMHS.setValue(0.0);
    }
    else
    {
        _AccelerationKMHS.setValue(SpeedDiffKMH / (DeltaTimeMillis / 1000.0));
    }

    // Compute engine acceleration
    double EngineDiffRPS = CUtils::RPMToRPS(_CurrentRPM.Value()) - _PreviousRPS;

    if (abs(EngineDiffRPS) < 0.0001)
    {
        _EngineAccelerationRPSS.setValue(0.0);
    }
    else
    {
        _EngineAccelerationRPSS.setValue(EngineDiffRPS / (DeltaTimeMillis / 1000.0));
    }

    // Compute fuel consumption

    /*
    if (_FuelConsTimer.ElapsedMilliseconds > 1000)
    {
        _FuelConsTimer.Stop();

        double FuelDiff = _CurrentFuelLevelL.Value - _PreviousFuelLevelL;
        _PreviousFuelLevelL = _CurrentFuelLevelL.Value;

        if (_CurrentSpeedKMH.Value > 3.0)
        {
            double FuelConsumptionLS = (FuelDiff * ((double) _FuelConsTimer.ElapsedMilliseconds / 1000.0)) * -1.0;
            // _FuelConsumptionL100KM.Value = FuelConsumptionLS;
            double _SecondsFor100KM = Utils.HoursToSeconds(100.0 / _CurrentSpeedKMH.Value);
            _FuelConsumptionL100KM.Value = FuelConsumptionLS * _SecondsFor100KM;
        }
        else
        {
            _FuelConsumptionL100KM.Value = 0.0;
        }

        _FuelConsTimer.Restart();
    }
    */

    _PreviousSpeedKMH = _CurrentSpeedKMH.Value();
    _PreviousRPS = CUtils::RPMToRPS(_CurrentRPM.Value());
}
