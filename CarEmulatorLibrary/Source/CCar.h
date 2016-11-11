
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
#include "CNormalizedInput.h"
#include "CCarSettings.h"
#include "CSensors.h"
#include "CEngineSettings.h"
#include "CGearBox.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CCar : public QObject
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Constructeurs et destructeur
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructeur par défaut
    //! Default constructor
    CCar();

    //! Destructeur
    //! Destructor
    virtual ~CCar();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //! Définit le nom du noeud
    //! Sets the node's name

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    CCarSettings& Settings();

    CEngineSettings& EngineSettings();

    CSensors& Sensors();

    CGearBox& GearBox();

    CNormalizedInput& GasPedal();

    CNormalizedInput& BreakPedal();

    CNormalizedInput& ClutchPedal();

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

    CCarSettings        _Settings;
    CEngineSettings     _EngineSettings;
    CSensors            _Sensors;
    CGearBox            _GearBox;

    CNormalizedInput    _GasPedal;
    CNormalizedInput    _BreakPedal;
    CNormalizedInput    _ClutchPedal;
};

}
