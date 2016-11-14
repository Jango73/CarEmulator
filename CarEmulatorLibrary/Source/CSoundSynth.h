
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------
// Includes

// Qt
#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <QThread>
#include <QMutex>

// Application
#include "CInterpolator.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CSoundSynth : public QIODevice
{
    Q_OBJECT

    friend class CSoundSynthGenerator;

public:

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CSoundSynth();

    //! Destructor
    virtual ~CSoundSynth();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    virtual qint64 readData(char* data, qint64 len) Q_DECL_OVERRIDE;

    virtual qint64 writeData(const char *data, qint64 len) Q_DECL_OVERRIDE;

    virtual qint64 bytesAvailable() const Q_DECL_OVERRIDE;

    virtual QByteArray synthesize(qint64 pos);

    //-------------------------------------------------------------------------------------------------
    // Slots
    //-------------------------------------------------------------------------------------------------

protected slots:

    //-------------------------------------------------------------------------------------------------
    // Inner classes
    //-------------------------------------------------------------------------------------------------

protected:

    class CSoundSynthGenerator : public QThread
    {
    public:

        CSoundSynthGenerator(CSoundSynth* pSynth);

        virtual ~CSoundSynthGenerator();

        QList<QByteArray> getBuffers();

        void stopMe();

        virtual void run() Q_DECL_OVERRIDE;

    protected:

        QMutex                  m_tMutex;
        CSoundSynth*            m_pSynth;
        QList<QByteArray>       m_lBuffers;
        qint64                  m_iPosition;
        bool                    m_bRun;
    };

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CSoundSynthGenerator    m_tGenerator;

    QAudioDeviceInfo        m_tDevice;
    QAudioOutput*           m_tAudioOutput;
    QIODevice*              m_pOutput; // not owned
    QAudioFormat            m_tFormat;
    QList<QByteArray>       m_lBuffers;
};

}
