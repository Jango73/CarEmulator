
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QElapsedTimer>
#include <QMap>

// Application
#include "CSensorBooleanValue.h"
#include "CSensorIntegerValue.h"
#include "CSensorRealValue.h"

//-------------------------------------------------------------------------------------------------

#define ENGINE_ESPILON  0.0001

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CSensors : public QObject
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Enumerators
    //-------------------------------------------------------------------------------------------------

    enum EDoorSensors
    {
        eDoorDriver,
        eDoorPassenger,
        eDoorRearLeft,
        eDoorRearRight,
        eDoorBack,
        eDoorEngine
    };

    enum EMainLights
    {
        eMLOff,
        eMLPosition,      // Position lights
        eMLCrossing,      // Crossing lights
        eMLRoad           // Road lights
    };

    enum ESecondaryLights
    {
        eSLOff,
        eSLFrontAntiFog,  // Front anti-fog lights
        eSLRearAntiFog    // Rear anti-fog lights
    };

    enum EBlinkLights
    {
        eBLOff,
        eBLBlinkLeft,
        eBLBlinkRight,
        eBLBlinkWarnings
    };

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CSensors();

    //! Destructor
    virtual ~CSensors();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    void setMainLightsState(EMainLights eValue);
    void secondaryLightsState(ESecondaryLights eValue);
    void blinkLightsState(EBlinkLights eValue);

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    const CSensorRealValue& currentRPM() const;
    const CSensorRealValue& currentSpeedKMH() const;
    const CSensorRealValue& currentEngineTempC() const;
    const CSensorRealValue& accelerationKMHS() const;
    const CSensorRealValue& engineAccelerationRPSS() const;
    const CSensorRealValue& currentFuelLevelL() const;
    const CSensorRealValue& currentFuelLevelPercent() const;
    const CSensorRealValue& fuelConsumptionL100KM() const;

    CSensorRealValue& currentRPM();
    CSensorRealValue& currentSpeedKMH();
    CSensorRealValue& currentEngineTempC();
    CSensorRealValue& accelerationKMHS();
    CSensorRealValue& engineAccelerationRPSS();
    CSensorRealValue& currentFuelLevelL();
    CSensorRealValue& currentFuelLevelPercent();
    CSensorRealValue& fuelConsumptionL100KM();

    QMap<EDoorSensors, CSensorBooleanValue>& doorSensors();

    EMainLights mainLightsState() const;
    ESecondaryLights secondaryLightsState() const;
    EBlinkLights blinkLightsState() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QElapsedTimer                               m_tFuelConsTimer;

    CSensorRealValue                            m_vCurrentRPM;                  // Rounds per minute
    CSensorRealValue                            m_vCurrentSpeedKMH;             // Kilometers per hour
    CSensorRealValue                            m_vCurrentEngineTempC;          // Degrees celcius
    CSensorRealValue                            m_vAccelerationKMHS;            // Kilometers per hour per second
    CSensorRealValue                            m_vEngineAccelerationRPSS;      // Rounds per second per second
    CSensorRealValue                            m_vMaximumFuelLevelL;           // Liters
    CSensorRealValue                            m_vCurrentFuelLevelL;           // Liters
    CSensorRealValue                            m_vCurrentFuelLevelPercent;     // Percentage
    CSensorRealValue                            m_vFuelConsumptionL100KM;       // Liters per 100 km

    QMap<EDoorSensors, CSensorBooleanValue>     m_mDoorSensors;
    EMainLights                                 m_eMainLights;
    ESecondaryLights                            m_eSecondaryLights;
    EBlinkLights                                m_eBlinkLights;

    double                                      m_dPreviousSpeedKMH;            // Kilometers per hour
    double                                      m_dPreviousRPS;                 // Rounds per second
    double                                      m_dPreviousFuelLevelL;          // Liters
};

}
