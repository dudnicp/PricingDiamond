#pragma once
#define DLLEXP   __declspec( dllexport )
#include "Option.hpp"

/// <summary>
/// Class representing a Basket Option
/// </summary>
class BasketOption : public Option
{
	public:
		double strike_; /// Option strike

		DLLEXP virtual double payoff(const PnlMat* path) const;

		/// <summary>
		/// Creates a Basket Option
		/// </summary>
		/// <param name="T">Option maturity</param>
		/// <param name="nbTimeSteps">Number of discretization steps</param>
		/// <param name="size">size of the model</param>
		/// <param name="strike">Option strike</param>
		DLLEXP BasketOption(double T, int nbTimeSteps, int size, const PnlVect* weighs, double strike);

		DLLEXP virtual BasketOption* clone() const;

		DLLEXP ~BasketOption();
};

