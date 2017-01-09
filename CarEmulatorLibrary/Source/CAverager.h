
#pragma once

// Qt
#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QFile>

//-------------------------------------------------------------------------------------------------

template <class T>
class CAverager
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
	CAverager(int iMaxValues = 5)
	: m_iMaxValues(iMaxValues)
	{
	}

    //! Destructor
	virtual ~CAverager()
	{
	}

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //! Returns the average of stored values
    T getAverage() const
    {
        if (m_mValues.count() == 0)
        {
            return (T) 0;
        }

        T returnValue = (T) 0;

        foreach (T iterValue, m_mValues)
        {
            returnValue += iterValue;
        }

        return returnValue / (T) m_mValues.count();
    }

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Clear internal values
	void reset()
	{
		m_mValues.clear();
	}

    //! Adds a value to average
	void append(const T& value)
	{
		m_mValues.append(value);

		if (m_mValues.count() > m_iMaxValues)
		{
			m_mValues.remove(0);
		}
	}

protected:

    int			m_iMaxValues;			// Maximum number of values to store
    QVector<T>	m_mValues;				// The values to average
};
