#include "BasketOption.hpp"

#include <algorithm>

double BasketOption::payoff(const PnlMat* path) const
{
	PnlVect* lastSpots = pnl_vect_create(size_);
	pnl_mat_get_row(lastSpots, path, path->m - 1);
	double payoff = pnl_vect_scalar_prod(lastSpots, assetWeights_) - strike_;
	return std::max(payoff, 0.0);
}

BasketOption::BasketOption(double T, int nbTimeSteps, int size, const PnlVect* weights, double strike) :
	Option(T, nbTimeSteps, size, weights), 
	strike_(strike)
{}

BasketOption* BasketOption::clone() const
{
	return new BasketOption(*this);
}

BasketOption::~BasketOption()
{}

