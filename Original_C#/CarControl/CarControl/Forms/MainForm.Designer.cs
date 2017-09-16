namespace CarControl.Forms
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MainSplit = new System.Windows.Forms.SplitContainer();
            this.DisplayLayout = new System.Windows.Forms.TableLayoutPanel();
            this.Gauge_RPM = new CarControl.Forms.AnalogGauge();
            this.Gauge_Speed = new CarControl.Forms.AnalogGauge();
            this.BT_SimBreakDown = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.SpeedDemand = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.AccelDemand = new System.Windows.Forms.TrackBar();
            this.CB_AutoClutch = new System.Windows.Forms.CheckBox();
            this.CB_AutoGear = new System.Windows.Forms.CheckBox();
            this.CB_AutoGas = new System.Windows.Forms.CheckBox();
            this.CB_AutoBreak = new System.Windows.Forms.CheckBox();
            this.Label_SpeedDemand = new System.Windows.Forms.Label();
            this.Label_AccelDemand = new System.Windows.Forms.Label();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.label7 = new System.Windows.Forms.Label();
            this.Label_State = new System.Windows.Forms.Label();
            this.Gauge_Temp = new CarControl.Forms.AnalogGauge();
            this.Gauge_Fuel = new CarControl.Forms.AnalogGauge();
            this.BT_Reset = new System.Windows.Forms.Button();
            this.CB_Disconnect = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Label_Acceleration = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.Label_GLoad = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Label_FuelCons = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.Label_WheelRPS = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.Label_EnginePower = new System.Windows.Forms.Label();
            this.ControlsSplit = new System.Windows.Forms.SplitContainer();
            this.ControlsLayout = new System.Windows.Forms.TableLayoutPanel();
            this.ClutchPedal = new System.Windows.Forms.TrackBar();
            this.GasPedal = new System.Windows.Forms.TrackBar();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.Label_Gear = new System.Windows.Forms.Label();
            this.Button_GearUp = new System.Windows.Forms.Button();
            this.Button_GearDown = new System.Windows.Forms.Button();
            this.BreakPedal = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.MainSplit)).BeginInit();
            this.MainSplit.Panel1.SuspendLayout();
            this.MainSplit.Panel2.SuspendLayout();
            this.MainSplit.SuspendLayout();
            this.DisplayLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedDemand)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AccelDemand)).BeginInit();
            this.flowLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ControlsSplit)).BeginInit();
            this.ControlsSplit.Panel1.SuspendLayout();
            this.ControlsSplit.SuspendLayout();
            this.ControlsLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ClutchPedal)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GasPedal)).BeginInit();
            this.flowLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BreakPedal)).BeginInit();
            this.SuspendLayout();
            // 
            // MainSplit
            // 
            this.MainSplit.Dock = System.Windows.Forms.DockStyle.Fill;
            this.MainSplit.Location = new System.Drawing.Point(0, 0);
            this.MainSplit.Name = "MainSplit";
            // 
            // MainSplit.Panel1
            // 
            this.MainSplit.Panel1.Controls.Add(this.DisplayLayout);
            // 
            // MainSplit.Panel2
            // 
            this.MainSplit.Panel2.Controls.Add(this.ControlsSplit);
            this.MainSplit.Size = new System.Drawing.Size(990, 568);
            this.MainSplit.SplitterDistance = 703;
            this.MainSplit.TabIndex = 0;
            // 
            // DisplayLayout
            // 
            this.DisplayLayout.ColumnCount = 3;
            this.DisplayLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 280F));
            this.DisplayLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 280F));
            this.DisplayLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.DisplayLayout.Controls.Add(this.Gauge_RPM, 0, 0);
            this.DisplayLayout.Controls.Add(this.Gauge_Speed, 1, 0);
            this.DisplayLayout.Controls.Add(this.BT_SimBreakDown, 2, 7);
            this.DisplayLayout.Controls.Add(this.label2, 0, 1);
            this.DisplayLayout.Controls.Add(this.SpeedDemand, 1, 1);
            this.DisplayLayout.Controls.Add(this.label4, 0, 2);
            this.DisplayLayout.Controls.Add(this.AccelDemand, 1, 2);
            this.DisplayLayout.Controls.Add(this.CB_AutoClutch, 2, 3);
            this.DisplayLayout.Controls.Add(this.CB_AutoGear, 2, 4);
            this.DisplayLayout.Controls.Add(this.CB_AutoGas, 2, 5);
            this.DisplayLayout.Controls.Add(this.CB_AutoBreak, 2, 6);
            this.DisplayLayout.Controls.Add(this.Label_SpeedDemand, 2, 1);
            this.DisplayLayout.Controls.Add(this.Label_AccelDemand, 2, 2);
            this.DisplayLayout.Controls.Add(this.flowLayoutPanel2, 2, 0);
            this.DisplayLayout.Controls.Add(this.BT_Reset, 2, 8);
            this.DisplayLayout.Controls.Add(this.CB_Disconnect, 0, 3);
            this.DisplayLayout.Controls.Add(this.label1, 0, 4);
            this.DisplayLayout.Controls.Add(this.Label_Acceleration, 1, 4);
            this.DisplayLayout.Controls.Add(this.label6, 0, 5);
            this.DisplayLayout.Controls.Add(this.Label_GLoad, 1, 5);
            this.DisplayLayout.Controls.Add(this.label3, 0, 6);
            this.DisplayLayout.Controls.Add(this.Label_FuelCons, 1, 6);
            this.DisplayLayout.Controls.Add(this.label5, 0, 7);
            this.DisplayLayout.Controls.Add(this.Label_WheelRPS, 1, 7);
            this.DisplayLayout.Controls.Add(this.label8, 0, 8);
            this.DisplayLayout.Controls.Add(this.Label_EnginePower, 1, 8);
            this.DisplayLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.DisplayLayout.Location = new System.Drawing.Point(0, 0);
            this.DisplayLayout.Name = "DisplayLayout";
            this.DisplayLayout.RowCount = 10;
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 280F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.DisplayLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.DisplayLayout.Size = new System.Drawing.Size(703, 568);
            this.DisplayLayout.TabIndex = 0;
            // 
            // Gauge_RPM
            // 
            this.Gauge_RPM.DangerZone = 7000D;
            this.Gauge_RPM.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Gauge_RPM.Location = new System.Drawing.Point(3, 3);
            this.Gauge_RPM.MajorSteps = 1000D;
            this.Gauge_RPM.MajorValueMultiplier = 0.01D;
            this.Gauge_RPM.MaxAngle = 315D;
            this.Gauge_RPM.MaxValue = 8000D;
            this.Gauge_RPM.MinAngle = 45D;
            this.Gauge_RPM.MinorSteps = 500D;
            this.Gauge_RPM.MinValue = 0D;
            this.Gauge_RPM.Name = "Gauge_RPM";
            this.Gauge_RPM.ShowDigital = false;
            this.Gauge_RPM.Size = new System.Drawing.Size(274, 274);
            this.Gauge_RPM.TabIndex = 10;
            this.Gauge_RPM.Value = 2000D;
            // 
            // Gauge_Speed
            // 
            this.Gauge_Speed.DangerZone = 200D;
            this.Gauge_Speed.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Gauge_Speed.Location = new System.Drawing.Point(283, 3);
            this.Gauge_Speed.MajorSteps = 30D;
            this.Gauge_Speed.MajorValueMultiplier = 1D;
            this.Gauge_Speed.MaxAngle = 315D;
            this.Gauge_Speed.MaxValue = 240D;
            this.Gauge_Speed.MinAngle = 45D;
            this.Gauge_Speed.MinorSteps = 10D;
            this.Gauge_Speed.MinValue = 0D;
            this.Gauge_Speed.Name = "Gauge_Speed";
            this.Gauge_Speed.ShowDigital = false;
            this.Gauge_Speed.Size = new System.Drawing.Size(274, 274);
            this.Gauge_Speed.TabIndex = 11;
            this.Gauge_Speed.Value = 0D;
            // 
            // BT_SimBreakDown
            // 
            this.BT_SimBreakDown.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BT_SimBreakDown.Location = new System.Drawing.Point(563, 483);
            this.BT_SimBreakDown.Name = "BT_SimBreakDown";
            this.BT_SimBreakDown.Size = new System.Drawing.Size(137, 24);
            this.BT_SimBreakDown.TabIndex = 28;
            this.BT_SimBreakDown.Text = "Simulate breakdown";
            this.BT_SimBreakDown.UseVisualStyleBackColor = true;
            this.BT_SimBreakDown.Click += new System.EventHandler(this.BT_SimBreakDown_Click);
            // 
            // label2
            // 
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(3, 280);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(274, 40);
            this.label2.TabIndex = 25;
            this.label2.Text = "Speed demand";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SpeedDemand
            // 
            this.SpeedDemand.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SpeedDemand.LargeChange = 10;
            this.SpeedDemand.Location = new System.Drawing.Point(283, 283);
            this.SpeedDemand.Maximum = 100;
            this.SpeedDemand.Name = "SpeedDemand";
            this.SpeedDemand.Size = new System.Drawing.Size(274, 34);
            this.SpeedDemand.SmallChange = 5;
            this.SpeedDemand.TabIndex = 21;
            this.SpeedDemand.TickFrequency = 5;
            this.SpeedDemand.Scroll += new System.EventHandler(this.SpeedDemand_Scroll);
            // 
            // label4
            // 
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.Location = new System.Drawing.Point(3, 320);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(274, 40);
            this.label4.TabIndex = 26;
            this.label4.Text = "Acceleration demand";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // AccelDemand
            // 
            this.AccelDemand.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AccelDemand.LargeChange = 10;
            this.AccelDemand.Location = new System.Drawing.Point(283, 323);
            this.AccelDemand.Maximum = 100;
            this.AccelDemand.Name = "AccelDemand";
            this.AccelDemand.Size = new System.Drawing.Size(274, 34);
            this.AccelDemand.SmallChange = 5;
            this.AccelDemand.TabIndex = 27;
            this.AccelDemand.TickFrequency = 10;
            this.AccelDemand.Value = 50;
            this.AccelDemand.Scroll += new System.EventHandler(this.AccelDemand_Scroll);
            // 
            // CB_AutoClutch
            // 
            this.CB_AutoClutch.Appearance = System.Windows.Forms.Appearance.Button;
            this.CB_AutoClutch.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CB_AutoClutch.Location = new System.Drawing.Point(563, 363);
            this.CB_AutoClutch.Name = "CB_AutoClutch";
            this.CB_AutoClutch.Size = new System.Drawing.Size(137, 24);
            this.CB_AutoClutch.TabIndex = 18;
            this.CB_AutoClutch.Text = "Auto-clutch";
            this.CB_AutoClutch.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.CB_AutoClutch.UseVisualStyleBackColor = true;
            this.CB_AutoClutch.CheckedChanged += new System.EventHandler(this.CB_AutoClutch_CheckedChanged);
            // 
            // CB_AutoGear
            // 
            this.CB_AutoGear.Appearance = System.Windows.Forms.Appearance.Button;
            this.CB_AutoGear.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CB_AutoGear.Location = new System.Drawing.Point(563, 393);
            this.CB_AutoGear.Name = "CB_AutoGear";
            this.CB_AutoGear.Size = new System.Drawing.Size(137, 24);
            this.CB_AutoGear.TabIndex = 19;
            this.CB_AutoGear.Text = "Auto-gear";
            this.CB_AutoGear.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.CB_AutoGear.UseVisualStyleBackColor = true;
            this.CB_AutoGear.CheckedChanged += new System.EventHandler(this.CB_AutoGear_CheckedChanged);
            // 
            // CB_AutoGas
            // 
            this.CB_AutoGas.Appearance = System.Windows.Forms.Appearance.Button;
            this.CB_AutoGas.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CB_AutoGas.Location = new System.Drawing.Point(563, 423);
            this.CB_AutoGas.Name = "CB_AutoGas";
            this.CB_AutoGas.Size = new System.Drawing.Size(137, 24);
            this.CB_AutoGas.TabIndex = 20;
            this.CB_AutoGas.Text = "Auto-gas";
            this.CB_AutoGas.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.CB_AutoGas.UseVisualStyleBackColor = true;
            this.CB_AutoGas.CheckedChanged += new System.EventHandler(this.CB_AutoGas_CheckedChanged);
            // 
            // CB_AutoBreak
            // 
            this.CB_AutoBreak.Appearance = System.Windows.Forms.Appearance.Button;
            this.CB_AutoBreak.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CB_AutoBreak.Location = new System.Drawing.Point(563, 453);
            this.CB_AutoBreak.Name = "CB_AutoBreak";
            this.CB_AutoBreak.Size = new System.Drawing.Size(137, 24);
            this.CB_AutoBreak.TabIndex = 24;
            this.CB_AutoBreak.Text = "Auto-break";
            this.CB_AutoBreak.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.CB_AutoBreak.UseVisualStyleBackColor = true;
            this.CB_AutoBreak.CheckedChanged += new System.EventHandler(this.CB_AutoBreak_CheckedChanged);
            // 
            // Label_SpeedDemand
            // 
            this.Label_SpeedDemand.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Label_SpeedDemand.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_SpeedDemand.Location = new System.Drawing.Point(563, 280);
            this.Label_SpeedDemand.Name = "Label_SpeedDemand";
            this.Label_SpeedDemand.Size = new System.Drawing.Size(137, 40);
            this.Label_SpeedDemand.TabIndex = 29;
            this.Label_SpeedDemand.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_AccelDemand
            // 
            this.Label_AccelDemand.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Label_AccelDemand.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_AccelDemand.Location = new System.Drawing.Point(563, 320);
            this.Label_AccelDemand.Name = "Label_AccelDemand";
            this.Label_AccelDemand.Size = new System.Drawing.Size(137, 40);
            this.Label_AccelDemand.TabIndex = 30;
            this.Label_AccelDemand.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Controls.Add(this.label7);
            this.flowLayoutPanel2.Controls.Add(this.Label_State);
            this.flowLayoutPanel2.Controls.Add(this.Gauge_Temp);
            this.flowLayoutPanel2.Controls.Add(this.Gauge_Fuel);
            this.flowLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel2.Location = new System.Drawing.Point(563, 3);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            this.flowLayoutPanel2.Size = new System.Drawing.Size(137, 274);
            this.flowLayoutPanel2.TabIndex = 33;
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(3, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(50, 20);
            this.label7.TabIndex = 0;
            this.label7.Text = "State";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_State
            // 
            this.Label_State.Location = new System.Drawing.Point(59, 0);
            this.Label_State.Name = "Label_State";
            this.Label_State.Size = new System.Drawing.Size(70, 20);
            this.Label_State.TabIndex = 1;
            this.Label_State.Text = "label8";
            this.Label_State.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Gauge_Temp
            // 
            this.Gauge_Temp.DangerZone = 0D;
            this.Gauge_Temp.Location = new System.Drawing.Point(3, 23);
            this.Gauge_Temp.MajorSteps = 40D;
            this.Gauge_Temp.MajorValueMultiplier = 1D;
            this.Gauge_Temp.MaxAngle = 270D;
            this.Gauge_Temp.MaxValue = 130D;
            this.Gauge_Temp.MinAngle = 90D;
            this.Gauge_Temp.MinorSteps = 10D;
            this.Gauge_Temp.MinValue = 50D;
            this.Gauge_Temp.Name = "Gauge_Temp";
            this.Gauge_Temp.ShowDigital = false;
            this.Gauge_Temp.Size = new System.Drawing.Size(126, 119);
            this.Gauge_Temp.TabIndex = 2;
            this.Gauge_Temp.Value = 90D;
            // 
            // Gauge_Fuel
            // 
            this.Gauge_Fuel.DangerZone = 0D;
            this.Gauge_Fuel.Location = new System.Drawing.Point(3, 148);
            this.Gauge_Fuel.MajorSteps = 10D;
            this.Gauge_Fuel.MajorValueMultiplier = 0.1D;
            this.Gauge_Fuel.MaxAngle = 315D;
            this.Gauge_Fuel.MaxValue = 60D;
            this.Gauge_Fuel.MinAngle = 45D;
            this.Gauge_Fuel.MinorSteps = 5D;
            this.Gauge_Fuel.MinValue = 0D;
            this.Gauge_Fuel.Name = "Gauge_Fuel";
            this.Gauge_Fuel.ShowDigital = true;
            this.Gauge_Fuel.Size = new System.Drawing.Size(126, 119);
            this.Gauge_Fuel.TabIndex = 3;
            this.Gauge_Fuel.Value = 60D;
            // 
            // BT_Reset
            // 
            this.BT_Reset.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BT_Reset.Location = new System.Drawing.Point(563, 513);
            this.BT_Reset.Name = "BT_Reset";
            this.BT_Reset.Size = new System.Drawing.Size(137, 24);
            this.BT_Reset.TabIndex = 34;
            this.BT_Reset.Text = "Reset";
            this.BT_Reset.UseVisualStyleBackColor = true;
            this.BT_Reset.Click += new System.EventHandler(this.BT_Reset_Click);
            // 
            // CB_Disconnect
            // 
            this.CB_Disconnect.Appearance = System.Windows.Forms.Appearance.Button;
            this.CB_Disconnect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CB_Disconnect.Location = new System.Drawing.Point(3, 363);
            this.CB_Disconnect.Name = "CB_Disconnect";
            this.CB_Disconnect.Size = new System.Drawing.Size(274, 24);
            this.CB_Disconnect.TabIndex = 35;
            this.CB_Disconnect.Text = "Disconnect";
            this.CB_Disconnect.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.CB_Disconnect.UseVisualStyleBackColor = true;
            this.CB_Disconnect.CheckedChanged += new System.EventHandler(this.CB_Disconnect_CheckedChanged);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(3, 390);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(274, 30);
            this.label1.TabIndex = 22;
            this.label1.Text = "Acceleration m/s/s";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_Acceleration
            // 
            this.Label_Acceleration.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_Acceleration.Location = new System.Drawing.Point(283, 390);
            this.Label_Acceleration.Name = "Label_Acceleration";
            this.Label_Acceleration.Size = new System.Drawing.Size(274, 30);
            this.Label_Acceleration.TabIndex = 23;
            this.Label_Acceleration.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(3, 420);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(274, 30);
            this.label6.TabIndex = 31;
            this.label6.Text = "G load";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_GLoad
            // 
            this.Label_GLoad.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_GLoad.Location = new System.Drawing.Point(283, 420);
            this.Label_GLoad.Name = "Label_GLoad";
            this.Label_GLoad.Size = new System.Drawing.Size(274, 30);
            this.Label_GLoad.TabIndex = 32;
            this.Label_GLoad.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(3, 450);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(274, 30);
            this.label3.TabIndex = 36;
            this.label3.Text = "Fuel consumption l/100km";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_FuelCons
            // 
            this.Label_FuelCons.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_FuelCons.Location = new System.Drawing.Point(283, 450);
            this.Label_FuelCons.Name = "Label_FuelCons";
            this.Label_FuelCons.Size = new System.Drawing.Size(274, 30);
            this.Label_FuelCons.TabIndex = 37;
            this.Label_FuelCons.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(3, 480);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(274, 30);
            this.label5.TabIndex = 38;
            this.label5.Text = "Wheel RPS";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_WheelRPS
            // 
            this.Label_WheelRPS.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_WheelRPS.Location = new System.Drawing.Point(283, 480);
            this.Label_WheelRPS.Name = "Label_WheelRPS";
            this.Label_WheelRPS.Size = new System.Drawing.Size(274, 30);
            this.Label_WheelRPS.TabIndex = 39;
            this.Label_WheelRPS.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(3, 510);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(274, 30);
            this.label8.TabIndex = 40;
            this.label8.Text = "Power RPS";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Label_EnginePower
            // 
            this.Label_EnginePower.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_EnginePower.Location = new System.Drawing.Point(283, 510);
            this.Label_EnginePower.Name = "Label_EnginePower";
            this.Label_EnginePower.Size = new System.Drawing.Size(274, 30);
            this.Label_EnginePower.TabIndex = 41;
            this.Label_EnginePower.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ControlsSplit
            // 
            this.ControlsSplit.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ControlsSplit.Location = new System.Drawing.Point(0, 0);
            this.ControlsSplit.Name = "ControlsSplit";
            this.ControlsSplit.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // ControlsSplit.Panel1
            // 
            this.ControlsSplit.Panel1.Controls.Add(this.ControlsLayout);
            this.ControlsSplit.Size = new System.Drawing.Size(283, 568);
            this.ControlsSplit.SplitterDistance = 271;
            this.ControlsSplit.TabIndex = 2;
            // 
            // ControlsLayout
            // 
            this.ControlsLayout.ColumnCount = 4;
            this.ControlsLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.ControlsLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.ControlsLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.ControlsLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.ControlsLayout.Controls.Add(this.ClutchPedal, 0, 0);
            this.ControlsLayout.Controls.Add(this.GasPedal, 2, 0);
            this.ControlsLayout.Controls.Add(this.flowLayoutPanel1, 3, 0);
            this.ControlsLayout.Controls.Add(this.BreakPedal, 1, 0);
            this.ControlsLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ControlsLayout.Location = new System.Drawing.Point(0, 0);
            this.ControlsLayout.Name = "ControlsLayout";
            this.ControlsLayout.RowCount = 1;
            this.ControlsLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.ControlsLayout.Size = new System.Drawing.Size(283, 271);
            this.ControlsLayout.TabIndex = 1;
            // 
            // ClutchPedal
            // 
            this.ClutchPedal.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ClutchPedal.LargeChange = 25;
            this.ClutchPedal.Location = new System.Drawing.Point(3, 3);
            this.ClutchPedal.Maximum = 100;
            this.ClutchPedal.Name = "ClutchPedal";
            this.ClutchPedal.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.ClutchPedal.Size = new System.Drawing.Size(64, 265);
            this.ClutchPedal.SmallChange = 10;
            this.ClutchPedal.TabIndex = 1;
            this.ClutchPedal.TickFrequency = 10;
            this.ClutchPedal.Value = 100;
            this.ClutchPedal.Scroll += new System.EventHandler(this.ClutchPedal_Scroll);
            // 
            // GasPedal
            // 
            this.GasPedal.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GasPedal.LargeChange = 25;
            this.GasPedal.Location = new System.Drawing.Point(143, 3);
            this.GasPedal.Maximum = 100;
            this.GasPedal.Name = "GasPedal";
            this.GasPedal.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.GasPedal.Size = new System.Drawing.Size(64, 265);
            this.GasPedal.SmallChange = 10;
            this.GasPedal.TabIndex = 0;
            this.GasPedal.TickFrequency = 10;
            this.GasPedal.Scroll += new System.EventHandler(this.AccelPedal_Scroll);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.Label_Gear);
            this.flowLayoutPanel1.Controls.Add(this.Button_GearUp);
            this.flowLayoutPanel1.Controls.Add(this.Button_GearDown);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(213, 3);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(67, 265);
            this.flowLayoutPanel1.TabIndex = 2;
            // 
            // Label_Gear
            // 
            this.Label_Gear.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_Gear.Location = new System.Drawing.Point(3, 0);
            this.Label_Gear.Name = "Label_Gear";
            this.Label_Gear.Size = new System.Drawing.Size(60, 40);
            this.Label_Gear.TabIndex = 9;
            this.Label_Gear.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Button_GearUp
            // 
            this.Button_GearUp.Location = new System.Drawing.Point(3, 43);
            this.Button_GearUp.Name = "Button_GearUp";
            this.Button_GearUp.Size = new System.Drawing.Size(60, 25);
            this.Button_GearUp.TabIndex = 0;
            this.Button_GearUp.Text = "GR UP";
            this.Button_GearUp.UseVisualStyleBackColor = true;
            this.Button_GearUp.Click += new System.EventHandler(this.Button_GearUp_Click);
            // 
            // Button_GearDown
            // 
            this.Button_GearDown.Location = new System.Drawing.Point(3, 74);
            this.Button_GearDown.Name = "Button_GearDown";
            this.Button_GearDown.Size = new System.Drawing.Size(60, 25);
            this.Button_GearDown.TabIndex = 1;
            this.Button_GearDown.Text = "GR DN";
            this.Button_GearDown.UseVisualStyleBackColor = true;
            this.Button_GearDown.Click += new System.EventHandler(this.Button_GearDown_Click);
            // 
            // BreakPedal
            // 
            this.BreakPedal.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BreakPedal.LargeChange = 25;
            this.BreakPedal.Location = new System.Drawing.Point(73, 3);
            this.BreakPedal.Maximum = 100;
            this.BreakPedal.Name = "BreakPedal";
            this.BreakPedal.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.BreakPedal.Size = new System.Drawing.Size(64, 265);
            this.BreakPedal.SmallChange = 10;
            this.BreakPedal.TabIndex = 3;
            this.BreakPedal.TickFrequency = 10;
            this.BreakPedal.Scroll += new System.EventHandler(this.BreakPedal_Scroll);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(990, 568);
            this.Controls.Add(this.MainSplit);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Name = "MainForm";
            this.Text = "Car control";
            this.SizeChanged += new System.EventHandler(this.MainForm_SizeChanged);
            this.MainSplit.Panel1.ResumeLayout(false);
            this.MainSplit.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.MainSplit)).EndInit();
            this.MainSplit.ResumeLayout(false);
            this.DisplayLayout.ResumeLayout(false);
            this.DisplayLayout.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedDemand)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AccelDemand)).EndInit();
            this.flowLayoutPanel2.ResumeLayout(false);
            this.ControlsSplit.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.ControlsSplit)).EndInit();
            this.ControlsSplit.ResumeLayout(false);
            this.ControlsLayout.ResumeLayout(false);
            this.ControlsLayout.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ClutchPedal)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GasPedal)).EndInit();
            this.flowLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.BreakPedal)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer MainSplit;
        private System.Windows.Forms.TrackBar GasPedal;
        private System.Windows.Forms.TableLayoutPanel ControlsLayout;
        private System.Windows.Forms.TrackBar ClutchPedal;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Button Button_GearUp;
        private System.Windows.Forms.Button Button_GearDown;
        private System.Windows.Forms.TrackBar BreakPedal;
        private System.Windows.Forms.TableLayoutPanel DisplayLayout;
        private Forms.AnalogGauge Gauge_RPM;
        private Forms.AnalogGauge Gauge_Speed;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar SpeedDemand;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar AccelDemand;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label Label_Acceleration;
        private System.Windows.Forms.Label Label_Gear;
        private System.Windows.Forms.Button BT_SimBreakDown;
        private System.Windows.Forms.CheckBox CB_AutoClutch;
        private System.Windows.Forms.CheckBox CB_AutoGear;
        private System.Windows.Forms.CheckBox CB_AutoGas;
        private System.Windows.Forms.CheckBox CB_AutoBreak;
        private System.Windows.Forms.Label Label_SpeedDemand;
        private System.Windows.Forms.Label Label_AccelDemand;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label Label_GLoad;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label Label_State;
        private System.Windows.Forms.Button BT_Reset;
        private System.Windows.Forms.CheckBox CB_Disconnect;
        private Forms.AnalogGauge Gauge_Temp;
        private Forms.AnalogGauge Gauge_Fuel;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label Label_FuelCons;
        private System.Windows.Forms.SplitContainer ControlsSplit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label Label_WheelRPS;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label Label_EnginePower;
    }
}

