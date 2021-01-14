#include "PerformanceOption.hpp"

#include <algorithm>

double PerformanceOption::payoff(const PnlMat* path) const
{
	PnlVect* currentSpots = pnl_vect_create(size_);
	PnlVect* previousSpots = pnl_vect_create(size_);
	double sum = 0.0;
	for (int i = 1; i <= nbTimeSteps_; i++)
	{
		pnl_mat_get_row(currentSpots, path, i);
		pnl_mat_get_row(previousSpots, path, i - 1);

		sum += std::max(
			pnl_vect_scalar_prod(currentSpots, assetWeights_) / pnl_vect_scalar_prod(previousSpots, assetWeights_) - 1, 
			0.0);
	}

	return 1.0 + sum;
}

PerformanceOption::PerformanceOption(double T, int nbTimeSteps, int size, const PnlVect* weights) :
	Option(T, nbTimeSteps, size, weights)
{}

PerformanceOption* PerformanceOption::clone() const
{
	return new PerformanceOption(*this);
}

PerformanceOption::~PerformanceOption()
{}
