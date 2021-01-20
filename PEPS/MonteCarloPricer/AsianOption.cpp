#include "AsianOption.hpp"
#include <iostream>

double AsianOption::payoff(const PnlMat* path) const
{
	PnlVect* aux = pnl_vect_create(size_);
	pnl_mat_sum_vect(aux, path, 'r');
	pnl_vect_div_scalar(aux, (double)nbTimeSteps_ + 1.0);
	double payoff = pnl_vect_scalar_prod(aux, assetWeights_) - strike_;
	return std::max(payoff, 0.0);
}

AsianOption::AsianOption(double T, int nbTimeSteps, int size, const PnlVect* weights, double strike) :
	Option(T, nbTimeSteps, size, weights),
	strike_(strike)
{}

AsianOption* AsianOption::clone() const
{
	return new AsianOption(*this);
}

AsianOption::~AsianOption()
{}
