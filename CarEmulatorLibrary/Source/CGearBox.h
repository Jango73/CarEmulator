
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
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CGearBox();

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
    // Control methods
    //-------------------------------------------------------------------------------------------------

    bool up();

    bool down();

    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

protected slots:

    void onTimeout();

    //-------------------------------------------------------------------------------------------------
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
