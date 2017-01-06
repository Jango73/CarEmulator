
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>

// Application
#include "Constants.h"
#include "CXMLNode.h"
#include "CInterpolator.h"
#include "CNormalizedInput.h"
#include "CCarSettings.h"
#include "CSensors.h"
#include "CEngineSettings.h"
#include "CGearBox.h"
#include "CEngineSound.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CCar : public QObject
{
    Q_OBJECT

    //-------------------------------------------------------------------------------------------------
    // QML properties
    //-------------------------------------------------------------------------------------------------

    Q_PROPERTY(int gear READ gearValue WRITE setGearValue NOTIFY gearChanged)
    Q_PROPERTY(double gasPedal READ gasPedalValue WRITE setGasPedalValue NOTIFY gasPedalChanged)
    Q_PROPERTY(double breakPedal READ breakPedalValue WRITE setBreakPedalValue NOTIFY breakPedalChanged)
    Q_PROPERTY(double clutchPedal READ clutchPedalValue WRITE setClutchPedalValue NOTIFY clutchPedalChanged)
    Q_PROPERTY(double engineRPM READ engineRPM NOTIFY engineRPMChanged)
    Q_PROPERTY(double enginePowerHP READ enginePowerHP NOTIFY enginePowerHPChanged)
    Q_PROPERTY(double engineTorqueNM READ engineTorqueNM NOTIFY engineTorqueNMChanged)
    Q_PROPERTY(double speedKMH READ speedKMH NOTIFY speedKMHChanged)
    Q_PROPERTY(double fuelPercent READ fuelPercent NOTIFY fuelPercentChanged)
    Q_PROPERTY(double engineTemperatureC READ engineTemperatureC NOTIFY engineTemperatureCChanged)
    Q_PROPERTY(double engineWaterTemperatureC READ engineWaterTemperatureC NOTIFY engineWaterTemperatureCChanged)

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CCar(bool bSoundOn = false);

    //! Constructor using parameters
    CCar(CXMLNode xParams, bool bSoundOn = false);

    //! Destructor
    virtual ~CCar();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    void setGearValue(int iValue);

    void setGasPedalValue(double dValue);

    void setBreakPedalValue(double dValue);

    void setClutchPedalValue(double dValue);

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    CCarSettings& settings();

    CEngineSettings& engineSettings();

    CSensors& sensors();

    CGearBox& gearBox();

    CNormalizedInput& gasPedal();

    CNormalizedInput& breakPedal();

    CNormalizedInput& clutchPedal();

    CNormalizedInput& steering();

    int gearValue() const;

    double gasPedalValue() const;

    double breakPedalValue() const;

    double clutchPedalValue() const;

    double engineRPM() const;

    double enginePowerHP() const;

    double engineTorqueNM() const;

    double speedKMH() const;

    double fuelPercent() const;

    double engineTemperatureC() const;

    double engineWaterTemperatureC() const;

    double torqueTransferFactor() const;

    //-------------------------------------------------------------------------------------------------
    // Public control methods
    //-------------------------------------------------------------------------------------------------

    Q_INVOKABLE void startEngine();

    Q_INVOKABLE void stopEngine();

    Q_INVOKABLE void gearUp();

    Q_INVOKABLE void gearDown();

    Q_INVOKABLE virtual void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Private control methods
    //-------------------------------------------------------------------------------------------------

private:

    void initialize(bool bSoundOn);

    void applyParameters(CXMLNode xParams);

    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

protected slots:

    void onGearChanged();

    //-------------------------------------------------------------------------------------------------
    // Signals
    //-------------------------------------------------------------------------------------------------

signals:

    void gearChanged();

    void gasPedalChanged();

    void breakPedalChanged();

    void clutchPedalChanged();

    void engineRPMChanged();

    void enginePowerHPChanged();

    void engineTorqueNMChanged();

    void speedKMHChanged();

    void fuelPercentChanged();

    void engineTemperatureCChanged();

    void engineWaterTemperatureCChanged();

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

private:

    CCarSettings            m_sSettings;
    CEngineSettings         m_sEngineSettings;
    CSensors                m_sSensors;
    CGearBox                m_gGearBox;
    CEngineSound*           m_pSound;

    CNormalizedInput        m_iGasPedal;
    CNormalizedInput        m_iBreakPedal;
    CNormalizedInput        m_iClutchPedal;
    CNormalizedInput        m_iSteering;

    CNormalizedInput        m_iClutchLevel;

    bool                    m_bEngineOn;
    double                  m_dWheelRPS;                // For internal use, wheel rotation in revolutions per seconds
    double                  m_dEnginePowerRPS;          // For internal use, engine power in revolutions per second
    double                  m_dTorqueTransferFactor;    // For internal use, the actual torque transfer factor from engine to wheels
};

}
