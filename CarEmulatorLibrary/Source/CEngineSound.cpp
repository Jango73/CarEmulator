
// Qt
#include <qmath.h>
#include <qendian.h>

// Application
#include "CEngineSound.h"
#include "CCar.h"
#include "CUtils.h"

using namespace CarEmulator;

const int iDurationSeconds      = 1;
const int iToneSampleRateHz     = 440;
const int iSamplesPerBuffer     = 44100 / 20;
const int iBytesPerSample       = 2;
const double dSampleRate        = 44100.0;
const double dBufferDurationS   = (double) iSamplesPerBuffer / dSampleRate;

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

    CInterpolator<double> iTemp1 = m_iEngineSound;
    CInterpolator<double> iTemp2 = m_iEngineSound;
    // CInterpolator<double> iTemp3 = m_iEngineSound;
    // CInterpolator<double> iTemp4 = m_iEngineSound;

    iTemp1.shift(0.08);
    iTemp1.randomize(0.75);
    m_iEngineSound.merge(iTemp1);

    iTemp2.shift(0.16);
    iTemp2.randomize(0.75);
    m_iEngineSound.merge(iTemp2);

    /*
    iTemp3.shift(0.24);
    iTemp3.randomize(0.75);
    m_iEngineSound.merge(iTemp3);

    iTemp4.shift(0.32);
    iTemp4.randomize(0.75);
    m_iEngineSound.merge(iTemp4);
    */
}

//-------------------------------------------------------------------------------------------------

CEngineSound::~CEngineSound()
{
}

//-------------------------------------------------------------------------------------------------

/*
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
*/

//-------------------------------------------------------------------------------------------------

QByteArray CEngineSound::synthesize(qint64 pos)
{
    QByteArray baData;

    double dEngineRPS = CUtils::RPMToRPS(m_pCar->sensors().currentRPM().value()) * 1.5;
    double dBreakDownRPS = CUtils::RPMToRPS(m_pCar->engineSettings().breakDownRPM()) * 1.5;
    double dEngineAccelRPSS = m_pCar->sensors().engineAccelerationRPSS().value() * 1.5;
    double dCycleSecondsPerSample = dBufferDurationS / iSamplesPerBuffer;
    double dTimeS = 0.0;
    int iSoundDataIndex = 0;

    for (int Index = 0; Index < iSamplesPerBuffer; Index++)
    {
        double dSamplesPerCycle = (1.0 / dEngineRPS) * dSampleRate;
        double dCycleDurationS = dCycleSecondsPerSample * dSamplesPerCycle;
        double dValue = 0.0;

        m_iEngineSound.reset();

        for (int iSoundIndex = 0; iSoundIndex < m_dSoundNormalizedPosition.count(); iSoundIndex += 2)
        {
            if (m_dSoundNormalizedPosition[iSoundIndex] < 1.0)
            {
                double dSoundDurationS = m_dSoundNormalizedPosition[iSoundIndex + 1];
                double dAddValue = m_iEngineSound.getValue(m_dSoundNormalizedPosition[iSoundIndex]);
                double dNumSamplesForSound = dSoundDurationS * dSampleRate;
                double dSoundSecondsPerSample = dSoundDurationS / dNumSamplesForSound;

                if (iSoundIndex > 1) dAddValue *= 0.75;

                dValue += dAddValue;

                m_dSoundNormalizedPosition[iSoundIndex] += dSoundSecondsPerSample / dSoundDurationS;
            }

            if (m_dSoundNormalizedPosition[iSoundIndex] >= 1.0)
            {
                m_dSoundNormalizedPosition.removeAt(iSoundIndex);
                m_dSoundNormalizedPosition.removeAt(iSoundIndex);
                iSoundIndex -= 2;
            }
        }

        // Value *= 1.0 + (_Rand.NextDouble() / 20.0);

        if (dValue < -1.0) dValue = -1.0;
        if (dValue > 1.0) dValue = 1.0;

        int iSoundData = (int)(dValue * 32767.0);

        // Left
        baData[iSoundDataIndex++] = (char)((iSoundData >> 0) & 0xFF);
        baData[iSoundDataIndex++] = (char)((iSoundData >> 8) & 0xFF);

        // Right
        baData[iSoundDataIndex++] = (char)((iSoundData >> 0) & 0xFF);
        baData[iSoundDataIndex++] = (char)((iSoundData >> 8) & 0xFF);

        m_dSoundCycleNormalizedPosition += dCycleSecondsPerSample / dCycleDurationS;

        if (m_dSoundCycleNormalizedPosition >= 1.0)
        {
            m_dSoundCycleNormalizedPosition = 0.0;
            m_dSoundNormalizedPosition << 0.0;
            m_dSoundNormalizedPosition << (0.04 + (0.02 * (dBreakDownRPS / dEngineRPS)));
        }

        dTimeS += dCycleSecondsPerSample;
        dEngineRPS += dEngineAccelRPSS * dCycleSecondsPerSample;
    }

    return baData;
}
