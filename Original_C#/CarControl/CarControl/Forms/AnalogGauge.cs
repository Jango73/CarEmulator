
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace CarControl.Forms
{
    public partial class AnalogGauge : UserControl
    {
        protected Pen WhitePen = new Pen(Color.White);
        protected Pen BlackPen = new Pen(Color.Black);
        protected Pen BlackPen3 = new Pen(Color.Black, 3);
        protected Brush WhiteBrush = new SolidBrush(Color.White);
        protected Brush BlackBrush = new SolidBrush(Color.Black);
        protected Brush LiteGrayBrush = new SolidBrush(Color.LightGray);
        protected Brush BackBrush = new SolidBrush(Color.Gray);
        protected Brush DangerBrush = new SolidBrush(Color.FromArgb(80, 255, 0, 0));
        protected Font MainFont = new Font(FontFamily.GenericSansSerif, 8);
        protected LinearGradientBrush OuterBrush;
        protected LinearGradientBrush InnerBrush;

        double _MinValue;
        double _MaxValue;
        double _Value;
        double _MajorSteps;
        double _MinorSteps;
        double _MinAngle;
        double _MaxAngle;
        double _MajorValueMultiplier;
        double _DangerZone;
        bool _ShowDigital;

        /// <summary>
        /// 
        /// </summary>
        public double MinValue
        {
            get { return _MinValue; }
            set
            {
                _MinValue = value;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double MaxValue
        {
            get { return _MaxValue; }
            set
            {
                _MaxValue = value;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double Value
        {
            get { return _Value; }
            set
            {
                _Value = value;
                if (_Value < _MinValue) _Value = _MinValue;
                if (_Value > _MaxValue) _Value = _MaxValue;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double MajorSteps
        {
            get { return _MajorSteps; }
            set
            {
                _MajorSteps = value;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double MinorSteps
        {
            get { return _MinorSteps; }
            set
            {
                _MinorSteps = value;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double MinAngle
        {
            get { return _MinAngle; }
            set
            {
                _MinAngle = value;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double MaxAngle
        {
            get { return _MaxAngle; }
            set
            {
                _MaxAngle = value;
                Invalidate();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public double MajorValueMultiplier
        {
            get { return _MajorValueMultiplier; }
            set { _MajorValueMultiplier = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public double DangerZone
        {
            get { return _DangerZone; }
            set { _DangerZone = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public bool ShowDigital
        {
            get { return _ShowDigital; }
            set { _ShowDigital = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public AnalogGauge()
        {
            InitializeComponent();

            SetupBrushes();

            _MinValue = 0;
            _MaxValue = 6000;
            _Value = 2000;
            _MajorSteps = 500;
            _MinorSteps = 250;
            _MinAngle = 0;
            _MaxAngle = 180;
            _MajorValueMultiplier = 1.0;
            _DangerZone = 0.0;
            _ShowDigital = false;
        }

        private void SetupBrushes()
        {
            OuterBrush = new LinearGradientBrush(
               new Point(0, 0),
               new Point(0, ClientRectangle.Height),
               Color.FromArgb(255, 255, 255, 255),
               Color.FromArgb(255, 180, 180, 180));

            InnerBrush = new LinearGradientBrush(
               new Point(0, 0),
               new Point(0, ClientRectangle.Height),
               Color.FromArgb(255, 140, 140, 140),
               Color.FromArgb(255, 220, 220, 220));
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AnalogGauge_SizeChanged(object sender, EventArgs e)
        {
            SetupBrushes();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        protected override void OnPaintBackground(PaintEventArgs e)
        {
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        protected override void OnPaint(PaintEventArgs e)
        {
            Bitmap BackBuffer = new Bitmap(ClientSize.Width, ClientSize.Height);
            Graphics BackG = Graphics.FromImage(BackBuffer);

            BackG.FillRectangle(BackBrush, ClientRectangle);

            Rectangle BorderRect = new Rectangle(ClientRectangle.Location, ClientRectangle.Size);
            BorderRect.Inflate(-10, -10);

            Rectangle GaugeRect = new Rectangle(BorderRect.Location, BorderRect.Size);
            GaugeRect.Inflate(-10, -10);

            Point ClientCenter = new Point(ClientRectangle.Size.Width / 2, ClientRectangle.Size.Height / 2);
            Rectangle PinRect = new Rectangle(new Point(ClientCenter.X - 5, ClientCenter.Y - 5), new Size(10, 10));

            BackG.FillEllipse(OuterBrush, BorderRect);
            BackG.FillEllipse(InnerBrush, GaugeRect);

            double HalfX = (double)GaugeRect.Width * 0.5;
            double HalfY = (double)GaugeRect.Height * 0.5;

            double AngleSpan = _MaxAngle - _MinAngle;
            double ValueSpan = _MaxValue - _MinValue;

            Vector Offset = new Vector(GaugeRect.X + HalfX, GaugeRect.Y + HalfY, 0);
            Vector Center = new Vector(HalfX, HalfY, 0);

            if (_DangerZone > 0.0)
            {
                double Angle1 = _MinAngle + (AngleSpan * (_MinValue + (_DangerZone / ValueSpan)));
                double Angle2 = _MinAngle + (AngleSpan * (_MinValue + (_MaxValue / ValueSpan)));

                BackG.FillPie(DangerBrush, GaugeRect, 90 + (float)Angle1, (float)(Angle2 - Angle1));

                Rectangle CenterRect = new Rectangle(GaugeRect.Location, GaugeRect.Size);
                CenterRect.Inflate(CenterRect.Width / -4, CenterRect.Height / -4);

                BackG.FillEllipse(InnerBrush, CenterRect);
            }

            // Minor grads
            if (_MinorSteps > 0)
            {
                for (double Current = _MinValue; Current <= _MaxValue; Current += _MinorSteps)
                {
                    double Angle = _MinAngle + (((Current - _MinValue) / ValueSpan) * AngleSpan);

                    Vector P1 = new Vector(0, 0.95, 0);
                    Vector P2 = new Vector(0, 0.90, 0);

                    P1 = Offset + P1.RotateZ(Angle * Vector.Deg2Rad) * Center;
                    P2 = Offset + P2.RotateZ(Angle * Vector.Deg2Rad) * Center;

                    BackG.DrawLine(BlackPen, new Point((int)P1.x, (int)P1.y), new Point((int)P2.x, (int)P2.y));
                }
            }

            // Major grads
            if (_MajorSteps > 0)
            {
                for (double Current = _MinValue; Current <= _MaxValue; Current += _MajorSteps)
                {
                    double Angle = _MinAngle + (((Current - _MinValue) / ValueSpan) * AngleSpan);

                    Vector P1 = new Vector(0, 0.95, 0);
                    Vector P2 = new Vector(0, 0.85, 0);
                    Vector P3 = new Vector(0, 0.75, 0);

                    P1 = Offset + P1.RotateZ(Angle * Vector.Deg2Rad) * Center;
                    P2 = Offset + P2.RotateZ(Angle * Vector.Deg2Rad) * Center;
                    P3 = Offset + P3.RotateZ(Angle * Vector.Deg2Rad) * Center;

                    BackG.DrawLine(BlackPen, new Point((int)P1.x, (int)P1.y), new Point((int)P2.x, (int)P2.y));

                    String Text = ((int)(Current * _MajorValueMultiplier)).ToString();
                    Point TextPoint = new Point((int)P3.x, (int)P3.y);

                    SizeF Size = BackG.MeasureString(Text, MainFont);
                    TextPoint.X -= (int)(Size.Width / 2);
                    TextPoint.Y -= (int)(Size.Height / 2);

                    BackG.DrawString(Text, MainFont, BlackBrush, TextPoint);
                }
            }

            // Needle
            {
                double Angle = _MinAngle + (((_Value - _MinValue) / ValueSpan) * AngleSpan);

                Vector P1 = new Vector(-0.04, 0.0, 0);
                Vector P2 = new Vector(-0.01, 0.75, 0);
                Vector P3 = new Vector(0.01, 0.75, 0);
                Vector P4 = new Vector(0.04, 0.0, 0);

                P1 = Offset + P1.RotateZ(Angle * Vector.Deg2Rad) * Center;
                P2 = Offset + P2.RotateZ(Angle * Vector.Deg2Rad) * Center;
                P3 = Offset + P3.RotateZ(Angle * Vector.Deg2Rad) * Center;
                P4 = Offset + P4.RotateZ(Angle * Vector.Deg2Rad) * Center;

                Point[] Points = new Point[4];

                Points[0].X = (int)P1.x;
                Points[0].Y = (int)P1.y;
                Points[1].X = (int)P2.x;
                Points[1].Y = (int)P2.y;
                Points[2].X = (int)P3.x;
                Points[2].Y = (int)P3.y;
                Points[3].X = (int)P4.x;
                Points[3].Y = (int)P4.y;

                BackG.FillPolygon(BlackBrush, Points);
            }

            BackG.FillEllipse(OuterBrush, PinRect);

            if (_ShowDigital)
            {
                String Str = String.Format("{0:0.00}", _Value);
                SizeF TextSize = TextRenderer.MeasureText(Str, MainFont);
                BackG.DrawString(Str, MainFont, BlackBrush, new Point((ClientRectangle.Size.Width / 2) - ((int)TextSize.Width / 2), (ClientRectangle.Size.Height / 2) + 20));
            }

            e.Graphics.DrawImage(BackBuffer, 0, 0);
            BackG.Dispose();
        }
    }
}
