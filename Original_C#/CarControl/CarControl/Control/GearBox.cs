
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    public class GearBox
    {
        #region Fields

        int _NumGears;
        int _CurrentGear;
        int _TargetGear;
        double[] _Ratios;
        double[] _MaxSpeedKMH;
        double[] _MinSpeedKMH;
        System.Timers.Timer _Timer;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the number of gears
        /// </summary>
        public int NumGears
        {
            get { return _NumGears; }
            set { _NumGears = value; }
        }

        /// <summary>
        /// Gets or sets the current gear
        /// </summary>
        public int CurrentGear
        {
            get { return _CurrentGear; }
            set
            {
                _TargetGear = _CurrentGear = value;

                if (_CurrentGear < 0) _CurrentGear = 0;
                if (_TargetGear < 0) _TargetGear = 0;

                if (_CurrentGear >= _NumGears) _CurrentGear = _NumGears - 1;
                if (_TargetGear >= _NumGears) _TargetGear = _NumGears - 1;
            }
        }

        /// <summary>
        /// Gets or sets the target gear
        /// </summary>
        public int TargetGear
        {
            get { return _TargetGear; }
            set
            {
                _TargetGear = value;
                if (_TargetGear >= _NumGears) _TargetGear = _NumGears - 1;
            }
        }

        /// <summary>
        /// Gets the current gear ratio, for simulation
        /// </summary>
        public double CurrentRatio
        {
            get { return _Ratios[_CurrentGear]; }
        }

        /// <summary>
        /// Gets the maximum allowed speed for the current gear
        /// </summary>
        public double CurrentMaxSpeedKMH
        {
            get { return _MaxSpeedKMH[_CurrentGear]; }
        }

        /// <summary>
        /// Gets the minimum allowed speed for the current gear
        /// </summary>
        public double CurrentMinSpeedKMH
        {
            get { return _MinSpeedKMH[_CurrentGear]; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Initialize the class
        /// </summary>
        public GearBox()
        {
            _NumGears = 6;
            _CurrentGear = 0;
            _TargetGear = 0;
            _Ratios = new double[_NumGears];
            _MaxSpeedKMH = new double[_NumGears];
            _MinSpeedKMH = new double[_NumGears];

            _Ratios[0] = 0.0;
            _Ratios[1] = 2.20;
            _Ratios[2] = 1.20;
            _Ratios[3] = 0.75;
            _Ratios[4] = 0.60;
            _Ratios[5] = 0.50;

            _MaxSpeedKMH[0] = 0.0;
            _MaxSpeedKMH[1] = 10.0;
            _MaxSpeedKMH[2] = 25.0;
            _MaxSpeedKMH[3] = 45.0;
            _MaxSpeedKMH[4] = 65.0;
            _MaxSpeedKMH[5] = 200.0;

            _MinSpeedKMH[0] = 0.0;
            _MinSpeedKMH[1] = 5.0;
            _MinSpeedKMH[2] = 10.0;
            _MinSpeedKMH[3] = 20.0;
            _MinSpeedKMH[4] = 40.0;
            _MinSpeedKMH[5] = 60.0;

            _Timer = new System.Timers.Timer();
            _Timer.Interval = 1000;
            _Timer.Elapsed += new System.Timers.ElapsedEventHandler(_Timer_Elapsed);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void _Timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            _Timer.Stop();
            _CurrentGear = _TargetGear;
        }

        /// <summary>
        /// 
        /// </summary>
        public Boolean SetNeutralGear()
        {
            if (_CurrentGear != 0)
            {
                _TargetGear = 0;
                _Timer.Start();
            }
            return true;
        }

        /// <summary>
        /// Select highest gear
        /// </summary>
        public Boolean SetHighestGear()
        {
            if (_CurrentGear < _NumGears - 1)
            {
                _TargetGear = _NumGears - 1;
                _Timer.Start();
            }
            return true;
        }

        /// <summary>
        /// Shift gear up
        /// </summary>
        public Boolean Up()
        {
            if (_CurrentGear == _NumGears - 1) return false;
            _TargetGear = _CurrentGear + 1;
            _Timer.Start();
            return true;
        }

        /// <summary>
        /// Shift gear down
        /// </summary>
        public Boolean Down()
        {
            if (_CurrentGear == 0) return false;
            _TargetGear = _CurrentGear - 1;
            _Timer.Start();
            return true;
        }

        #endregion
    }
}
