
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// Main controller of clutch pedal, break pedal, acceleration pedal and gear box in a car
    /// </summary>
    public class MainController
    {
        #region Enumerations

        public enum EFunctionMode
        {
            Nominal,        // All inputs OK
            Degraded,       // Only speed is OK
            Breakdown       // Speed input is lost or hardware does not respond
        }

        public enum EAccelerationBehavior
        {
            Slow,
            Normal,
            Fast
        }

        #endregion

        #region Fields

        Car _Vehicle;
        EFunctionMode _FunctionMode;
        EAccelerationBehavior _AccelerationBehavior;

        Boolean _AutoClutch;
        Boolean _AutoGear;
        Boolean _AutoGas;
        Boolean _AutoBreak;

        double _SpeedDemand;
        double _AccelDemand;

        PIDController _ClutchControl;
        PIDController _AccelControl;

        Averager _ClutchAverager;
        Averager _AccelAverager;

        #endregion

        #region Properties

        /// <summary>
        /// The vehicle this controller controls
        /// </summary>
        public Car Vehicle
        {
            get { return _Vehicle; }
            set { _Vehicle = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public EFunctionMode FunctionMode
        {
            get { return _FunctionMode; }
            set { _FunctionMode = value; }
        }

        /// <summary>
        /// How this controller accelerates
        /// </summary>
        public EAccelerationBehavior AccelerationBehavior
        {
            get { return _AccelerationBehavior; }
            set { _AccelerationBehavior = value; }
        }

        /// <summary>
        /// Is auto-clutch enabled?
        /// </summary>
        public Boolean AutoClutch
        {
            get { return _AutoClutch; }
            set { _AutoClutch = value; }
        }

        /// <summary>
        /// Is auto-gear enabled?
        /// </summary>
        public Boolean AutoGear
        {
            get { return _AutoGear; }
            set { _AutoGear = value; }
        }

        /// <summary>
        /// Is auto-acceleration enabled?
        /// </summary>
        public Boolean AutoGas
        {
            get { return _AutoGas; }
            set { _AutoGas = value; }
        }

        /// <summary>
        /// Is auto-break enabled?
        /// </summary>
        public Boolean AutoBreak
        {
            get { return _AutoBreak; }
            set { _AutoBreak = value; }
        }

        /// <summary>
        /// This value ranges from 0.0 to 1.0 where 1.0 stands for max car speed
        /// </summary>
        public double SpeedDemand
        {
            get { return _SpeedDemand; }
            set { _SpeedDemand = value; }
        }

        /// <summary>
        /// This value ranges from 0.0 to 1.0 where 1.0 stands for 15 km/h/s
        /// </summary>
        public double AccelDemand
        {
            get { return _AccelDemand; }
            set { _AccelDemand = value; }
        }

        /// <summary>
        /// This PID controls clutch position
        /// </summary>
        public PIDController ClutchControl
        {
            get { return _ClutchControl; }
            set { _ClutchControl = value; }
        }

        /// <summary>
        /// This PID controls acceleration pedal position
        /// </summary>
        public PIDController AccelControl
        {
            get { return _AccelControl; }
            set { _AccelControl = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Initialize the class
        /// </summary>
        public MainController(Car NewVehicle)
        {
            _Vehicle = NewVehicle;
            _FunctionMode = EFunctionMode.Nominal;
            _AccelerationBehavior = EAccelerationBehavior.Normal;

            _AutoClutch = true;
            _AutoGear = true;
            _AutoGas = true;
            _AutoBreak = true;

            _SpeedDemand = 0.0;
            _AccelDemand = 0.0;

            _ClutchControl = new PIDController(1.0, 0.005, 0.05);
            _AccelControl = new PIDController(0.9, 0.008, 0.2);

            _ClutchAverager = new Averager();
            _AccelAverager = new Averager();
        }

        /// <summary>
        /// Reset the controller
        /// </summary>
        public void Reset()
        {
            _FunctionMode = EFunctionMode.Nominal;

            _Vehicle.Sensors.CurrentSpeedKMH.IsValid = true;
            _Vehicle.Sensors.CurrentRPM.IsValid = true;
        }

        /// <summary>
        /// Chain all control processing
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        public void Process(double DeltaTimeMillis)
        {
            ProcessFailures(DeltaTimeMillis);
            ProcessAutoClutch(DeltaTimeMillis);
            ProcessAutoGear(DeltaTimeMillis);
            ProcessAutoGas(DeltaTimeMillis);
        }

        /// <summary>
        /// Process system failures
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        protected void ProcessFailures(double DeltaTimeMillis)
        {
            // Check essentials inputs

            if (_Vehicle.Sensors.CurrentRPM.IsValid == false || _Vehicle.Sensors.CurrentSpeedKMH.IsValid == false)
            {
                // Here we might have corrupted input
                // Only solution is to disconnect the system

                _FunctionMode = EFunctionMode.Breakdown;
            }
        }

        /// <summary>
        /// Process clutch control
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        protected void ProcessAutoClutch(double DeltaTimeMillis)
        {
            if (_FunctionMode == EFunctionMode.Breakdown)
            {
                _Vehicle.ClutchPedal.Release();
                return;
            }

            // Case where auto-clutch is active in nominal mode

            if (_FunctionMode == EFunctionMode.Nominal && _AutoClutch)
            {
                // Case where the gear is the one we asked for

                if (_Vehicle.GearBox.CurrentGear == _Vehicle.GearBox.TargetGear)
                {
                    // Case where the car speed is less than the end of startup speed (i.e speed at which clutch is fully engaged)

                    if (_Vehicle.Sensors.CurrentSpeedKMH.Value < _Vehicle.EngineSettings.StartupEndSpeedKMH)
                    {
                        // Get the car speed and scale it to RPM

                        double CarSpeedMS = Utils.KMHToMS(_Vehicle.Sensors.CurrentSpeedKMH.Value);
                        CarSpeedMS *= EngineSettings.SpeedMSToRPS;

                        // Compute the target RPM

                        double TargetRPM = _Vehicle.EngineSettings.IdleRPM + ((_Vehicle.EngineSettings.MaxRPM / 10.0) * _Vehicle.GasPedal.Value);
                        // double TargetRPM = _Vehicle.EngineSettings.IdleRPM;

                        // Process with the controller

                        _ClutchControl.SetPoint = TargetRPM;
                        _ClutchControl.Process((_Vehicle.Sensors.CurrentRPM.Value - CarSpeedMS), DeltaTimeMillis);

                        // Case where the gas pedal is released

                        if (_Vehicle.GasPedal.Value < _Vehicle.EngineSettings.GasPedalEpsilon)
                        {
                            // If we are in neutral gear, fully engage the clutch and reset the controller

                            if (_Vehicle.GearBox.CurrentGear == 0)
                            {
                                _Vehicle.ClutchPedal.Value = 1.0;
                                _ClutchControl.Reset();
                            }
                            else // else fully disengage the clutch and reset the controller
                            {
                                _Vehicle.ClutchPedal.Value = 0.0;
                                _ClutchControl.Reset();
                            }
                        }
                        else // else apply output of controller to clutch, using scale factor
                        {
                            _Vehicle.ClutchPedal.Value =
                                _Vehicle.EngineSettings.ClutchContact +
                                (_ClutchControl.Output / (_Vehicle.EngineSettings.BreakDownRPM * -1));
                        }
                    }
                    else // else we are driving, fully engage the clutch and reset the controller
                    {
                        _Vehicle.ClutchPedal.Value = 1.0;
                        _ClutchControl.Reset();
                    }
                }
                else // else we are in a gear shift sequence, fully disengage the clutch and reset the controller
                {
                    if (_Vehicle.GearBox.CurrentGear > 0 || _Vehicle.GearBox.TargetGear > 0)
                    {
                        _Vehicle.ClutchPedal.Value = 0.0;
                        _ClutchControl.Reset();
                    }
                }
            }
        }

        /// <summary>
        /// Process gear control
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        protected void ProcessAutoGear(double DeltaTimeMillis)
        {
            if (_FunctionMode == EFunctionMode.Breakdown)
            {
                // _Vehicle.GearBox.SetHighestGear();
                return;
            }

            // Case where auto-gear is active in nominal mode
            // Auto-clutch must also be active

            if (_FunctionMode == EFunctionMode.Nominal && _AutoGear && _AutoClutch)
            {
                // Case where the current gear is the one we asked for and the clutch is fully engaged

                if (_Vehicle.GearBox.CurrentGear == _Vehicle.GearBox.TargetGear && _Vehicle.ClutchPedal.Value > 0.95)
                {
                    // Case where the driver applies pressure to the gas pedal

                    if (_Vehicle.GasPedal.Value >= _Vehicle.EngineSettings.GasPedalEpsilon)
                    {
                        double MaxSpeedMultplier = 10.0;

                        if (_AccelerationBehavior == EAccelerationBehavior.Normal)
                        {
                            MaxSpeedMultplier = 15.0;
                        }
                        else if (_AccelerationBehavior == EAccelerationBehavior.Fast)
                        {
                            MaxSpeedMultplier = 25.0;
                        }

                        double MaxSpeedKMH = _Vehicle.GearBox.CurrentMaxSpeedKMH + (MaxSpeedMultplier * _Vehicle.GasPedal.Value);

                        if (_Vehicle.Sensors.CurrentSpeedKMH.Value > MaxSpeedKMH)
                        {
                            _Vehicle.GearBox.Up();
                        }
                    }
                    else
                    {
                        if (_Vehicle.Sensors.CurrentSpeedKMH.Value < _Vehicle.GearBox.CurrentMinSpeedKMH)
                        {
                            _Vehicle.GearBox.Down();
                        }
                    }
                }
                else
                {
                    // Case where the car's speed is less than the end of startup speed, i.e. car is moving too slow

                    if (_Vehicle.Sensors.CurrentSpeedKMH.Value < _Vehicle.EngineSettings.StartupEndSpeedKMH)
                    {
                        // Case where the driver applies pressure to the gas pedal

                        if (_Vehicle.GasPedal.Value >= _Vehicle.EngineSettings.GasPedalEpsilon)
                        {
                            // If gear is neutral, then bring gear up

                            if (_Vehicle.GearBox.CurrentGear < 1) _Vehicle.GearBox.Up();
                        }
                        else // No gas pedal pressure, bring gear down to reach neutral
                        {
                            _Vehicle.GearBox.Down();
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Process gas control
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        protected void ProcessAutoGas(double DeltaTimeMillis)
        {
            if (_FunctionMode == EFunctionMode.Breakdown)
            {
                _Vehicle.GasPedal.Release();
                return;
            }

            // Case where auto-gas is active in nominal mode
            // Auto-clutch and auto-gear must also be active

            if (_FunctionMode == EFunctionMode.Nominal && _AutoGas && _AutoGear && _AutoClutch)
            {
                double CarSpeedMS = Utils.KMHToMS(_Vehicle.Sensors.CurrentSpeedKMH.Value);
                double TargetSpeedMS = Utils.KMHToMS(_SpeedDemand * _Vehicle.EngineSettings.MaxSpeedKMH);
                double CarAccelerationMSS = Utils.KMHToMS(_Vehicle.Sensors.AccelerationKMHS.Value);
                double TargetAccelerationMSS = TargetSpeedMS - CarSpeedMS;
                Boolean ServingSpeed = true;

                // Case where there is an acceleration demand

                if (_AccelDemand != 0.0)
                {
                    ServingSpeed = false;

                    // Target speed becomes current speed

                    _SpeedDemand = _Vehicle.Sensors.CurrentSpeedKMH.Value / _Vehicle.EngineSettings.MaxSpeedKMH;

                    TargetAccelerationMSS = _AccelDemand * Utils.KMHToMS(15.0);
                }
                else
                {
                    double ClipAcceleration = 1.0;

                    if (_AccelerationBehavior == EAccelerationBehavior.Normal)
                    {
                        ClipAcceleration = 1.5;
                    }
                    else if (_AccelerationBehavior == EAccelerationBehavior.Fast)
                    {
                        ClipAcceleration = 3.0;
                    }

                    // In case we decelerate, clip is more gentle

                    if (TargetAccelerationMSS < 0.0) ClipAcceleration *= 0.5;

                    // Clip the target acceleration to some acceptable values

                    if (TargetAccelerationMSS > ClipAcceleration) TargetAccelerationMSS = ClipAcceleration;
                    if (TargetAccelerationMSS < -ClipAcceleration) TargetAccelerationMSS = -ClipAcceleration;
                }

                // Case where the speed demand, accel demand and car's speed are very low

                if (_SpeedDemand < 0.05 && _AccelDemand < 0.05 && _Vehicle.Sensors.CurrentSpeedKMH.Value < 3.0)
                {
                    // Fully disengage the gas pedal and reset the controller

                    _Vehicle.GasPedal.Value = 0.0;
                    _AccelControl.Reset();

                    // Apply parking breaks

                    if (_AutoBreak)
                    {
                        _Vehicle.BreakPedal.Value = 0.5;
                    }
                }
                else
                {
                    // Case where the gear is neutral

                    if (_Vehicle.GearBox.CurrentGear == 0)
                    {
                        // Apply little pressure to gas in order to activate the startup sequence
                        // Reset the controller

                        _Vehicle.GasPedal.Value = _Vehicle.EngineSettings.GasPedalEpsilon * 4;
                        _AccelControl.Reset();
                    }

                    // Case where the clutch is disengaged (not necessarily fully)

                    else if (_Vehicle.ClutchPedal.Value <= _Vehicle.EngineSettings.ClutchContact)
                    {
                        // Bring gas fully down

                        _Vehicle.GasPedal.Value = 0.0;

                        if (TargetSpeedMS < CarSpeedMS)
                        {
                            // _AccelControl.Reset();
                        }
                    }

                    // All other cases

                    else
                    {
                        _AccelControl.SetPoint = TargetAccelerationMSS;
                        _AccelControl.Process(CarAccelerationMSS, DeltaTimeMillis);

                        _AccelAverager.Value = _AccelControl.Output;

                        double GasPedalValue = (_AccelAverager.Value / (5));
                        double BreakPedalValue = GasPedalValue * -1.5;

                        // In case of extreme deceleration demand, push hard on brakes

                        if (_AccelDemand < -0.9)
                        {
                            BreakPedalValue = 1.0;
                            GasPedalValue = 0.0;
                        }

                        // In case no acceleration demand is done, limit gas pedal position

                        if (ServingSpeed)
                        {
                            // Choose a gas clip value according to acceleration behavior

                            double GasClip = 0.4;

                            if (_AccelerationBehavior == EAccelerationBehavior.Normal)
                            {
                                GasClip = 0.6;
                            }
                            else if (_AccelerationBehavior == EAccelerationBehavior.Fast)
                            {
                                GasClip = 1.0;
                            }

                            if (GasPedalValue > GasClip) GasPedalValue = GasClip;

                            if (TargetSpeedMS <= CarSpeedMS && GasPedalValue > 0.95)
                            {
                                _AccelControl.Reset();
                            }
                        }
                        else
                        {
                            if (_AccelDemand <= 0.0 && GasPedalValue > 0.95)
                            {
                                _AccelControl.Reset();
                            }
                        }

                        if (BreakPedalValue < 0.0) BreakPedalValue = 0.0;

                        // Assign gas value to pedal controller

                        _Vehicle.GasPedal.Value = GasPedalValue;

                        // Check if breaking is needed
                        // Executed only if auto-break is enabled

                        if (_AutoBreak)
                        {
                            // Assign break value to pedal controller

                            _Vehicle.BreakPedal.Value = BreakPedalValue;
                        }
                    }
                }
            }
        }

        #endregion
    }
}
