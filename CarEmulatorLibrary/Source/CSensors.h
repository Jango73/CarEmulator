
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QElapsedTimer>
#include <QMap>

// Application
#include "CSensorRealValue.h"
#include "CSensorBooleanValue.h"

//-------------------------------------------------------------------------------------------------

#define ENGINE_ESPILON  0.0001

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

    enum EBoolSensor {
        eDoorDriver,
        eDoorPassenger,
        eDoorRearLeft,
        eDoorRearRight,
        eDoorBack,
        eDoorEngine,
        eLightPosition,
        eLightCrossing,
        eLightRoad,
        eLightWarnings,
        eLightTurnRight,
        eLightTurnLeft
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

    QMap<EBoolSensor, CSensorBooleanValue>& boolSensors();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QElapsedTimer                           m_tFuelConsTimer;

    CSensorRealValue                        m_vCurrentRPM;                  // Rounds per minute
    CSensorRealValue                        m_vCurrentSpeedKMH;             // Kilometers per hour
    CSensorRealValue                        m_vCurrentEngineTempC;          // Degrees celcius
    CSensorRealValue                        m_vAccelerationKMHS;            // Kilometers per hour per second
    CSensorRealValue                        m_vEngineAccelerationRPSS;      // Rounds per second per second
    CSensorRealValue                        m_vMaximumFuelLevelL;           // Liters
    CSensorRealValue                        m_vCurrentFuelLevelL;           // Liters
    CSensorRealValue                        m_vCurrentFuelLevelPercent;     // Percentage
    CSensorRealValue                        m_vFuelConsumptionL100KM;       // Liters per 100 km

    QMap<EBoolSensor, CSensorBooleanValue>  m_vBoolSensors;

    double                                  m_vPreviousSpeedKMH;            // Kilometers per hour
    double                                  m_vPreviousRPS;                 // Rounds per second
    double                                  m_vPreviousFuelLevelL;          // Liters
};

}
