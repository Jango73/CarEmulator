
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// This class provides a means of averaging a set of values
    /// </summary>
    class Averager
    {
        List<double> _Values;

        /// <summary>
        /// 
        /// </summary>
        public double Value
        {
            set
            {
                if (_Values.Count >= 4)
                {
                    _Values.RemoveAt(_Values.Count - 1);
                }

                _Values.Add(value);
            }

            get
            {
                if (_Values.Count > 0)
                {
                    double RetValue = 0.0;
                    foreach (double Val in _Values)
                    {
                        RetValue += Val;
                    }
                    return RetValue / (double)_Values.Count;
                }

                return 0;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public Averager()
        {
            _Values = new List<double>();
        }
    }
}
