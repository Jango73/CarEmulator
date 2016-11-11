
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QVector>
#include <QTimer>

// Application
#include "CSensorValue.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CGearBox : public QObject
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Constructeurs et destructeur
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructeur par défaut
    //! Default constructor
    CGearBox();

    //! Destructeur
    //! Destructor
    virtual ~CGearBox();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    bool SetNeutralGear();

    bool SetHighestGear();

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    int NumGears() const;

    int CurrentGear() const;

    int TargetGear() const;

    double CurrentRatio() const;

    double CurrentMaxSpeedKMH() const;

    double CurrentMinSpeedKMH() const;

    //-------------------------------------------------------------------------------------------------
    // Méthodes de contrôle
    // Control methods
    //-------------------------------------------------------------------------------------------------

    bool Up();

    bool Down();

    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

protected:

    void onTimeout();

    //-------------------------------------------------------------------------------------------------
    // Propriétés
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    int                 _NumGears;
    int                 _CurrentGear;
    int                 _TargetGear;
    QVector<double>     _Ratios;
    QVector<double>     _MaxSpeedKMH;
    QVector<double>     _MinSpeedKMH;
    QTimer              _Timer;
};

}
