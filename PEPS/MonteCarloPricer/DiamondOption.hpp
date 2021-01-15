#pragma once

#include "Option.hpp"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <stdint.h>

/// <summary>
/// Class representing Diamond FCP
/// </summary>
class DiamondOption : Option
{
public:

	PnlVectInt* constatationDates_;
	PnlVect* changeRate_;


	/// <summary>
	/// Creates a Diamond FCP
	/// </summary>
	/// <param name="T">Option maturity</param>
	/// <param name="nbTimeSteps">Number of discretization steps</param>
	/// <param name="size">size of the model</param>
	DiamondOption(double T, int nbTimeSteps, PnlVectInt* constatationDates, PnlVect* changeRate,int size = 24, const PnlVect* weights = pnl_vect_create_from_double(24, 1 / 24));

	virtual DiamondOption* clone() const;

	~DiamondOption();

	double payoff(const PnlMat* path) const;

	void constructDiamond(PnlMat* observedValues,const  PnlMat* path) const;
};

