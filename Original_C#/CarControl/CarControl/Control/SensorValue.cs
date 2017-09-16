
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// A value set by a sensor
    /// </summary>
    public class SensorValue
    {
        Boolean _IsValid;
        double _Value;

        /// <summary>
        /// Is the value valid?
        /// </summary>
        public Boolean IsValid
        {
            get { return _IsValid; }
            set { _IsValid = value; }
        }

        /// <summary>
        /// The value
        /// </summary>
        public double Value
        {
            get { return _Value; }
            set { _Value = value; }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public SensorValue(double NewValue)
        {
            _IsValid = true;
            _Value = NewValue;
        }
    }
}
