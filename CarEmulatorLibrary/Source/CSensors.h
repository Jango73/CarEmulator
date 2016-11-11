
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QVector>
#include <QTimer>
#include <QDateTime>

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

    //! Constructeur par défaut
    //! Default constructor
    CSensors();

    //! Destructeur
    //! Destructor
    virtual ~CSensors();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //! Définit le nom du noeud
    //! Sets the node's name

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    CSensorValue& CurrentRPM();

    CSensorValue& CurrentSpeedKMH();

    CSensorValue& CurrentEngineTempC();

    CSensorValue& AccelerationKMHS();

    CSensorValue& EngineAccelerationRPSS();

    CSensorValue& CurrentFuelLevelL();

    CSensorValue& FuelConsumptionL100KM();

    //-------------------------------------------------------------------------------------------------
    // Méthodes de contrôle
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void Process(double DeltaTimeMillis);

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
    // Propriétés
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CSensorValue    _CurrentRPM;                // Rounds per minute
    CSensorValue    _CurrentSpeedKMH;           // Kilometers per hour
    CSensorValue    _CurrentEngineTempC;        // Degrees celcius
    CSensorValue    _AccelerationKMHS;          // Kilometers per hour per second
    CSensorValue    _EngineAccelerationRPSS;    // Rounds per second per second
    CSensorValue    _CurrentFuelLevelL;         // Liters
    CSensorValue    _FuelConsumptionL100KM;     // Liters per 100 km

    double          _PreviousSpeedKMH;          // Kilometers per hour
    double          _PreviousRPS;               // Rounds per second
    double          _PreviousFuelLevelL;        // Liters
};

}
