
#pragma once

#include "CarEmulatorGlobal.h"

//-------------------------------------------------------------------------------------------------

namespace CarEmulator
{

class CAREMULATOR_SHARED_EXPORT CPIDController
{
public:

	//-------------------------------------------------------------------------------------------------
    // Constructeurs and destructeur
	//-------------------------------------------------------------------------------------------------

	//! Constructeur par défaut
	CPIDController(double dNewProportional, double dNewIntegral, double dNewDerivative);

	//! Destructeur
	virtual ~CPIDController();

	//-------------------------------------------------------------------------------------------------
	// Setters
	//-------------------------------------------------------------------------------------------------

	//! Définit la valeur cible à atteindre
	void setSetPoint(double value) { m_dSetPoint = value; }

	//! Définit le facteur proportionnel
	void setProportionalConstant(double value) { m_dProportionalConstant = value; }

	//! Définit le facteur intégral
	void setIntegralConstant(double value) { m_dIntegralConstant = value; }

	//! Définit le facteur dérivé
	void setDerivativeConstant(double value) { m_dDerivativeConstant = value; }

	//-------------------------------------------------------------------------------------------------
	// Getters
	//-------------------------------------------------------------------------------------------------

	//! Retourne la valeur cible à atteindre
    double getSetPoint() const { return m_dSetPoint; }

	//! Retourne le facteur proportionnel
    double getProportionalConstant() const { return m_dProportionalConstant; }

	//! Retourne le facteur intégral
    double getIntegralConstant() const { return m_dIntegralConstant; }

	//! Retourne le facteur dérivé
    double getDerivativeConstant() const { return m_dDerivativeConstant; }

	//! Retourne la valeur de sortie
    double getOutput() const { return m_dOutput; }

	//-------------------------------------------------------------------------------------------------
	// Méthode de contrôle
	//-------------------------------------------------------------------------------------------------

	//! Réinitialise le contrôleur
	void reset();

	//! Met à jour le contrôleur
	void update(double dCurrentValue, double dDeltaTimeMillis);

	//-------------------------------------------------------------------------------------------------
	// Propriétés
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
