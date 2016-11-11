
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
    // Constructeurs et destructeur
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructeur par d�faut
    //! Default constructor
    CSensors();

    //! Destructeur
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

    CSensorValue& fuelConsumptionL100KM();

    //-------------------------------------------------------------------------------------------------
    // M�thodes de contr�le
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Signaux
    // Signals
    //-------------------------------------------------------------------------------------------------

signals:

    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

protected slots:

    //-------------------------------------------------------------------------------------------------
    // Propri�t�s
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
    CSensorValue    m_vFuelConsumptionL100KM;     // Liters per 100 km

    double          m_vPreviousSpeedKMH;          // Kilometers per hour
    double          m_vPreviousRPS;               // Rounds per second
    double          m_vPreviousFuelLevelL;        // Liters
};

}
