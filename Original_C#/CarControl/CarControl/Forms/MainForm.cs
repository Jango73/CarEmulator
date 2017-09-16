
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Xna.Framework;

namespace CarControl.Forms
{
    public partial class MainForm : Form
    {
        System.Windows.Forms.Timer _FormTimer;
        System.Windows.Forms.Timer _ProcessTimer;
        System.Windows.Forms.Timer _XNATimer;
        Car _TheCar;
        Simulator.CarSimulator _TheSimulator;

        public MainForm()
        {
            InitializeComponent();

            FrameworkDispatcher.Update();

            _TheCar = new Car();
            _TheSimulator = new Simulator.CarSimulator(_TheCar);

            _FormTimer = new System.Windows.Forms.Timer();
            _FormTimer.Tick += new EventHandler(_FormTimer_Tick);
            _FormTimer.Interval = 30;
            _FormTimer.Start();

            _ProcessTimer = new System.Windows.Forms.Timer();
            _ProcessTimer.Tick += new EventHandler(_ProcessTimer_Tick);
            _ProcessTimer.Interval = 25;
            _ProcessTimer.Start();

            _XNATimer = new System.Windows.Forms.Timer();
            _XNATimer.Tick += new EventHandler(_XNATimer_Tick);
            _XNATimer.Interval = 500;
            _XNATimer.Start();

            CB_AutoClutch.Checked = true;
            CB_AutoGear.Checked = true;
            CB_AutoGas.Checked = true;
            CB_AutoBreak.Checked = true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void _FormTimer_Tick(object sender, EventArgs e)
        {
            Gauge_RPM.Value = _TheCar.Sensors.CurrentRPM.Value;
            Gauge_Speed.Value = _TheCar.Sensors.CurrentSpeedKMH.Value;
            Gauge_Temp.Value = _TheCar.Sensors.CurrentEngineTempC.Value;
            Gauge_Fuel.Value = _TheCar.Sensors.CurrentFuelLevelL.Value;

            Label_Gear.Text = _TheCar.GearBox.CurrentGear.ToString();
            Label_Acceleration.Text = String.Format("{0:0.00}", Utils.KMHToMS(_TheCar.Sensors.AccelerationKMHS.Value));
            Label_GLoad.Text = String.Format("{0:0.00}", Utils.MSSToG(Utils.KMHToMS(_TheCar.Sensors.AccelerationKMHS.Value)));
            Label_FuelCons.Text = String.Format("{0:0.0}", _TheCar.Sensors.FuelConsumptionL100KM.Value);
            Label_WheelRPS.Text = String.Format("{0:0.00}", _TheSimulator.WheelRPS);
            Label_EnginePower.Text = String.Format("{0:0.00}", _TheSimulator.EnginePowerRPS);

            Label_SpeedDemand.Text = String.Format("{0:0.00}", _TheCar.Controller.SpeedDemand * _TheCar.EngineSettings.MaxSpeedKMH);
            Label_AccelDemand.Text = _TheCar.Controller.AccelDemand.ToString();
            Label_State.Text = _TheCar.Controller.FunctionMode.ToString();

            if (CB_AutoClutch.Checked == true)
            {
                ClutchPedal.Value = (int)((1.0 - _TheCar.ClutchPedal.Value) * 100.0);
            }

            if (CB_AutoGas.Checked == true)
            {
                GasPedal.Value = (int)(_TheCar.GasPedal.Value * 100.0);
            }

            if (CB_AutoBreak.Checked == true)
            {
                BreakPedal.Value = (int)(_TheCar.BreakPedal.Value * 100.0);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void _ProcessTimer_Tick(object sender, EventArgs e)
        {
            _TheSimulator.Process(25);
            _TheCar.Process(25);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void _XNATimer_Tick(object sender, EventArgs e)
        {
            FrameworkDispatcher.Update();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ClutchPedal_Scroll(object sender, EventArgs e)
        {
            TrackBar Bar = (TrackBar)sender;

            if (CB_AutoClutch.Checked == false)
            {
                _TheCar.ClutchPedal.Value = 1.0 - ((double)(Bar.Value) / 100.0);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BreakPedal_Scroll(object sender, EventArgs e)
        {
            TrackBar Bar = (TrackBar)sender;
            _TheCar.BreakPedal.Value = (double)(Bar.Value) / 100.0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AccelPedal_Scroll(object sender, EventArgs e)
        {
            TrackBar Bar = (TrackBar)sender;
            _TheCar.GasPedal.Value = (double)(Bar.Value) / 100.0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SpeedDemand_Scroll(object sender, EventArgs e)
        {
            TrackBar Bar = (TrackBar)sender;
            _TheCar.Controller.SpeedDemand = (double)(Bar.Value) / 100.0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AccelDemand_Scroll(object sender, EventArgs e)
        {
            TrackBar Bar = (TrackBar)sender;
            _TheCar.Controller.AccelDemand = ((double)(Bar.Value - 50) * 2.0) / 100.0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_GearUp_Click(object sender, EventArgs e)
        {
            _TheCar.GearBox.CurrentGear++;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_GearDown_Click(object sender, EventArgs e)
        {
            _TheCar.GearBox.CurrentGear--;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CB_AutoClutch_CheckedChanged(object sender, EventArgs e)
        {
            _TheCar.Controller.AutoClutch = ((CheckBox)sender).Checked;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CB_AutoGear_CheckedChanged(object sender, EventArgs e)
        {
            _TheCar.Controller.AutoGear = ((CheckBox)sender).Checked;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CB_AutoGas_CheckedChanged(object sender, EventArgs e)
        {
            _TheCar.Controller.AutoGas = ((CheckBox)sender).Checked;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CB_AutoBreak_CheckedChanged(object sender, EventArgs e)
        {
            _TheCar.Controller.AutoBreak = ((CheckBox)sender).Checked;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CB_Disconnect_CheckedChanged(object sender, EventArgs e)
        {
            Boolean value = ((CheckBox)sender).Checked;

            CB_AutoClutch.Checked = value ? false : true;
            CB_AutoGear.Checked = value ? false : true;
            CB_AutoGas.Checked = value ? false : true;
            CB_AutoBreak.Checked = value ? false : true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BT_SimBreakDown_Click(object sender, EventArgs e)
        {
            _TheCar.Sensors.CurrentSpeedKMH.IsValid = false;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BT_Reset_Click(object sender, EventArgs e)
        {
            _TheCar.Controller.Reset();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainForm_SizeChanged(object sender, EventArgs e)
        {
        }
    }
}
