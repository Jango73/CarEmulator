
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

    bool setNeutralGear();

    bool setHighestGear();

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    int numGears() const;

    int currentGear() const;

    int targetGear() const;

    double currentRatio() const;

    double currentMaxSpeedKMH() const;

    double currentMinSpeedKMH() const;

    //-------------------------------------------------------------------------------------------------
    // Méthodes de contrôle
    // Control methods
    //-------------------------------------------------------------------------------------------------

    bool up();

    bool down();

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

    int                 m_iNumGears;
    int                 m_iCurrentGear;
    int                 m_iTargetGear;
    QVector<double>     m_vRatios;
    QVector<double>     m_vMaxSpeedKMH;
    QVector<double>     m_vMinSpeedKMH;
    QTimer              m_tTimer;
};

}
