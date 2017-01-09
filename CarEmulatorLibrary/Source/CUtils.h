
#pragma once

// Std
#include "math.h"

// Qt
#include <QObject>

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CUtils
{
public:

    //-------------------------------------------------------------------------------------------------
    // Public static methods
    //-------------------------------------------------------------------------------------------------

    static inline double millisToSeconds(double dMillis)
    {
        return dMillis / 1000.0;
    }

    static inline double secondsToHours(double dSeconds)
    {
        return dSeconds / (60.0 * 60.0);
    }

    static inline double hoursToSeconds(double dHours)
    {
        return dHours * (60.0 * 60.0);
    }

    static inline double perSecondToPerHour(double dSeconds)
    {
        return dSeconds * (60.0 * 60.0);
    }

    //! Kilometers/hour to meters/second
    static inline double KMHToMS(double KMH)
    {
        // Kilometers by second
        double Value = KMH / (60.0 * 60.0);
        // Meters by second
        return Value * 1000.0;
    }

    //! Meters/second to kilometers/hour
    static inline double MSToKMH(double MS)
    {
        double Value = MS / 1000.0;
        return Value * (60.0 * 60.0);
    }

    //! Rounds/minute to rounds/second
    static inline double RPMToRPS(double RPM)
    {
        return RPM / 60.0;
    }

    //! Rounds/second to rounds/minute
    static inline double RPSToRPM(double RPS)
    {
        return RPS * 60.0;
    }

    //! Kilometers/hour/second to meters/second/second
    static inline double KMHSToMSS(double KMHS)
    {
        return KMHToMS(KMHS);
    }

    //! Meters/second/second to G load
    static inline double MSSToG(double MSS)
    {
        return MSS * 0.10197162;
    }

    //! Kilometers/hour to Kilometers/second
    static inline double KMHToKMS(double KMH)
    {
        return KMH / (60.0 * 60.0);
    }

    static inline mix(double dValue1, double dValue2, double dMix)
    {
        double dFinalMix = qBound(0.0, dMix, 1.0);
        return dValue1 * (1.0 - dFinalMix) + dValue2 * dFinalMix;
    }
};

}
