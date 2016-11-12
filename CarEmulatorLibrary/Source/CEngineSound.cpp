
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

    iTemp1.shift(0.11);
    iTemp1.randomize(0.75);
    m_iEngineSound.merge(iTemp1);

    iTemp2.shift(0.22);
    iTemp2.randomize(0.75);
    m_iEngineSound.merge(iTemp2);

    /*
    iTemp3.shift(0.33);
    iTemp3.randomize(0.75);
    m_iEngineSound.merge(iTemp3);
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

    double dEngineRPS = CUtils::RPMToRPS(m_pCar->sensors().currentRPM().value()) * 1;
    double dBreakDownRPS = CUtils::RPMToRPS(m_pCar->engineSettings().breakDownRPM()) * 1;
    double dEngineAccelRPSS = m_pCar->sensors().engineAccelerationRPSS().value() * 1;
    double dCycleSecondsPerSample = dBufferDurationS / iSamplesPerBuffer;
    double dTimeS = 0.0;
    int iSoundDataIndex = 0;

    for (int Index = 0; Index < iSamplesPerBuffer; Index++)
    {
        double SamplesPerCycle = (1.0 / dEngineRPS) * dSampleRate;
        double CycleDurationS = dCycleSecondsPerSample * SamplesPerCycle;
        double Value = 0.0;

        m_iEngineSound.reset();

        for (int SoundIndex = 0; SoundIndex < _SoundNormalizedPosition.count(); SoundIndex += 2)
        {
            if (_SoundNormalizedPosition[SoundIndex] < 1.0)
            {
                double SoundDurationS = _SoundNormalizedPosition[SoundIndex + 1];
                double AddValue = m_iEngineSound.getValue(_SoundNormalizedPosition[SoundIndex]);
                double NumSamplesForSound = SoundDurationS * dSampleRate;
                double SoundSecondsPerSample = SoundDurationS / NumSamplesForSound;

                if (SoundIndex > 1) AddValue *= 0.75;

                Value += AddValue;

                _SoundNormalizedPosition[SoundIndex] += SoundSecondsPerSample / SoundDurationS;
            }

            if (_SoundNormalizedPosition[SoundIndex] >= 1.0)
            {
                _SoundNormalizedPosition.removeAt(SoundIndex);
                _SoundNormalizedPosition.removeAt(SoundIndex);
                SoundIndex -= 2;
            }
        }

        // Value *= 1.0 + (_Rand.NextDouble() / 20.0);

        if (Value < -1.0) Value = -1.0;
        if (Value > 1.0) Value = 1.0;

        int SoundData = (int)(Value * 32767.0);

        // Left
        baData[iSoundDataIndex++] = (char)((SoundData >> 0) & 0xFF);
        baData[iSoundDataIndex++] = (char)((SoundData >> 8) & 0xFF);

        // Right
        baData[iSoundDataIndex++] = (char)((SoundData >> 0) & 0xFF);
        baData[iSoundDataIndex++] = (char)((SoundData >> 8) & 0xFF);

        _SoundCycleNormalizedPosition += dCycleSecondsPerSample / CycleDurationS;

        if (_SoundCycleNormalizedPosition >= 1.0)
        {
            _SoundCycleNormalizedPosition = 0.0;
            _SoundNormalizedPosition << 0.0;
            _SoundNormalizedPosition << (0.04 + (0.02 * (dBreakDownRPS / dEngineRPS)));
        }

        dTimeS += dCycleSecondsPerSample;
        dEngineRPS += dEngineAccelRPSS * dCycleSecondsPerSample;
    }

    return baData;
}
