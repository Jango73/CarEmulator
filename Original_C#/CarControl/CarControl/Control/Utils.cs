
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarControl
{
    /// <summary>
    /// Utility class
    /// </summary>
    public class Utils
    {
        /// <summary>
        /// Converts milliseconds to seconds
        /// </summary>
        /// <param name="Millis"></param>
        /// <returns></returns>
        public static double MillisToSeconds(double Millis)
        {
            return Millis / 1000;
        }

        /// <summary>
        /// Converts seconds to hours
        /// </summary>
        /// <param name="Seconds"></param>
        /// <returns></returns>
        public static double SecondsToHours(double Seconds)
        {
            return Seconds / (60.0 * 60.0);
        }

        /// <summary>
        /// Converts hours to seconds
        /// </summary>
        /// <param name="Seconds"></param>
        /// <returns></returns>
        public static double HoursToSeconds(double Hours)
        {
            return Hours * (60.0 * 60.0);
        }

        /// <summary>
        /// Converts a per second value to a per hour value
        /// </summary>
        /// <param name="Seconds"></param>
        /// <returns></returns>
        public static double PerSecondToPerHour(double Seconds)
        {
            return Seconds * (60.0 * 60.0);
        }

        /// <summary>
        /// Convert kilometers per hour to meters per second
        /// </summary>
        /// <param name="Millis"></param>
        /// <returns></returns>
        public static double KMHToMS(double KMH)
        {
            // Kilometers by second
            double Value = KMH / (60.0 * 60.0);
            // Meters by second
            return Value * 1000.0;
        }

        /// <summary>
        /// Convert meters per second to kilometers per hour
        /// </summary>
        /// <param name="MS"></param>
        /// <returns></returns>
        public static double MSToKMH(double MS)
        {
            double Value = MS / 1000.0;
            return Value * (60.0 * 60.0);
        }

        /// <summary>
        /// Converts rounds per minute to rounds per second
        /// </summary>
        /// <param name="RPM"></param>
        /// <returns></returns>
        public static double RPMToRPS(double RPM)
        {
            return RPM / 60.0;
        }

        /// <summary>
        /// Converts rounds per second to rounds per minute
        /// </summary>
        /// <param name="RPS"></param>
        /// <returns></returns>
        public static double RPSToRPM(double RPS)
        {
            return RPS * 60.0;
        }

        /// <summary>
        /// Converts meters per second per second acceleration to G load factor
        /// </summary>
        /// <param name="KMHS"></param>
        /// <returns></returns>
        public static double MSSToG(double MSS)
        {
            return MSS * 0.10197162;
        }

        /// <summary>
        /// Converts kilometers per hours to kilometers per second
        /// </summary>
        /// <param name="KMH"></param>
        /// <returns></returns>
        public static double KMHToKMS(double KMH)
        {
            return KMH / (60.0 * 60.0);
        }
    }
}
