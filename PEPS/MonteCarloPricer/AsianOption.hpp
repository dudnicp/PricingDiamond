#pragma once
#define DLLEXP   __declspec( dllexport )
#include "Option.hpp"
#include <algorithm>

/// <summary>
/// Class representing a Asian Option
/// </summary>
class AsianOption : public Option
{
public:
	double strike_; /// Option strike
	PnlVect* aux_;

	DLLEXP virtual double payoff(const PnlMat* path) const;

	DLLEXP AsianOption(const AsianOption& other);

	DLLEXP AsianOption(int size, const PnlVect* weights, double strike, PnlVect* observationDates);

	DLLEXP virtual AsianOption* clone() const;

	DLLEXP ~AsianOption();
};

