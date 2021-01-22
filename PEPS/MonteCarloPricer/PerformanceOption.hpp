#pragma once
#define DLLEXP   __declspec( dllexport )
#include "Option.hpp"

/// <summary>
/// Class representing a Performance Option
/// </summary>
class PerformanceOption : public Option
{
public:
	PnlVect* currentSpots_;
	PnlVect* previousSpots_;

	DLLEXP virtual double payoff(const PnlMat* path) const;

	/// <summary>
	/// Creates a Performance Option
	/// </summary>
	/// <param name="T">Option maturity</param>
	/// <param name="nbTimeSteps">Number of discretization steps</param>
	/// <param name="size">size of the model</param>
	DLLEXP PerformanceOption(int size, const PnlVect* weights,
		PnlVect* observationDates, PnlVect* changeRate);

	DLLEXP PerformanceOption(const PerformanceOption& other);

	DLLEXP virtual PerformanceOption* clone() const;

	DLLEXP ~PerformanceOption();
};



