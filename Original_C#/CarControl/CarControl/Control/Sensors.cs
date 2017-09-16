
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;
using System.Diagnostics;

namespace CarControl
{
    /// <summary>
    /// The real-time input values of the car
    /// </summary>
    public class Sensors
    {
        #region Fields

        SensorValue _CurrentRPM;                // Rounds per minute
        SensorValue _CurrentSpeedKMH;           // Kilometers per hour
        SensorValue _CurrentEngineTempC;        // Degrees celcius
        SensorValue _AccelerationKMHS;          // Kilometers per hour per second
        SensorValue _EngineAccelerationRPSS;    // Rounds per second per second
        SensorValue _CurrentFuelLevelL;         // Liters
        SensorValue _FuelConsumptionL100KM;     // Liters per second

        double _PreviousSpeedKMH;
        double _PreviousRPS;
        double _PreviousFuelLevelL;

        Stopwatch _FuelConsTimer;

        #endregion

        #region Properties

        /// <summary>
        /// Input value from the engine RPM sensor
        /// </summary>
        public SensorValue CurrentRPM
        {
            get { return _CurrentRPM; }
            set { _CurrentRPM = value; }
        }

        /// <summary>
        /// Input value from the car speed sensor
        /// </summary>
        public SensorValue CurrentSpeedKMH
        {
            get { return _CurrentSpeedKMH; }
            set { _CurrentSpeedKMH = value; }
        }

        /// <summary>
        /// Input value from the engine temperature sensor
        /// </summary>
        public SensorValue CurrentEngineTempC
        {
            get { return _CurrentEngineTempC; }
            set { _CurrentEngineTempC = value; }
        }

        /// <summary>
        /// Commputed acceleration value
        /// </summary>
        public SensorValue AccelerationKMHS
        {
            get { return _AccelerationKMHS; }
            set { _AccelerationKMHS = value; }
        }

        /// <summary>
        /// Computed engine RPM acceleration in rounds per second per second
        /// </summary>
        public SensorValue EngineAccelerationRPSS
        {
            get { return _EngineAccelerationRPSS; }
            set { _EngineAccelerationRPSS = value; }
        }

        /// <summary>
        /// Input value from the fuel level sensor
        /// </summary>
        public SensorValue CurrentFuelLevelL
        {
            get { return _CurrentFuelLevelL; }
            set { _CurrentFuelLevelL = value; }
        }

        /// <summary>
        /// Computed value of fuel consumption in liters per hundred kilometers
        /// </summary>
        public SensorValue FuelConsumptionL100KM
        {
            get { return _FuelConsumptionL100KM; }
            set { _FuelConsumptionL100KM = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// 
        /// </summary>
        public Sensors()
        {
            _FuelConsTimer = new Stopwatch();
            _CurrentRPM = new SensorValue(800.0);
            _CurrentSpeedKMH = new SensorValue(0.0);
            _CurrentEngineTempC = new SensorValue(80.0);
            _AccelerationKMHS = new SensorValue(0.0);
            _EngineAccelerationRPSS = new SensorValue(0.0);
            _CurrentFuelLevelL = new SensorValue(60.0);
            _FuelConsumptionL100KM = new SensorValue(0.0);
            _PreviousSpeedKMH = 0.0;
            _PreviousRPS = 0.0;
            _PreviousFuelLevelL = 0.0;
            _FuelConsTimer.Start();
        }

        /// <summary>
        /// Do the work
        /// </summary>
        public void Process(double DeltaTimeMillis)
        {
            // Compute acceleration
            double SpeedDiffKMH = _CurrentSpeedKMH.Value - _PreviousSpeedKMH;

            if (Math.Abs(SpeedDiffKMH) < 0.0001)
            {
                _AccelerationKMHS.Value = 0.0;
            }
            else
            {
                _AccelerationKMHS.Value = SpeedDiffKMH / (DeltaTimeMillis / 1000.0);
            }

            // Compute engine acceleration
            double EngineDiffRPS = Utils.RPMToRPS(_CurrentRPM.Value) - _PreviousRPS;

            if (Math.Abs(EngineDiffRPS) < 0.0001)
            {
                _EngineAccelerationRPSS.Value = 0.0;
            }
            else
            {
                _EngineAccelerationRPSS.Value = EngineDiffRPS / (DeltaTimeMillis / 1000.0);
            }

            // Compute fuel consumption

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

            _PreviousSpeedKMH = _CurrentSpeedKMH.Value;
            _PreviousRPS = Utils.RPMToRPS(_CurrentRPM.Value);
        }

        #endregion
    }
}
