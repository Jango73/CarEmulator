
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>

// Application
#include "CInterpolator.h"
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

    //-------------------------------------------------------------------------------------------------
    // QML properties
    //-------------------------------------------------------------------------------------------------

    Q_PROPERTY(double engineRPM READ engineRPM NOTIFY engineRPMChanged)
    Q_PROPERTY(double speedKMH READ speedKMH NOTIFY speedKMHChanged)

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CCar();

    //! Destructor
    virtual ~CCar();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    double engineRPM() { return m_sSensors.currentRPM().value(); }

    double speedKMH() { return m_sSensors.currentSpeedKMH().value(); }

    double torqueTransferFactor() { return m_dTorqueTransferFactor; }

    CCarSettings& settings();

    CEngineSettings& engineSettings();

    CSensors& sensors();

    CGearBox& gearBox();

    CNormalizedInput& gasPedal();

    CNormalizedInput& breakPedal();

    CNormalizedInput& clutchPedal();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void startEngine();

    void stopEngine();

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Signals
    //-------------------------------------------------------------------------------------------------

signals:

    void engineRPMChanged();

    void speedKMHChanged();

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CCarSettings            m_sSettings;
    CEngineSettings         m_sEngineSettings;
    CSensors                m_sSensors;
    CGearBox                m_gGearBox;

    CNormalizedInput        m_iGasPedal;
    CNormalizedInput        m_iBreakPedal;
    CNormalizedInput        m_iClutchPedal;

    CNormalizedInput        m_iClutchLevel;
    CInterpolator<double>   m_iTorqueTable;

    bool                    m_bEngineOn;
    double                  m_dWheelRPS;
    double                  m_dEnginePowerRPS;
    double                  m_dTorqueTransferFactor;
};

}
