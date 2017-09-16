
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// A proportional / integral / derivative controller
    /// </summary>
    public class PIDController
    {
        #region Fields

        double _SetPoint;
        double _Error;
        double _PreviousError;
        double _Integral;
        double _Derivative;
        double _ProportionalConstant;
        double _IntegralConstant;
        double _DerivativeConstant;
        double _Output;

        #endregion

        #region Properties

        /// <summary>
        /// 
        /// </summary>
        public double SetPoint
        {
            get { return _SetPoint; }
            set { _SetPoint = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double ProportionalConstant
        {
            get { return _ProportionalConstant; }
            set { _ProportionalConstant = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double IntegralConstant
        {
            get { return _IntegralConstant; }
            set { _IntegralConstant = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double DerivativeConstant
        {
            get { return _DerivativeConstant; }
            set { _DerivativeConstant = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double Output
        {
            get { return _Output; }
            set { _Output = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// 
        /// </summary>
        /// <param name="NewProportional"></param>
        /// <param name="NewIntegral"></param>
        /// <param name="NewDerivative"></param>
        public PIDController(double NewProportional, double NewIntegral, double NewDerivative)
        {
            _ProportionalConstant = NewProportional;
            _IntegralConstant = NewIntegral;
            _DerivativeConstant = NewDerivative;

            Reset();
        }

        /// <summary>
        /// 
        /// </summary>
        public void Reset()
        {
            _SetPoint = 0;
            _Error = 0;
            _PreviousError = 0;
            _Integral = 0;
            _Derivative = 0;
            _Output = 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="CurrentValue"></param>
        /// <param name="DeltaTimeMillis"></param>
        public void Process(double CurrentValue, double DeltaTimeMillis)
        {
            // Calculate the difference between the desired value and the actual value
            _Error = _SetPoint - CurrentValue;

            // Track error over time, scaled to the timer interval
            _Integral = _Integral + (_Error * DeltaTimeMillis);

            // Determine the amount of change from the last time checked
            _Derivative = (_Error - _PreviousError) / DeltaTimeMillis;

            // Calculate how much drive the output in order to get to the desired setpoint. 
            _Output = (_ProportionalConstant * _Error) + (_IntegralConstant * _Integral) + (_DerivativeConstant * _Derivative);

            // Remember the error for the next time around.
            _PreviousError = _Error;
        }

        #endregion
    }
}
