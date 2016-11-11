
#pragma once

// Std
#include "math.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CUtils
{
public:

    //-------------------------------------------------------------------------------------------------
    // Public static methods
    //-------------------------------------------------------------------------------------------------

    static inline double MillisToSeconds(double Millis)
    {
        return Millis / 1000.0;
    }

    static inline double SecondsToHours(double Seconds)
    {
        return Seconds / (60.0 * 60.0);
    }

    static inline double HoursToSeconds(double Hours)
    {
        return Hours * (60.0 * 60.0);
    }

    static inline double PerSecondToPerHour(double Seconds)
    {
        return Seconds * (60.0 * 60.0);
    }

    static inline double KMHToMS(double KMH)
    {
        // Kilometers by second
        double Value = KMH / (60.0 * 60.0);
        // Meters by second
        return Value * 1000.0;
    }

    static inline double MSToKMH(double MS)
    {
        double Value = MS / 1000.0;
        return Value * (60.0 * 60.0);
    }

    static inline double RPMToRPS(double RPM)
    {
        return RPM / 60.0;
    }

    static inline double RPSToRPM(double RPS)
    {
        return RPS * 60.0;
    }

    static inline double MSSToG(double MSS)
    {
        return MSS * 0.10197162;
    }

    static inline double KMHToKMS(double KMH)
    {
        return KMH / (60.0 * 60.0);
    }
};

}
