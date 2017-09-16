
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// System values for an engine
    /// </summary>
    public class EngineSettings
    {
        #region Fields

        double _StallRPM;                           // RPM at which car will stall if clutch is fully engaged
        double _IdleRPM;                            // RPM at idle (no gear)
        double _MaxRPM;                             // Max RPM that controller allows
        double _BreakDownRPM;                       // RPM at which engine breaks down
        double _MaxTemperatureC;                    // Maximum engine temperature in normal usage
        double _BreakDownTemperatureC;              // Temperature at which engine breaks down
        double _MaxSpeedKMH;                        // Maximum speed of vehicle in normal usage
        double _ClutchContact;                      // Clutch contact point normalized (0 = full disengage, 1 = full engage)
        double _ClutchFullEngaged;                  // Normalized value at which clutch is fully engaged
        double _GasPedalEpsilon;                    // Value at which gas pedal is considered fully released
        double _StartupEndSpeedKMH;                 // Speed at which clutch is supposed to be fully engaged after startup

        public static double SpeedMSToRPS = 9.0;    // Factor used to convert speed to RPS
        public static double RPSToL = 0.0005;       // Factor used to convert RPM to Liters
        public static double WheelRadiusM = 0.4;

        #endregion

        #region Properties

        /// <summary>
        /// RPM at which engine stalls
        /// </summary>
        public double StallRPM
        {
            get { return _StallRPM; }
            set { _StallRPM = value; }
        }

        /// <summary>
        /// Idle RPM (gear at neutral, minimum gas injected)
        /// </summary>
        public double IdleRPM
        {
            get { return _IdleRPM; }
            set { _IdleRPM = value; }
        }

        /// <summary>
        /// Max RPM allowed
        /// </summary>
        public double MaxRPM
        {
            get { return _MaxRPM; }
            set { _MaxRPM = value; }
        }

        /// <summary>
        /// RPM at which engine breaks down
        /// </summary>
        public double BreakDownRPM
        {
            get { return _BreakDownRPM; }
            set { _BreakDownRPM = value; }
        }

        /// <summary>
        /// Max allowed engine temperature
        /// </summary>
        public double MaxTemperatureC
        {
            get { return _MaxTemperatureC; }
            set { _MaxTemperatureC = value; }
        }

        /// <summary>
        /// Temperature at which engines breaks down
        /// </summary>
        public double BreakDownTemperatureC
        {
            get { return _BreakDownTemperatureC; }
            set { _BreakDownTemperatureC = value; }
        }

        /// <summary>
        /// Maximum car speed
        /// </summary>
        public double MaxSpeedKMH
        {
            get { return _MaxSpeedKMH; }
            set { _MaxSpeedKMH = value; }
        }

        /// <summary>
        /// Point (from 0.0 to 1.0) at which clutch contacts
        /// </summary>
        public double ClutchContact
        {
            get { return _ClutchContact; }
            set { _ClutchContact = value; }
        }

        /// <summary>
        /// Point (from 0.0 to 1.0) at which clutch is fully engaged (max pressure)
        /// </summary>
        public double ClutchFullEngaged
        {
            get { return _ClutchFullEngaged; }
            set { _ClutchFullEngaged = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double GasPedalEpsilon
        {
            get { return _GasPedalEpsilon; }
            set { _GasPedalEpsilon = value; }
        }

        /// <summary>
        /// Speed at which clutch can be fully released in first gear
        /// </summary>
        public double StartupEndSpeedKMH
        {
            get { return _StartupEndSpeedKMH; }
            set { _StartupEndSpeedKMH = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// 
        /// </summary>
        public EngineSettings()
        {
            _StallRPM = 500.0;
            _IdleRPM = 800.0;
            _MaxRPM = 3000.0;
            _BreakDownRPM = 8000.0;
            _MaxTemperatureC = 90.0;
            _BreakDownTemperatureC = 120.0;
            _MaxSpeedKMH = 200.0;
            _ClutchContact = 0.3;
            _ClutchFullEngaged = 0.6;
            _GasPedalEpsilon = 0.02;
            _StartupEndSpeedKMH = 5.0;
        }

        #endregion
    }
}
