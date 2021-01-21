#include "PerformanceOption.hpp"

#include <algorithm>

double PerformanceOption::payoff(const PnlMat* path) const
{
	double sum = 0.0;
	for (int i = 1; i <= nbTimeSteps_; i++)
	{
		pnl_mat_get_row(currentSpots_, path, i);
		pnl_mat_get_row(previousSpots_, path, i - 1);

		sum += std::max(
			pnl_vect_scalar_prod(currentSpots_, assetWeights_) / pnl_vect_scalar_prod(previousSpots_, assetWeights_) - 1, 
			0.0);
	}

	return 1.0 + sum;
}

PerformanceOption::PerformanceOption(double T, int nbTimeSteps, int size, const PnlVect* weights) :
	Option(T, nbTimeSteps, size, weights)
{
	currentSpots_ = pnl_vect_create(size_);
	previousSpots_ = pnl_vect_create(size_);
}

PerformanceOption::PerformanceOption(const PerformanceOption& other) : Option(other)
{
	currentSpots_ = pnl_vect_copy(other.currentSpots_);
	previousSpots_ = pnl_vect_copy(other.previousSpots_);
}

PerformanceOption* PerformanceOption::clone() const
{
	return new PerformanceOption(*this);
}

PerformanceOption::~PerformanceOption()
{
	Option::~Option();
	pnl_vect_free(&currentSpots_);
	pnl_vect_free(&previousSpots_);
}
