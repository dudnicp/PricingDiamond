#include "BasketOption.hpp"
#include <iostream>
#include <algorithm>

double BasketOption::payoff(const PnlMat* path) const
{
	pnl_mat_get_row(aux_, path, path->m - 1);
	double payoff = pnl_vect_scalar_prod(aux_, assetWeights_) - strike_;
	return std::max(payoff, 0.0);
}

BasketOption::BasketOption(double T, int nbTimeSteps, int size, const PnlVect* weights, double strike) :
	Option(T, nbTimeSteps, size, weights), 
	strike_(strike)
{
	aux_ = pnl_vect_create(size_);
}

BasketOption::BasketOption(const BasketOption& other) : Option(other)
{
	aux_ = pnl_vect_copy(other.aux_);
	strike_ = other.strike_;
}

BasketOption* BasketOption::clone() const
{
	return new BasketOption(*this);
}


BasketOption::~BasketOption()
{
	Option::~Option();
	pnl_vect_free(&aux_);
}

