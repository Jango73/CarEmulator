
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Application
#include "Constants.h"
#include "CXMLNode.h"
#include "CInterpolator.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CEngineSettings
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CEngineSettings();

    //! Destructor
    virtual ~CEngineSettings();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------


    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    double stallRPM() const;

    double idleRPM() const;

    double maxRPM() const;

    double breakDownRPM() const;

    double maxTemperatureC() const;

    double breakDownTemperatureC() const;

    double maxSpeedKMH() const;

    double clutchContact() const;

    double clutchFullEngaged() const;

    double gasPedalEpsilon() const;

    double startupEndSpeedKMH() const;

    CInterpolator<double>& torqueTable();

    const CInterpolator<double>& torqueTable() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void applyParameters(CXMLNode xParams);

    //-------------------------------------------------------------------------------------------------
    // Public properties
    //-------------------------------------------------------------------------------------------------

    static const double SpeedMSToRPS;                 // Factor used to convert speed to RPS
    static const double RPSToL;                       // Factor used to convert RPM to Liters
    static const double WheelRadiusM;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    double                  m_dStallRPM;                        // RPM at which car will stall if clutch is fully engaged
    double                  m_dIdleRPM;                         // RPM at idle (no gear)
    double                  m_dMaxRPM;                          // Max RPM that controller allows
    double                  m_dBreakDownRPM;                    // RPM at which engine breaks down
    double                  m_dMaxTemperatureC;                 // Maximum engine temperature in normal usage
    double                  m_dBreakDownTemperatureC;           // Temperature at which engine breaks down
    double                  m_dMaxSpeedKMH;                     // Maximum speed of vehicle in normal usage
    double                  m_dClutchContact;                   // Clutch contact point normalized (0 = full disengage, 1 = full engage)
    double                  m_dClutchFullEngaged;               // Normalized value at which clutch is fully engaged
    double                  m_dGasPedalEpsilon;                 // Value at which gas pedal is considered fully released
    double                  m_dStartupEndSpeedKMH;              // Speed at which clutch is supposed to be fully engaged after startup
    CInterpolator<double>   m_iTorqueTable;
};

}
