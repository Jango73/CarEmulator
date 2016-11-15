
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CPIDController
{
public:

	//-------------------------------------------------------------------------------------------------
	// Constructeurs et destructeur
	//-------------------------------------------------------------------------------------------------

	//! Constructeur par d�faut
	CPIDController(double dNewProportional, double dNewIntegral, double dNewDerivative);

	//! Destructeur
	virtual ~CPIDController();

	//-------------------------------------------------------------------------------------------------
	// Setters
	//-------------------------------------------------------------------------------------------------

	//! D�finit la valeur cible � atteindre
	void setSetPoint(double value) { m_dSetPoint = value; }

	//! D�finit le facteur proportionnel
	void setProportionalConstant(double value) { m_dProportionalConstant = value; }

	//! D�finit le facteur int�gral
	void setIntegralConstant(double value) { m_dIntegralConstant = value; }

	//! D�finit le facteur d�riv�
	void setDerivativeConstant(double value) { m_dDerivativeConstant = value; }

	//-------------------------------------------------------------------------------------------------
	// Getters
	//-------------------------------------------------------------------------------------------------

	//! Retourne la valeur cible � atteindre
	double getSetPoint() { return m_dSetPoint; }

	//! Retourne le facteur proportionnel
	double getProportionalConstant() { return m_dProportionalConstant; }

	//! Retourne le facteur int�gral
	double getIntegralConstant() { return m_dIntegralConstant; }

	//! Retourne le facteur d�riv�
	double getDerivativeConstant() { return m_dDerivativeConstant; }

	//! Retourne la valeur de sortie
	double getOutput() { return m_dOutput; }

	//-------------------------------------------------------------------------------------------------
	// M�thode de contr�le
	//-------------------------------------------------------------------------------------------------

	//! R�initialise le contr�leur
	void reset();

	//! Met � jour le contr�leur
	void update(double dCurrentValue, double dDeltaTimeMillis);

	//-------------------------------------------------------------------------------------------------
	// Propri�t�s
	//-------------------------------------------------------------------------------------------------

protected:

	double m_dSetPoint;
	double m_dError;
	double m_dPreviousError;
	double m_dIntegral;
	double m_dDerivative;
	double m_dProportionalConstant;
	double m_dIntegralConstant;
	double m_dDerivativeConstant;
	double m_dOutput;
};

}
