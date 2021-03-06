#pragma once

#include "Option.hpp"
#include <algorithm>

/// <summary>
/// Class representing a Asian Option
/// </summary>
class AsianOption : public Option
{
public:
	double strike_; /// Option strike

	virtual double payoff(const PnlMat* path) const;

	/// <summary>
	/// Creates a Asian Option
	/// </summary>
	/// <param name="T">Option maturity</param>
	/// <param name="nbTimeSteps">Number of discretization steps</param>
	/// <param name="size">size of the model</param>
	/// <param name="strike">Option strike</param>
	AsianOption(double T, int nbTimeSteps, int size, const PnlVect* weights, double strike);

	virtual AsianOption* clone() const;

	~AsianOption();
};

