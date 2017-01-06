
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
    // Classes imbriquées
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
    // Constructors and destructor
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

    void clear()
    {
        reset();
        m_vValues.clear();
    }

    void reset()
    {
        m_iLastIndex = 0;
    }

    //! Ajoute un pas d'interpolation
    //! Une valeur double donnée est associée une valeur T
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

    //! Retourne la valeur T correspondant à la valeur double d'entrée
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

    void merge(CInterpolator<T> tInput)
    {
        for (int newIndex = 0; newIndex < tInput.m_vValues.count(); newIndex++)
        {
            for (int localIndex = 0; localIndex < m_vValues.count(); localIndex++)
            {
                if (m_vValues[localIndex].dInput == tInput.m_vValues[newIndex].dInput)
                {
                    m_vValues[localIndex].tOutput += tInput.m_vValues[newIndex].tOutput;

                    if (m_vValues[localIndex].tOutput < -1.0) m_vValues[localIndex].tOutput = -1.0;
                    if (m_vValues[localIndex].tOutput >  1.0) m_vValues[localIndex].tOutput =  1.0;

                    break;
                }
                else if
                        (
                         m_vValues[localIndex].dInput < tInput.m_vValues[newIndex].dInput
                         &&
                         (
                             localIndex == m_vValues.count() - 1 ||
                             m_vValues[localIndex + 1].dInput > tInput.m_vValues[newIndex].dInput
                             )
                         )
                {
                    m_vValues.insert(localIndex + 1, tInput.m_vValues[newIndex]);

                    break;
                }
            }
        }
    }

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    int                         m_iLastIndex;
    QVector<InterpolatorValue>	m_vValues;
};

}
