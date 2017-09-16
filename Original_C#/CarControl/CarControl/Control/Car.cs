
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// A car
    /// </summary>
    public class Car
    {
        #region Fields

        CarSettings _Settings;
        Sensors _Sensors;
        EngineSettings _EngineSettings;
        GearBox _GearBox;
        MainController _Controller;

        NormalizedInput _GasPedal;
        NormalizedInput _BreakPedal;
        NormalizedInput _ClutchPedal;

        #endregion

        #region Properties

        /// <summary>
        /// The physical properties of this car
        /// </summary>
        public CarSettings Settings
        {
            get { return _Settings; }
            set { _Settings = value; }
        }

        /// <summary>
        /// The sensors' input
        /// </summary>
        public Sensors Sensors
        {
            get { return _Sensors; }
            set { _Sensors = value; }
        }

        /// <summary>
        /// The physical properties of the engine
        /// </summary>
        public EngineSettings EngineSettings
        {
            get { return _EngineSettings; }
            set { _EngineSettings = value; }
        }

        /// <summary>
        /// An interface to the gear box
        /// </summary>
        public GearBox GearBox
        {
            get { return _GearBox; }
            set { _GearBox = value; }
        }

        /// <summary>
        /// The controller of this car
        /// </summary>
        public MainController Controller
        {
            get { return _Controller; }
            set { _Controller = value; }
        }

        /// <summary>
        /// The interface to the acceleration pedal
        /// </summary>
        public NormalizedInput GasPedal
        {
            get { return _GasPedal; }
            set { _GasPedal = value; }
        }

        /// <summary>
        /// The interface to the break pedal
        /// </summary>
        public NormalizedInput BreakPedal
        {
            get { return _BreakPedal; }
            set { _BreakPedal = value; }
        }

        /// <summary>
        /// The interface to the clutch pedal
        /// </summary>
        public NormalizedInput ClutchPedal
        {
            get { return _ClutchPedal; }
            set { _ClutchPedal = value; }
        }

        #endregion

        #region Methods

        /// <summary>
        /// Constructor
        /// </summary>
        public Car()
        {
            _Controller = new MainController(this);
            _Settings = new CarSettings();
            _Sensors = new Sensors();
            _EngineSettings = new EngineSettings();
            _GearBox = new GearBox();
            _GasPedal = new NormalizedInput();
            _BreakPedal = new NormalizedInput();
            _ClutchPedal = new NormalizedInput();
        }

        /// <summary>
        /// Do the work
        /// </summary>
        /// <param name="DeltaTimeMillis"></param>
        public void Process(double DeltaTimeMillis)
        {
            _Sensors.Process(DeltaTimeMillis);
            _Controller.Process(DeltaTimeMillis);
        }

        #endregion
    }
}
