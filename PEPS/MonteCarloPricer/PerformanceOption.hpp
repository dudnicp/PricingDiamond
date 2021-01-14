#pragma once

#include "Option.hpp"

/// <summary>
/// Class representing a Performance Option
/// </summary>
class PerformanceOption : public Option
{
public:
	virtual double payoff(const PnlMat* path) const;

	/// <summary>
	/// Creates a Performance Option
	/// </summary>
	/// <param name="T">Option maturity</param>
	/// <param name="nbTimeSteps">Number of discretization steps</param>
	/// <param name="size">size of the model</param>
	PerformanceOption(double T, int nbTimeSteps, int size, const PnlVect* weights);

	~PerformanceOption();
};



