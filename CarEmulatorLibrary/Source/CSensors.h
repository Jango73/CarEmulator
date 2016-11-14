
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QElapsedTimer>

// Application
#include "CSensorRealValue.h"
#include "CSensorBooleanValue.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CSensors : public QObject
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Enumerators
    //-------------------------------------------------------------------------------------------------

    enum EDoorIndex {
        eDoorDriver,
        eDoorPassenger,
        eDoorRearLeft,
        eDoorRearRight,
        eDoorBack,
        eDoorMax
    };

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

    CSensorRealValue& currentRPM();

    CSensorRealValue& currentSpeedKMH();

    CSensorRealValue& currentEngineTempC();

    CSensorRealValue& accelerationKMHS();

    CSensorRealValue& engineAccelerationRPSS();

    CSensorRealValue& currentFuelLevelL();

    CSensorRealValue& currentFuelLevelPercent();

    CSensorRealValue& fuelConsumptionL100KM();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QElapsedTimer       m_tFuelConsTimer;

    CSensorRealValue    m_vCurrentRPM;                  // Rounds per minute
    CSensorRealValue    m_vCurrentSpeedKMH;             // Kilometers per hour
    CSensorRealValue    m_vCurrentEngineTempC;          // Degrees celcius
    CSensorRealValue    m_vAccelerationKMHS;            // Kilometers per hour per second
    CSensorRealValue    m_vEngineAccelerationRPSS;      // Rounds per second per second
    CSensorRealValue    m_vCurrentFuelLevelL;           // Liters
    CSensorRealValue    m_vCurrentFuelLevelPercent;     // Percentage
    CSensorRealValue    m_vFuelConsumptionL100KM;       // Liters per 100 km

    CSensorBooleanValue m_vDoorsClosed[eDoorMax];

    double              m_vPreviousSpeedKMH;            // Kilometers per hour
    double              m_vPreviousRPS;                 // Rounds per second
    double              m_vPreviousFuelLevelL;          // Liters
};

}
