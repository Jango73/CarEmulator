
// Qt
#include <QDebug>

// Application
#include "CCarAI.h"
#include "CUtils.h"

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

CCarAI::CCarAI(bool bSoundOn)
    : CCar(bSoundOn)
    , m_eBehavior(eNormal)
    , m_bAutoClutch(true)
    , m_bAutoGear(true)
    , m_bAutoGas(false)
    , m_bAutoBreak(false)
    , m_dSpeedDemand(0.0)
    , m_dAccelDemand(0.0)
    , m_pidClutchControl(1.0, 0.005, 0.05)
    , m_pidAccelControl(0.9, 0.008, 0.2)
{
}

//-------------------------------------------------------------------------------------------------

CCarAI::~CCarAI()
{
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setBehavior(EBehavior eBehavior)
{
    m_eBehavior = eBehavior;
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setAutoClutch(bool bValue)
{
    m_bAutoClutch = bValue;
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setAutoGear(bool bValue)
{
    m_bAutoGear = bValue;
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setAutoGas(bool bValue)
{
    m_bAutoGas = bValue;
    m_dAccelDemand = 0.0;
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setAutoBreak(bool bValue)
{
    m_bAutoBreak = bValue;
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setSpeedDemand(double dValue)
{
    m_dSpeedDemand = dValue;
    emit speedDemandChanged();
}

//-------------------------------------------------------------------------------------------------

void CCarAI::setAccelDemand(double dValue)
{
    if (fabs(dValue) < ENGINE_ESPILON)
        dValue = 0.0;

    m_dAccelDemand = dValue;
    emit accelDemandChanged();
}

//-------------------------------------------------------------------------------------------------

double CCarAI::speedDemand() const
{
    return m_dSpeedDemand;
}

//-------------------------------------------------------------------------------------------------

double CCarAI::accelDemand() const
{
    return m_dAccelDemand;
}

//-------------------------------------------------------------------------------------------------

const CPIDController& CCarAI::accelControl() const
{
    return m_pidAccelControl;
}

//-------------------------------------------------------------------------------------------------

void CCarAI::process(double dDeltaTimeMillis)
{
    processAutoClutch(dDeltaTimeMillis);
    processAutoGear(dDeltaTimeMillis);
    processAutoGas(dDeltaTimeMillis);

    CCar::process(dDeltaTimeMillis);
}

//-------------------------------------------------------------------------------------------------

void CCarAI::processAutoClutch(double dDeltaTimeMillis)
{
    // Case where auto-clutch is active

    if (m_bAutoClutch)
    {
        // Case where the gear is the one we asked for

        if (gearBox().currentGear() == gearBox().targetGear())
        {
            // Case where the car speed is less than the end of startup speed (i.e speed at which clutch is fully engaged)

            if (sensors().currentSpeedKMH().value() < engineSettings().startupEndSpeedKMH())
            {
                // Get the car speed and scale it to RPM

                double dCarSpeedMS = CUtils::KMHToMS(sensors().currentSpeedKMH().value());
                dCarSpeedMS *= CEngineSettings::SpeedMSToRPS;

                // Compute the target RPM

                double dCurrentRPM = sensors().currentRPM().value();
                double dTargetRPM = engineSettings().idleRPM() + ((engineSettings().maxRPM() / 10.0) * gasPedal().value());
                // double TargetRPM = engineSettings().IdleRPM;
                dTargetRPM = CUtils::mix(dTargetRPM, dCurrentRPM, 0.25);

                // Process with the controller

                m_pidClutchControl.setSetPoint(dTargetRPM);
                m_pidClutchControl.update((sensors().currentRPM().value() - dCarSpeedMS), dDeltaTimeMillis);

                // Case where the gas pedal is released

                if (gasPedal().value() < engineSettings().gasPedalEpsilon())
                {
                    // If we are in neutral gear, fully engage the clutch and reset the controller

                    if (gearBox().currentGear() == GEAR_NEUTRAL)
                    {
                        clutchPedal().setValue(1.0);
                        emit clutchPedalChanged();
                        m_pidClutchControl.reset();
                    }
                    else // else fully disengage the clutch and reset the controller
                    {
                        clutchPedal().setValue(0.0);
                        emit clutchPedalChanged();
                        m_pidClutchControl.reset();
                    }
                }
                else // else apply output of controller to clutch, using scale factor
                {
                    clutchPedal().setValue(
                                engineSettings().clutchContact() +
                                (m_pidClutchControl.output() / (engineSettings().breakDownRPM() * -1))
                                );
                    emit clutchPedalChanged();
                }
            }
            else // else we are driving, fully engage the clutch and reset the controller
            {
                clutchPedal().setValue(1.0);
                emit clutchPedalChanged();
                m_pidClutchControl.reset();
            }
        }
        else // else we are in a gear shift sequence, fully disengage the clutch and reset the controller
        {
            if (gearBox().currentGear() > GEAR_NEUTRAL || gearBox().targetGear() > GEAR_NEUTRAL)
            {
                clutchPedal().setValue(0.0);
                emit clutchPedalChanged();
                m_pidClutchControl.reset();
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CCarAI::processAutoGear(double dDeltaTimeMillis)
{
    Q_UNUSED(dDeltaTimeMillis);

    // Case where auto-gear is active in nominal mode
    // Auto-clutch must also be active

    if (m_bAutoGear && m_bAutoClutch)
    {
        // Case where the current gear is the one we asked for and the clutch is fully engaged

        if (gearBox().currentGear() == gearBox().targetGear() && clutchPedal().value() > 0.95)
        {
            // Case where the driver applies pressure to the gas pedal

            if (gasPedal().value() >= engineSettings().gasPedalEpsilon())
            {
                double dMaxSpeedMultplier = 10.0;

                if (m_eBehavior == eNormal)
                {
                    dMaxSpeedMultplier = 15.0;
                }
                else if (m_eBehavior == eFast)
                {
                    dMaxSpeedMultplier = 25.0;
                }

                double dMaxSpeedKMH = gearBox().currentMaxSpeedKMH() + (dMaxSpeedMultplier * gasPedal().value());

                if (sensors().currentSpeedKMH().value() > dMaxSpeedKMH && gearBox().currentGear() != GEAR_REVERSE)
                {
                    gearBox().up();
                }
            }
            else
            {
                if (sensors().currentSpeedKMH().value() < gearBox().currentMinSpeedKMH())
                {
                    if (gearBox().targetGear() > GEAR_NEUTRAL)
                        gearBox().down();
                }
            }
        }
        else
        {
            // Case where the car's speed is less than the end of startup speed, i.e. car is moving too slow

            if (sensors().currentSpeedKMH().value() < engineSettings().startupEndSpeedKMH())
            {
                // Case where the driver applies pressure to the gas pedal

                if (gasPedal().value() >= engineSettings().gasPedalEpsilon())
                {
                    // If gear is neutral, then bring gear up

                    if (gearBox().targetGear() < GEAR_1 && gearBox().currentGear() != GEAR_REVERSE)
                    {
                        gearBox().up();
                    }
                }
                else // No gas pedal pressure, bring gear down to reach neutral
                {
                    if (gearBox().targetGear() > GEAR_NEUTRAL)
                    {
                        gearBox().down();
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CCarAI::processAutoGas(double dDeltaTimeMillis)
{
    // Case where auto-gas is active
    // Auto-clutch and auto-gear must also be active

    if (m_bAutoGas && m_bAutoGear && m_bAutoClutch)
    {
        double dCarSpeedMS = CUtils::KMHToMS(sensors().currentSpeedKMH().value());
        double dTargetSpeedMS = CUtils::KMHToMS(m_dSpeedDemand * engineSettings().maxSpeedKMH());
        double dCarAccelerationMSS = CUtils::KMHToMS(sensors().accelerationKMHS().value());
        double dTargetAccelerationMSS = dTargetSpeedMS - dCarSpeedMS;
        bool bServingSpeed = true;

        // Case where there is an acceleration demand

        if (m_dAccelDemand != 0.0)
        {
            bServingSpeed = false;

            // Target speed becomes current speed

            m_dSpeedDemand = sensors().currentSpeedKMH().value() / engineSettings().maxSpeedKMH();
            emit speedDemandChanged();

            dTargetAccelerationMSS = m_dAccelDemand * CUtils::KMHToMS(15.0);
        }
        else
        {
            double dClipAcceleration = 1.0;

            if (m_eBehavior == eNormal)
            {
                dClipAcceleration = 1.5;
            }
            else if (m_eBehavior == eFast)
            {
                dClipAcceleration = 3.0;
            }

            // In case we decelerate, clip is more gentle

            if (dTargetAccelerationMSS < 0.0) dClipAcceleration *= 0.5;

            // Clip the target acceleration to some acceptable values

            if (dTargetAccelerationMSS > dClipAcceleration) dTargetAccelerationMSS = dClipAcceleration;
            if (dTargetAccelerationMSS < -dClipAcceleration) dTargetAccelerationMSS = -dClipAcceleration;
        }

        // Case where the speed demand, accel demand and car's speed are very low

        if (m_dSpeedDemand < 0.05 && m_dAccelDemand < 0.05 && sensors().currentSpeedKMH().value() < 3.0)
        {
            // Fully disengage the gas pedal and reset the controller

            gasPedal().setValue(0.0);
            emit gasPedalChanged();
            m_pidAccelControl.reset();

            // Apply parking breaks

            if (m_bAutoBreak)
            {
                breakPedal().setValue(1.0);
                emit breakPedalChanged();
            }
        }
        else
        {
            // Case where the gear is neutral

            if (gearBox().currentGear() == GEAR_NEUTRAL)
            {
                // Apply little pressure to gas in order to activate the startup sequence
                // Reset the controller

                gasPedal().setValue(engineSettings().gasPedalEpsilon() * 4);
                emit gasPedalChanged();
                m_pidAccelControl.reset();
            }

            // Case where the clutch is partially or fully disengaged

            else if (clutchPedal().value() <= engineSettings().clutchContact())
            {
                // Bring gas fully down

                gasPedal().setValue(0.0);
                emit gasPedalChanged();

                if (dTargetSpeedMS < dCarSpeedMS)
                {
                    // m_pidAccelControl.Reset();
                }
            }

            // All other cases

            else
            {
                m_pidAccelControl.setSetPoint(dTargetAccelerationMSS);
                m_pidAccelControl.update(dCarAccelerationMSS, dDeltaTimeMillis);

                m_aAccelAverager.append(m_pidAccelControl.output());

                double dGasPedalValue = (m_aAccelAverager.getAverage() / 5.0);
                double dBreakPedalValue = dGasPedalValue * -1.5;

                // In case of extreme deceleration demand, push hard on brakes

                if (m_dAccelDemand < -0.9)
                {
                    dBreakPedalValue = 1.0;
                    dGasPedalValue = 0.0;
                }

                // In case no acceleration demand is done, limit gas pedal position

                if (bServingSpeed)
                {
                    if (dTargetSpeedMS <= dCarSpeedMS && dGasPedalValue > 0.95)
                    {
                        m_pidAccelControl.reset();
                    }
                }
                else
                {
                    if (m_dAccelDemand <= 0.0 && dGasPedalValue > 0.95)
                    {
                        m_pidAccelControl.reset();
                    }
                }

                if (dBreakPedalValue < 0.0) dBreakPedalValue = 0.0;

                // Assign gas value to pedal controller

                gasPedal().setValue(dGasPedalValue);
                emit gasPedalChanged();

                // Check if breaking is needed
                // Executed only if auto-break is enabled

                if (m_bAutoBreak)
                {
                    // Assign break value to pedal controller

                    breakPedal().setValue(dBreakPedalValue);
                    emit breakPedalChanged();
                }
            }
        }
    }
    else
    {
        m_dAccelDemand = (gasPedal().value() - (engineSettings().gasPedalEpsilon() * 4.0)) * 5.0;
    }
}
