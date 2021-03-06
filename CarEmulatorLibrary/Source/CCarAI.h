
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

    Q_PROPERTY(double speedDemand READ speedDemand WRITE setSpeedDemand NOTIFY speedDemandChanged)
    Q_PROPERTY(double accelDemand READ accelDemand WRITE setAccelDemand NOTIFY accelDemandChanged)

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
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CCarAI(bool bSoundOn = false);

    //! Destructor
    virtual ~CCarAI();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    void setBehavior(EBehavior eBehavior);

    void setAutoClutch(bool bValue);

    void setAutoGear(bool bValue);

    void setAutoGas(bool bValue);

    void setAutoBreak(bool bValue);

    void setSpeedDemand(double dValue);

    void setAccelDemand(double dValue);

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    double speedDemand() const;

    double accelDemand() const;

    const CPIDController& accelControl() const;

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

    void speedDemandChanged();

    void accelDemandChanged();

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
