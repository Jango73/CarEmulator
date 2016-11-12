
#pragma once

// Std
#include "math.h"

// Qt
#include <QVector>

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

template <class T>
class CInterpolator
{
public:

    //-------------------------------------------------------------------------------------------------
    // Classes imbriqu�es
    //-------------------------------------------------------------------------------------------------

    class InterpolatorValue
    {
    public:

        InterpolatorValue()
        {
            dInput = 0.0;
        }

        InterpolatorValue(double NewInput, T NewOutput)
        {
            dInput = NewInput;
            tOutput = NewOutput;
        }

        double	dInput;
        T		tOutput;
    };

    //-------------------------------------------------------------------------------------------------
    // Constructors et destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    CInterpolator()
    {
        m_iLastIndex = 0;
    }

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //! Returns number of values
    int count() { return m_vValues.count(); }

    //! Returns the vector of values
    QVector<InterpolatorValue>& getValues() { return m_vValues; }

    T getValue(double input)
    {
        reset();
        return interpolateFromLast(input);
    }

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    void reset()
    {
        m_iLastIndex = 0;
    }

    //! Ajoute un pas d'interpolation
    //! Une valeur double donn�e est associ�e une valeur T
    void addValue(double input, T output)
    {
        m_vValues.append(InterpolatorValue(input, output));
    }

    void operator << (InterpolatorValue value)
    {
        m_vValues.append(value);
    }

    void shift(double dAmount)
    {
        for (int iIndex = 0; iIndex < m_vValues.count(); iIndex++)
        {
            m_vValues[iIndex].dInput += dAmount;

            if (m_vValues[iIndex].dInput > 1.0)
            {
                m_vValues.removeAt(iIndex);
                iIndex--;
            }
        }
    }

    void mult(T tAmount)
    {
        for (int iIndex = 0; iIndex < m_vValues.count(); iIndex++)
        {
            m_vValues[iIndex].tOutput *= tAmount;
        }
    }

    void randomize(double dAmount)
    {
        for (int iIndex = 0; iIndex < m_vValues.count(); iIndex++)
        {
            double dRandom = (double) qrand() / 32767.0;
            m_vValues[iIndex].tOutput *= ((dRandom * 2.0) * dAmount);
        }
    }

    //! Retourne la valeur T correspondant � la valeur double d'entr�e
    T interpolateFromLast(double input)
    {
        T output = T();

        if (m_vValues.count() == 0) return output;

        if (input < m_vValues[0].dInput) input = m_vValues[0].dInput;
        if (input > m_vValues[m_vValues.count() - 1].dInput) input = m_vValues[m_vValues.count() - 1].dInput;

        for (int iIndex = m_iLastIndex; iIndex < m_vValues.count(); iIndex++)
        {
            if (input >= m_vValues[iIndex].dInput)
            {
                if (iIndex < m_vValues.count() - 1)
                {
                    if (input <= m_vValues[iIndex + 1].dInput)
                    {
                        double input1 = m_vValues[iIndex + 0].dInput;
                        double input2 = m_vValues[iIndex + 1].dInput;
                        double inputRange = input2 - input1;

                        T output1 = m_vValues[iIndex + 0].tOutput;
                        T output2 = m_vValues[iIndex + 1].tOutput;
                        T outputRange = output2 - output1;

                        double factor = (input - input1) / inputRange;
                        output = output1 + (outputRange * factor);

                        m_iLastIndex = iIndex;
                        break;
                    }
                }
                else
                {
                    output = m_vValues[iIndex].tOutput;
                }
            }
        }

        return output;
    }

    bool compareByInput(CInterpolator<T>::InterpolatorValue& a, CInterpolator<T>::InterpolatorValue& b)
    {
        return a.dInput < b.dInput;
    }

    void Merge(CInterpolator<T> tInput)
    {
        for (int newIndex = 0; newIndex < tInput.m_vValues; newIndex++)
        {
            bool Found = false;

            for (int localIndex = 0; localIndex < m_vValues; localIndex++)
            {
                if (m_vValues[localIndex].Input == tInput.m_vValues[newIndex].dInput)
                {
                    m_vValues[localIndex].Output += tInput.m_vValues[newIndex].Output;

                    if (m_vValues[localIndex].Output < -1.0) m_vValues[localIndex].Output = -1.0;
                    if (m_vValues[localIndex].Output > 1.0) m_vValues[localIndex].Output = 1.0;

                    Found = true;
                }
            }

            if (Found == false)
            {
                m_vValues << tInput.m_vValues[newIndex];
            }
        }

        qSort(m_vValues.begin(), m_vValues.end(), compareByInput);
    }

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    int                         m_iLastIndex;
    QVector<InterpolatorValue>	m_vValues;
};

}
