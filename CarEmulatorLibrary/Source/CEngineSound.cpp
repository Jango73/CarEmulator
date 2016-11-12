
// Qt
#include <qmath.h>
#include <qendian.h>

// Application
#include "CEngineSound.h"
#include "CCar.h"
#include "CUtils.h"

using namespace CarEmulator;

const int DurationSeconds   = 1;
const int ToneSampleRateHz  = 440;
const int BufferSize        = 32768;

//-------------------------------------------------------------------------------------------------

CEngineSound::CEngineSound(CCar* pCar)
    : m_pCar(pCar)
{
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.00,  0.0);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.05,  0.4);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.10, -0.1);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.15,  0.3);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.20, -0.2);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.25,  0.2);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.30, -0.3);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.35,  0.1);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.40, -0.4);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.45, -0.2);
    m_iEngineSound << CInterpolator<double>::InterpolatorValue(0.50,  0.0);
}

//-------------------------------------------------------------------------------------------------

CEngineSound::~CEngineSound()
{
}

//-------------------------------------------------------------------------------------------------

QByteArray CEngineSound::synthesize(qint64 pos)
{
    QByteArray baData;

    const int channelBytes = m_tFormat.sampleSize() / 8;
    const int sampleBytes = m_tFormat.channelCount() * channelBytes;

    qint64 length = (m_tFormat.sampleRate() * m_tFormat.channelCount() * (m_tFormat.sampleSize() / 8)) * DurationSeconds;

    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    baData.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(baData.data());
    int sampleIndex = 0;

    while (length)
    {
        const qreal x = qSin(2 * M_PI * ToneSampleRateHz * qreal(sampleIndex % m_tFormat.sampleRate()) / m_tFormat.sampleRate());

        for (int i = 0; i < m_tFormat.channelCount(); ++i)
        {
            if (m_tFormat.sampleSize() == 8 && m_tFormat.sampleType() == QAudioFormat::UnSignedInt)
            {
                const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            }
            else if (m_tFormat.sampleSize() == 8 && m_tFormat.sampleType() == QAudioFormat::SignedInt)
            {
                const qint8 value = static_cast<qint8>(x * 127);
                *reinterpret_cast<quint8*>(ptr) = value;
            }
            else if (m_tFormat.sampleSize() == 16 && m_tFormat.sampleType() == QAudioFormat::UnSignedInt)
            {
                quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);

                if (m_tFormat.byteOrder() == QAudioFormat::LittleEndian)
                {
                    qToLittleEndian<quint16>(value, ptr);
                }
                else
                {
                    qToBigEndian<quint16>(value, ptr);
                }
            }
            else if (m_tFormat.sampleSize() == 16 && m_tFormat.sampleType() == QAudioFormat::SignedInt)
            {
                qint16 value = static_cast<qint16>(x * 32767);

                if (m_tFormat.byteOrder() == QAudioFormat::LittleEndian)
                {
                    qToLittleEndian<qint16>(value, ptr);
                }
                else
                {
                    qToBigEndian<qint16>(value, ptr);
                }
            }

            ptr += channelBytes;
            length -= channelBytes;
        }

        ++sampleIndex;
    }

    return baData;
}
