
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Microsoft.Xna.Framework.Audio;

namespace CarControl.Simulator
{
    public class CarSimulator
    {
        #region Fields

        Car _Vehicle;
        NormalizedInput _ClutchLevel;
        Interpolator _TorqueTable;
        Random _Rand = new Random(0);

        Thread _EngineSoundThread;
        Interpolator _EngineSound;

        double _WheelRPS;
        double _EnginePowerRPS;

        #endregion

        #region Properties

        /// <summary>
        /// 
        /// </summary>
        public Car Vehicle
        {
            get { return _Vehicle; }
            set { _Vehicle = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public NormalizedInput ClutchLevel
        {
            get { return _ClutchLevel; }
            set { _ClutchLevel = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double WheelRPS
        {
            get { return _WheelRPS; }
            set { _WheelRPS = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double EnginePowerRPS
        {
            get { return _EnginePowerRPS; }
            set { _EnginePowerRPS = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="NewCar"></param>
        public CarSimulator(Car NewCar)
        {
            _Vehicle = NewCar;
            _ClutchLevel = new NormalizedInput();
            _TorqueTable = new Interpolator();
            _EngineSound = new Interpolator();

            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(0, 0.0));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(5, 0.4));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(10, 0.6));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(16, 1.0));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(45, 2.0));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(75, 2.5));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(103, 1.8));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(133, 0.4));
            _TorqueTable.AddValue(new Interpolator.InterpolatorValue(150, 0.0));

            /*
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.00, 0.0));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.05, 0.6));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.10, 0.8));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.15, 0.6));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.20, 0.2));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.25, 0.0));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.30, 0.4));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.35, 0.6));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.40, 0.1));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.45, 0.0));
             */

            /*
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.00, 0.0));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.05, 0.8));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.10, 0.3));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.15, 0.7));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.20, 0.2));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.25, 0.6));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.30, 0.1));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.35, 0.5));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.40, 0.0));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.45, 0.2));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.50, 0.0));
            */

            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.00,  0.0));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.05,  0.4));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.10, -0.1));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.15,  0.3));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.20, -0.2));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.25,  0.2));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.30, -0.3));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.35,  0.1));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.40, -0.4));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.45, -0.2));
            _EngineSound.AddValue(new Interpolator.InterpolatorValue(0.50,  0.0));

            Interpolator Temp1 = _EngineSound.Clone();
            //Interpolator Temp2 = _EngineSound.Clone();
            //Interpolator Temp3 = _EngineSound.Clone();

            Temp1.Shift(0.12);
            Temp1.Randomize(0.75);
            _EngineSound.Merge(Temp1);

            //Temp2.Shift(0.24);
            //Temp2.Randomize(0.75);
            //_EngineSound.Merge(Temp2);

            //Temp3.Shift(0.36);
            //Temp3.Randomize(0.75);
            //_EngineSound.Merge(Temp3);

            ParameterizedThreadStart strt = new ParameterizedThreadStart(EngineSoundThreadStart);
            _EngineSoundThread = new Thread(strt);
            _EngineSoundThread.Start();
        }

        /// <summary>
        /// This thread creates the engine sound in real time
        /// </summary>
        /// <param name="o"></param>
        void EngineSoundThreadStart(object o)
        {
            DynamicSoundEffectInstance _DynEngineSound;
            double _SoundCycleNormalizedPosition;
            List<double> _SoundNormalizedPosition;

            _SoundCycleNormalizedPosition = 0;
            _SoundNormalizedPosition = new List<double>();
            _DynEngineSound = new DynamicSoundEffectInstance(44100, AudioChannels.Stereo);
            _DynEngineSound.Play();

            int SamplesPerBuffer = 44100 / 10;
            int BytesPerSample = 2;
            double SampleRate = 44100.0;
            double BufferDurationS = (double)SamplesPerBuffer / SampleRate;

            byte[] buffer = new byte[SamplesPerBuffer * BytesPerSample * 2];

            while (true)
            {
                lock (_DynEngineSound)
                {
                    if (_DynEngineSound.PendingBufferCount < 3)
                    {
                        for (int BufferIndex = 0; BufferIndex < 1; BufferIndex++)
                        {
                            double EngineRPS = Utils.RPMToRPS(_Vehicle.Sensors.CurrentRPM.Value) * 1;
                            double BreakDownRPS = Utils.RPMToRPS(_Vehicle.EngineSettings.BreakDownRPM) * 1;
                            double EngineAccelRPSS = _Vehicle.Sensors.EngineAccelerationRPSS.Value * 1;
                            double CycleSecondsPerSample = BufferDurationS / SamplesPerBuffer;
                            double TimeS = 0.0;
                            int SoundDataIndex = 0;

                            for (int Index = 0; Index < SamplesPerBuffer; Index++)
                            {
                                double SamplesPerCycle = (1.0 / EngineRPS) * SampleRate;
                                double CycleDurationS = CycleSecondsPerSample * SamplesPerCycle;
                                double Value = 0.0;

                                _EngineSound.Reset();

                                for (int SoundIndex = 0; SoundIndex < _SoundNormalizedPosition.Count; SoundIndex += 2)
                                {
                                    if (_SoundNormalizedPosition[SoundIndex] < 1.0)
                                    {
                                        double SoundDurationS = _SoundNormalizedPosition[SoundIndex + 1];
                                        double AddValue = _EngineSound.Interpolate(_SoundNormalizedPosition[SoundIndex]);
                                        double NumSamplesForSound = SoundDurationS * SampleRate;
                                        double SoundSecondsPerSample = SoundDurationS / NumSamplesForSound;

                                        if (SoundIndex > 1) AddValue *= 0.75;

                                        Value += AddValue;

                                        _SoundNormalizedPosition[SoundIndex] += SoundSecondsPerSample / SoundDurationS;
                                    }

                                    if (_SoundNormalizedPosition[SoundIndex] >= 1.0)
                                    {
                                        _SoundNormalizedPosition.RemoveAt(SoundIndex);
                                        _SoundNormalizedPosition.RemoveAt(SoundIndex);
                                        SoundIndex -= 2;
                                    }
                                }

                                // Value *= 1.0 + (_Rand.NextDouble() / 20.0);

                                if (Value < -1.0) Value = -1.0;
                                if (Value > 1.0) Value = 1.0;

                                int SoundData = (int)(Value * 32767.0);

                                // Left
                                buffer[SoundDataIndex++] = (byte)((SoundData >> 0) & 0xFF);
                                buffer[SoundDataIndex++] = (byte)((SoundData >> 8) & 0xFF);

                                // Right
                                buffer[SoundDataIndex++] = (byte)((SoundData >> 0) & 0xFF);
                                buffer[SoundDataIndex++] = (byte)((SoundData >> 8) & 0xFF);

                                _SoundCycleNormalizedPosition += CycleSecondsPerSample / CycleDurationS;

                                if (_SoundCycleNormalizedPosition >= 1.0)
                                {
                                    _SoundCycleNormalizedPosition = 0.0;
                                    _SoundNormalizedPosition.Add(0.000);
                                    _SoundNormalizedPosition.Add(0.04 + (0.02 * (BreakDownRPS / EngineRPS)));
                                }

                                TimeS += CycleSecondsPerSample;
                                EngineRPS += EngineAccelRPSS * CycleSecondsPerSample;
                            }

                            _DynEngineSound.SubmitBuffer(buffer);
                        }
                    }
                }

                Thread.Sleep(5);
            }
        }

        /// <summary>
        /// Processes all simulated values (engine rpm, speed, temperature, etc...)
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        public void Process(double DeltaTimeMillis)
        {
            // Get parameters from settings and sensors
            double DeltaTimeSeconds = Utils.MillisToSeconds(DeltaTimeMillis);
            double EngineRPS = Utils.RPMToRPS(_Vehicle.Sensors.CurrentRPM.Value);
            double IdleEngineRPS = Utils.RPMToRPS(_Vehicle.EngineSettings.IdleRPM);
            double BreakDownRPS = Utils.RPMToRPS(_Vehicle.EngineSettings.BreakDownRPM);
            double CarSpeedMS = Utils.KMHToMS(_Vehicle.Sensors.CurrentSpeedKMH.Value);
            double ClutchRange = _Vehicle.EngineSettings.ClutchFullEngaged - _Vehicle.EngineSettings.ClutchContact;
            double GearRatio = _Vehicle.GearBox.CurrentRatio;
            double CurrentEngineTempC = _Vehicle.Sensors.CurrentEngineTempC.Value;
            double MaxTemperatureC = _Vehicle.EngineSettings.MaxTemperatureC;
            double BreakDownTemperatureC = _Vehicle.EngineSettings.BreakDownTemperatureC;
            double FuelLevelL = _Vehicle.Sensors.CurrentFuelLevelL.Value;

            // Compute the actual clutch level using contact point and full engage point
            _ClutchLevel.Value = (_Vehicle.ClutchPedal.Value - _Vehicle.EngineSettings.ClutchContact) / ClutchRange;

            // Compute fuel consumption
            double FuelGasFactor = _Vehicle.GasPedal.Value;
            if (FuelGasFactor < 0.05) FuelGasFactor = 0.05;

            // Compute torque transfer factor
            double TorqueTransferFactor = _ClutchLevel.Value;
            if (TorqueTransferFactor > 1.0) TorqueTransferFactor = 1.0;
            if (GearRatio == 0.0) TorqueTransferFactor = 0.0;

            // Bring car speed value up to RPM
            CarSpeedMS *= EngineSettings.SpeedMSToRPS;

            // Compute wheel circumference
            double WheelCircM = 2.0 * EngineSettings.WheelRadiusM * Math.PI;
            _WheelRPS = CarSpeedMS / WheelCircM;

            // Compute raw force produced by engine
            double RawEngineTorqueRPS = EngineRPS * FuelGasFactor;

            // Slow down the engine RPS using limit RPM
            RawEngineTorqueRPS = (RawEngineTorqueRPS * ((BreakDownRPS - RawEngineTorqueRPS) / BreakDownRPS)) * 4;

            double EngineDrag = ((BreakDownRPS - EngineRPS) / BreakDownRPS);

            // Apply the engine drag (reaching limit RPM) to the engine RPM
            EngineRPS += (((RawEngineTorqueRPS * (1 - TorqueTransferFactor)) * EngineDrag) * DeltaTimeSeconds) * 1.5;

            // Bring back engine to minimum RPS according to torque transfer factor and fuel flow
            double IdlePower = (EngineRPS - IdleEngineRPS) / (IdleEngineRPS / 15.0);

            EngineRPS -= ((IdlePower * (1.0 - TorqueTransferFactor) * (1.0 - FuelGasFactor)) * DeltaTimeSeconds) * 1.5;

            // Compute the force from the wheels applied to the engine by the clutch
            double WheelRPSToEngine = 0.0;

            if (GearRatio != 0.0)
            {
                WheelRPSToEngine = ((_WheelRPS - (EngineRPS / GearRatio)) * TorqueTransferFactor) * 8.0;
            }

            // Apply the wheel force to the engine
            EngineRPS += WheelRPSToEngine * DeltaTimeSeconds;

            if (EngineRPS < 0) EngineRPS = 0;
            if (EngineRPS > BreakDownRPS) EngineRPS = BreakDownRPS;

            // Compute the engine power
            _EnginePowerRPS = (_TorqueTable.Interpolate(EngineRPS) * 8) * FuelGasFactor;

            double CarSpeedDivider = CarSpeedMS * 0.05;
            if (CarSpeedDivider < 1.0) CarSpeedDivider = 1.0;

            // Add power to engine when starting up
            _EnginePowerRPS += (EngineRPS * (1.0 - TorqueTransferFactor)) / CarSpeedDivider;

            // Compute engine break
            // TODO

            // Compute acceleration
            double AccelRPS = _EnginePowerRPS * TorqueTransferFactor;

            // Compute car speed
            _WheelRPS += AccelRPS * DeltaTimeSeconds;

            // Check speed limits
            if (_WheelRPS < 0) _WheelRPS = 0;

            CarSpeedMS = _WheelRPS * WheelCircM;

            // Compute ground drag
            double GroundDrag = CarSpeedMS / -5000.0;
            if (GroundDrag > -2) GroundDrag = -2;

            // Compute air drag
            double AirDrag = (CarSpeedMS * CarSpeedMS) / -5000.0;
            if (AirDrag > -2) AirDrag = -2;

            // Compute total drag
            double TotalDrag = GroundDrag + AirDrag;

            // Add drags to speed
            CarSpeedMS += (TotalDrag * DeltaTimeSeconds);

            // Add break to speed
            CarSpeedMS += (_Vehicle.BreakPedal.Value * -60) * DeltaTimeSeconds;

            // Compute wheel RPS
            _WheelRPS = (CarSpeedMS / WheelCircM) / EngineSettings.SpeedMSToRPS;

            // Compute fuel consumption
            double FuelCons = (((TotalDrag * -1.0) + AccelRPS) * EngineSettings.RPSToL) * FuelGasFactor;

            FuelLevelL -= FuelCons * DeltaTimeSeconds;
            if (FuelLevelL < 0.0) FuelLevelL = 0.0;

            // Compute engine temperature
            double TemperatureChangeCS = ((EngineRPS / BreakDownRPS) * (EngineRPS / BreakDownRPS)) * 5;
            TemperatureChangeCS *= (BreakDownTemperatureC - CurrentEngineTempC) / BreakDownTemperatureC;

            CurrentEngineTempC += TemperatureChangeCS * DeltaTimeSeconds;

            // Compute engine cooling
            double EngineTemperatureCoolingCS = (CurrentEngineTempC - MaxTemperatureC) * 0.01;
            if (EngineTemperatureCoolingCS < 0.0) EngineTemperatureCoolingCS = 0.0;
            EngineTemperatureCoolingCS *= -1.0;

            CurrentEngineTempC += EngineTemperatureCoolingCS * DeltaTimeSeconds;

            // Compute natural temperature loss
            if (TemperatureChangeCS < 0.01)
            {
                CurrentEngineTempC -= 0.05 * DeltaTimeSeconds;
            }

            // Bring car speed value down from RPM
            CarSpeedMS /= EngineSettings.SpeedMSToRPS;

            // Assign new engine RPM
            _Vehicle.Sensors.CurrentRPM.Value = Utils.RPSToRPM(EngineRPS);

            // Assign new speed
            _Vehicle.Sensors.CurrentSpeedKMH.Value = Utils.MSToKMH(CarSpeedMS);

            // Assign new engine temperature
            _Vehicle.Sensors.CurrentEngineTempC.Value = CurrentEngineTempC;

            // Assign new fuel level
            _Vehicle.Sensors.CurrentFuelLevelL.Value = FuelLevelL;
        }

        #endregion
    }
}
