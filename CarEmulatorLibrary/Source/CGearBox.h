
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QVector>
#include <QTimer>

// Application
#include "CSensorRealValue.h"

//-------------------------------------------------------------------------------------------------

#define GEAR_REVERSE    0
#define GEAR_NEUTRAL    1
#define GEAR_1          2

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CGearBox : public QObject
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CGearBox();

    //! Destructor
    virtual ~CGearBox();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    bool setCurrentGear(int iValue);

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
    // Signals
    //-------------------------------------------------------------------------------------------------

signals:

    void gearChanged();

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
