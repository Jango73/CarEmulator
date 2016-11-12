
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Application
#include "CSoundSynth.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CCar;

class CAREMULATOR_SHARED_EXPORT CEngineSound : public CSoundSynth
{
    Q_OBJECT

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CEngineSound(CCar* pCar);

    //! Destructor
    virtual ~CEngineSound();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    virtual QByteArray synthesize(qint64 pos) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CCar*                   m_pCar;
    CInterpolator<double>   m_iEngineSound;
    double                  _SoundCycleNormalizedPosition;
    QList<double>           _SoundNormalizedPosition;
};

}
