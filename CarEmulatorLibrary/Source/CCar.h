
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QObject>
#include <QVector>
#include <QTimer>
#include <QDateTime>

// Application
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

public:

    //-------------------------------------------------------------------------------------------------
    // Constructeurs et destructeur
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructeur par défaut
    //! Default constructor
    CCar();

    //! Destructeur
    //! Destructor
    virtual ~CCar();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //! Définit le nom du noeud
    //! Sets the node's name

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

    //-------------------------------------------------------------------------------------------------
    // Méthodes de contrôle
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void process(double dDeltaTimeMillis);

    //-------------------------------------------------------------------------------------------------
    // Signaux
    // Signals
    //-------------------------------------------------------------------------------------------------

signals:

    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

protected slots:

    //-------------------------------------------------------------------------------------------------
    // Propriétés
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CCarSettings        m_sSettings;
    CEngineSettings     m_sEngineSettings;
    CSensors            m_sSensors;
    CGearBox            m_gGearBox;

    CNormalizedInput    m_iGasPedal;
    CNormalizedInput    m_iBreakPedal;
    CNormalizedInput    m_iClutchPedal;
};

}
