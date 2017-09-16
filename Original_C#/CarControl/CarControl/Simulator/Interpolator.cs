
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl.Simulator
{
    public class Interpolator
    {
        public class InterpolatorValue
        {
            double _Input;
            double _Output;

            /// <summary>
            /// 
            /// </summary>
            public double Input
            {
                get { return _Input; }
                set { _Input = value; }
            }

            /// <summary>
            /// 
            /// </summary>
            public double Output
            {
                get { return _Output; }
                set { _Output = value; }
            }

            /// <summary>
            /// 
            /// </summary>
            /// <param name="NewInput"></param>
            /// <param name="NewOutput"></param>
            public InterpolatorValue(double NewInput, double NewOutput)
            {
                _Input = NewInput;
                _Output = NewOutput;
            }

            /// <summary>
            /// 
            /// </summary>
            /// <param name="Target"></param>
            public InterpolatorValue(InterpolatorValue Target)
            {
                _Input = Target._Input;
                _Output = Target._Output;
            }
        }

        List<InterpolatorValue> _Values;
        int _LastIndex;
        Random _Rand;

        /// <summary>
        /// Constructor
        /// </summary>
        public Interpolator()
        {
            _Values = new List<InterpolatorValue>();
            _Rand = new Random(0);
            Reset();
        }

        /// <summary>
        /// Adds a value to this object
        /// </summary>
        /// <param name="NewValue"></param>
        public void AddValue(InterpolatorValue NewValue)
        {
            _Values.Add(NewValue);
        }

        /// <summary>
        /// Shifts all input values by some amount
        /// </summary>
        /// <param name="Amount"></param>
        public void Shift(double Amount)
        {
            for (int Index = 0; Index < _Values.Count; Index++)
            {
                _Values[Index].Input += Amount;
                if (_Values[Index].Input > 1.0)
                {
                    _Values.RemoveAt(Index);
                    Index--;
                }
            }
        }

        /// <summary>
        /// Scales all output values by some amount
        /// </summary>
        /// <param name="Amount"></param>
        public void Mult(double Amount)
        {
            foreach (InterpolatorValue LocalValue in _Values)
            {
                LocalValue.Output *= Amount;
            }
        }

        /// <summary>
        /// Randomizes values by some amount
        /// </summary>
        /// <param name="Amount"></param>
        public void Randomize(double Amount)
        {
            foreach (InterpolatorValue LocalValue in _Values)
            {
                LocalValue.Output *= ((_Rand.NextDouble() * 2.0) * Amount);
            }
        }

        /// <summary>
        /// Creates a deep clone of this object
        /// </summary>
        /// <returns></returns>
        public Interpolator Clone()
        {
            Interpolator NewInterpolator = new Interpolator();

            foreach (InterpolatorValue LocalValue in _Values)
            {
                NewInterpolator.AddValue(new InterpolatorValue(LocalValue));
            }

            return NewInterpolator;
        }

        /// <summary>
        /// Merges a Interpolator into this object
        /// </summary>
        /// <param name="Input"></param>
        public void Merge(Interpolator Input)
        {
            foreach (InterpolatorValue NewValue in Input._Values)
            {
                bool Found = false;

                foreach (InterpolatorValue LocalValue in _Values)
                {
                    if (LocalValue.Input == NewValue.Input)
                    {
                        LocalValue.Output += NewValue.Output;

                        if (LocalValue.Output < -1.0) LocalValue.Output = -1.0;
                        if (LocalValue.Output > 1.0) LocalValue.Output = 1.0;

                        Found = true;
                    }
                }

                if (Found == false)
                {
                    _Values.Add(NewValue);
                }
            }

            _Values.Sort(
                delegate(InterpolatorValue a, InterpolatorValue b)
                {
                    if (a.Input < b.Input) return -1;
                    if (a.Input > b.Input) return 1;
                    return 0;
                }
                );
        }

        public void Smooth()
        {
            for (int Index = 1; Index < _Values.Count - 1; Index++)
            {
                _Values[Index + 0].Output = (_Values[Index - 1].Output + _Values[Index + 0].Output + _Values[Index + 1].Output) / 3.0;
            }
        }

        /// <summary>
        /// Returns an interpolated value
        /// </summary>
        /// <param name="Value"></param>
        /// <returns></returns>
        public double InterpolateFromLast(double Value)
        {
            double ReturnValue = 0.0;

            if (_Values.Count == 0) return Value;

            if (Value < _Values[0].Input) Value = _Values[0].Input;
            if (Value > _Values[_Values.Count - 1].Input) Value = _Values[_Values.Count - 1].Input;

            for (int Index = _LastIndex; Index < _Values.Count; Index++)
            {
                if (Value >= _Values[Index].Input)
                {
                    if (_Values.Count > Index + 1)
                    {
                        if (Value < _Values[Index + 1].Input)
                        {
                            double Input1 = _Values[Index].Input;
                            double Input2 = _Values[Index + 1].Input;
                            double Output1 = _Values[Index].Output;
                            double Output2 = _Values[Index + 1].Output;
                            double InputRange = Input2 - Input1;
                            double OutputRange = Output2 - Output1;

                            ReturnValue = (Value - Input1) / InputRange;
                            ReturnValue = Output1 + (ReturnValue * OutputRange);

                            _LastIndex = Index;
                            break;
                        }
                    }
                    else
                    {
                        ReturnValue = _Values[Index].Output;
                    }
                }
            }

            return ReturnValue;
        }

        /// <summary>
        /// Returns an interpolated value
        /// </summary>
        /// <param name="Value"></param>
        /// <returns></returns>
        public double Interpolate(double Value)
        {
            Reset();
            return InterpolateFromLast(Value);
        }

        /// <summary>
        /// Resets the search index
        /// </summary>
        public void Reset()
        {
            _LastIndex = 0;
        }
    }
}
