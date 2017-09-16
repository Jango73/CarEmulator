
using System;
using System.Xml;
using System.Linq;
using System.Text;
using System.Collections.Generic;

namespace CarControl.Forms
{
    /// <summary>
    /// A 3D vector
    /// </summary>
    public class Vector
    {
        public double x;
        public double y;
        public double z;

        public const double Deg2Rad = (Math.PI * 2) / 360.0;
        public const double Rad2Deg = 360.0 / (Math.PI * 2);

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// </summary>
        public Vector()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// </summary>
        /// <param name="NewX">The new X.</param>
        /// <param name="NewY">The new Y.</param>
        /// <param name="NewZ">The new Z.</param>
        public Vector(double NewX, double NewY, double NewZ)
        {
            x = NewX;
            y = NewY;
            z = NewZ;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Vector"/> class.
        /// </summary>
        /// <param name="NewVector">The new vector.</param>
        public Vector(Vector NewVector)
        {
            x = NewVector.x;
            y = NewVector.y;
            z = NewVector.z;
        }

        /// <summary>
        /// Implements the operator +.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns>The result of the operator.</returns>
        public static Vector operator +(Vector a, Vector b)
        {
            return new Vector(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        /// <summary>
        /// Implements the operator -.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns>The result of the operator.</returns>
        public static Vector operator -(Vector a, Vector b)
        {
            return new Vector(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        /// <summary>
        /// Implements the operator *.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns>The result of the operator.</returns>
        public static Vector operator *(Vector a, Vector b)
        {
            return new Vector(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        /// <summary>
        /// Implements the operator *.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns>The result of the operator.</returns>
        public static Vector operator *(Vector a, double b)
        {
            return new Vector(a.x * b, a.y * b, a.z * b);
        }

        /// <summary>
        /// Implements the operator /.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns>The result of the operator.</returns>
        public static Vector operator /(Vector a, double b)
        {
            return new Vector(a.x / b, a.y / b, a.z / b);
        }

        /// <summary>
        /// Lengthes the squared.
        /// </summary>
        /// <returns></returns>
        public double LengthSquared()
        {
            return Math.Abs(x * x + y * y + z * z);
        }

        /// <summary>
        /// Lengthes this instance.
        /// </summary>
        /// <returns></returns>
        public double Length()
        {
            return Math.Sqrt(x * x + y * y + z * z);
        }

        /// <summary>
        /// Normalizeds this instance.
        /// </summary>
        /// <returns></returns>
        public Vector Normalized()
        {
            double L = Length();
            if (L != 0.0) return this / L;
            return new Vector(0.0, 0.0, 1.0);
        }

        /// <summary>
        /// Gets the X angle.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns></returns>
        public static double GetXAngle(Vector a, Vector b)
        {
            Vector Temp = a - b;
            if (Temp.y == 0.0) return 0.0;
            return Math.Atan2(Temp.z, Temp.y) + (Math.PI / 2.0);
        }

        /// <summary>
        /// Gets the Y angle.
        /// </summary>
        /// <param name="a">A.</param>
        /// <param name="b">The b.</param>
        /// <returns></returns>
        public static double GetYAngle(Vector a, Vector b)
        {
            Vector Temp = a - b;
            if (Temp.z == 0.0)
            {
                if (Temp.x == 0.0) return 0.0;
                return Math.Atan2(Temp.z, Temp.x) + (Math.PI / 2.0);
            }
            return Math.Atan2(Temp.x, Temp.z) + Math.PI;
        }

        /// <summary>
        /// Rotates the X.
        /// </summary>
        /// <param name="Angle">The angle.</param>
        /// <returns></returns>
        public Vector RotateX(double Angle)
        {
            Vector Temp = new Vector();
            double C = Math.Cos(Angle);
            double S = Math.Sin(Angle);
            Temp.y = (y * C) + (z * -S);
            Temp.z = (y * S) + (z * C);
            return new Vector(x, Temp.y, Temp.z);
        }

        /// <summary>
        /// Rotates the Y.
        /// </summary>
        /// <param name="Angle">The angle.</param>
        /// <returns></returns>
        public Vector RotateY(double Angle)
        {
            Vector Temp = new Vector();
            double C = Math.Cos(Angle);
            double S = Math.Sin(Angle);
            Temp.z = (z * C) + (x * -S);
            Temp.x = (z * S) + (x * C);
            return new Vector(Temp.x, y, Temp.z);
        }

        /// <summary>
        /// Rotates the Z.
        /// </summary>
        /// <param name="Angle">The angle.</param>
        /// <returns></returns>
        public Vector RotateZ(double Angle)
        {
            Vector Temp = new Vector();
            double C = Math.Cos(Angle);
            double S = Math.Sin(Angle);
            Temp.x = (x * C) + (y * -S);
            Temp.y = (x * S) + (y * C);
            return new Vector(Temp.x, Temp.y, z);
        }

        /// <summary>
        /// Toes the XML node.
        /// </summary>
        /// <param name="Master">The master.</param>
        /// <returns></returns>
        public XmlNode ToXmlNode(XmlDocument Master)
        {
            XmlNode ReturnNode = Master.CreateElement("Vector");
            XmlNode NodeX = Master.CreateElement("X");
            XmlNode NodeY = Master.CreateElement("Y");
            XmlNode NodeZ = Master.CreateElement("Z");

            NodeX.InnerText = x.ToString();
            NodeY.InnerText = y.ToString();
            NodeZ.InnerText = z.ToString();

            ReturnNode.AppendChild(NodeX);
            ReturnNode.AppendChild(NodeY);
            ReturnNode.AppendChild(NodeZ);

            return ReturnNode;
        }
    }
}
