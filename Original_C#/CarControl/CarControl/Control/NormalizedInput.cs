
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// This object is a normalized value container, i.e. ranging from 0.0 to 1.0
    /// </summary>
    public class NormalizedInput
    {
        Boolean _Released;
        double _Value;

        /// <summary>
        /// 
        /// </summary>
        public double Value
        {
            get { return _Value; }
            set
            {
                if (_Released == false)
                {
                    _Value = value;

                    if (_Value < 0.0) _Value = 0.0;
                    if (_Value > 1.0) _Value = 1.0;
                }
            }
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public NormalizedInput()
        {
            _Released = false;
            _Value = 0.0;
        }

        /// <summary>
        /// Tell hardware to release pressure
        /// </summary>
        public void Release()
        {
            _Released = true;
        }
    }
}
