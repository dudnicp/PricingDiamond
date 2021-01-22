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
	PnlVect* aux_;

	DLLEXP virtual double payoff(const PnlMat* path) const;

	DLLEXP BasketOption(const BasketOption& other);

	/// <summary>
	/// Creates a Basket Option
	/// </summary>
	/// <param name="size">size of the model</param>
	/// <param name="strike">Option strike</param>
	DLLEXP BasketOption(int size, const PnlVect* weighs, double strike,
		PnlVect* observationDates, PnlVect* changeRate);

	DLLEXP virtual BasketOption* clone() const;

	DLLEXP ~BasketOption();
};


