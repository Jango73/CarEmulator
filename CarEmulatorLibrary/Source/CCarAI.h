
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>

// Application
#include "CCar.h"
#include "CPIDController.h"
#include "CAverager.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CCarAI : public CCar
{
    Q_OBJECT

    //-------------------------------------------------------------------------------------------------
    // QML properties
    //-------------------------------------------------------------------------------------------------

public:

    //-------------------------------------------------------------------------------------------------
    // Enumerators
    //-------------------------------------------------------------------------------------------------

    enum EBehavior {
        eSlow,
        eNormal,
        eFast
    };

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CCarAI(bool bSoundOn = false);

    //! Destructor
    virtual ~CCarAI();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    virtual void process(double dDeltaTimeMillis) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Protected control methods
    //-------------------------------------------------------------------------------------------------

protected:

    void processAutoClutch(double dDeltaTimeMillis);

    void processAutoGear(double dDeltaTimeMillis);

    void processAutoGas(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Signals
    //-------------------------------------------------------------------------------------------------

signals:

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    EBehavior               m_eBehavior;

    bool                    m_bAutoClutch;
    bool                    m_bAutoGear;
    bool                    m_bAutoGas;
    bool                    m_bAutoBreak;

    double                  m_dSpeedDemand;
    double                  m_dAccelDemand;

    CPIDController          m_pidClutchControl;
    CPIDController          m_pidAccelControl;

    CAverager<double>       m_aClutchAverager;
    CAverager<double>       m_aAccelAverager;
};

}