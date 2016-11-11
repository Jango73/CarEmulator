
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CEngineSettings
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructeurs et destructeur
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructeur par défaut
    //! Default constructor
    CEngineSettings();

    //! Destructeur
    //! Destructor
    virtual ~CEngineSettings();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    double StallRPM() const;

    double IdleRPM() const;

    double MaxRPM() const;

    double BreakDownRPM() const;

    double MaxTemperatureC() const;

    double BreakDownTemperatureC() const;

    double MaxSpeedKMH() const;

    double ClutchContact() const;

    double ClutchFullEngaged() const;

    double GasPedalEpsilon() const;

    double StartupEndSpeedKMH() const;

    static const double SpeedMSToRPS;                 // Factor used to convert speed to RPS
    static const double RPSToL;                       // Factor used to convert RPM to Liters
    static const double WheelRadiusM;

    //-------------------------------------------------------------------------------------------------
    // Propriétés
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    double _StallRPM;                           // RPM at which car will stall if clutch is fully engaged
    double _IdleRPM;                            // RPM at idle (no gear)
    double _MaxRPM;                             // Max RPM that controller allows
    double _BreakDownRPM;                       // RPM at which engine breaks down
    double _MaxTemperatureC;                    // Maximum engine temperature in normal usage
    double _BreakDownTemperatureC;              // Temperature at which engine breaks down
    double _MaxSpeedKMH;                        // Maximum speed of vehicle in normal usage
    double _ClutchContact;                      // Clutch contact point normalized (0 = full disengage, 1 = full engage)
    double _ClutchFullEngaged;                  // Normalized value at which clutch is fully engaged
    double _GasPedalEpsilon;                    // Value at which gas pedal is considered fully released
    double _StartupEndSpeedKMH;                 // Speed at which clutch is supposed to be fully engaged after startup
};

}
