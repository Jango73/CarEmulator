
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QElapsedTimer>

// Application
#include "CSensorValue.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CSensors : public QObject
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CSensors();

    //! Destructor
    virtual ~CSensors();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    CSensorValue& currentRPM();

    CSensorValue& currentSpeedKMH();

    CSensorValue& currentEngineTempC();

    CSensorValue& accelerationKMHS();

    CSensorValue& engineAccelerationRPSS();

    CSensorValue& currentFuelLevelL();

    CSensorValue& currentFuelLevelPercent();

    CSensorValue& fuelConsumptionL100KM();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QElapsedTimer   m_tFuelConsTimer;

    CSensorValue    m_vCurrentRPM;                // Rounds per minute
    CSensorValue    m_vCurrentSpeedKMH;           // Kilometers per hour
    CSensorValue    m_vCurrentEngineTempC;        // Degrees celcius
    CSensorValue    m_vAccelerationKMHS;          // Kilometers per hour per second
    CSensorValue    m_vEngineAccelerationRPSS;    // Rounds per second per second
    CSensorValue    m_vCurrentFuelLevelL;         // Liters
    CSensorValue    m_vCurrentFuelLevelPercent;   // Percentage
    CSensorValue    m_vFuelConsumptionL100KM;     // Liters per 100 km

    double          m_vPreviousSpeedKMH;          // Kilometers per hour
    double          m_vPreviousRPS;               // Rounds per second
    double          m_vPreviousFuelLevelL;        // Liters
};

}
