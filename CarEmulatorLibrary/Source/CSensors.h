
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

    CSensorDoubleValue& currentRPM();

    CSensorDoubleValue& currentSpeedKMH();

    CSensorDoubleValue& currentEngineTempC();

    CSensorDoubleValue& accelerationKMHS();

    CSensorDoubleValue& engineAccelerationRPSS();

    CSensorDoubleValue& currentFuelLevelL();

    CSensorDoubleValue& currentFuelLevelPercent();

    CSensorDoubleValue& fuelConsumptionL100KM();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QElapsedTimer       m_tFuelConsTimer;

    CSensorDoubleValue  m_vCurrentRPM;                  // Rounds per minute
    CSensorDoubleValue  m_vCurrentSpeedKMH;             // Kilometers per hour
    CSensorDoubleValue  m_vCurrentEngineTempC;          // Degrees celcius
    CSensorDoubleValue  m_vAccelerationKMHS;            // Kilometers per hour per second
    CSensorDoubleValue  m_vEngineAccelerationRPSS;      // Rounds per second per second
    CSensorDoubleValue  m_vCurrentFuelLevelL;           // Liters
    CSensorDoubleValue  m_vCurrentFuelLevelPercent;     // Percentage
    CSensorDoubleValue  m_vFuelConsumptionL100KM;       // Liters per 100 km

    CSensorBooleanValue m_vDoorsClosed[eDoorMax];

    double              m_vPreviousSpeedKMH;            // Kilometers per hour
    double              m_vPreviousRPS;                 // Rounds per second
    double              m_vPreviousFuelLevelL;          // Liters
};

}
