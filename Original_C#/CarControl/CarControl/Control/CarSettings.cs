
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// Physical properties of car
    /// </summary>
    public class CarSettings
    {
        #region Fields

        double _WeightKG;

        #endregion

        #region Properties

        /// <summary>
        /// 
        /// </summary>
        public double WeightKG
        {
            get { return _WeightKG; }
            set { _WeightKG = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// 
        /// </summary>
        public CarSettings()
        {
            _WeightKG = 1200.0;
        }

        #endregion
    }
}
