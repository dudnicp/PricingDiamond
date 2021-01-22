#include "AsianOption.hpp"
#include <iostream>

double AsianOption::payoff(const PnlMat* path) const
{
	pnl_mat_sum_vect(aux_, path, 'r');
	pnl_vect_div_scalar(aux_, (double)observationDates_->size);
	double payoff = pnl_vect_scalar_prod(aux_, assetWeights_) - strike_;
	return std::max(payoff, 0.0);
}

AsianOption::AsianOption(int size, const PnlVect* weights, double strike,
	PnlVect* observationDates, PnlVect* changeRate) : Option(size, weights, observationDates, changeRate),
	strike_(strike)
{
	aux_ = pnl_vect_create(size_);
}

AsianOption::AsianOption(const AsianOption& other) : Option(other)
{
	aux_ = pnl_vect_copy(other.aux_);
	strike_ = other.strike_;
}

AsianOption* AsianOption::clone() const
{
	return new AsianOption(*this);
}

AsianOption::~AsianOption()
{
	pnl_vect_free(&assetWeights_);
	pnl_vect_free(&observationDates_);
	pnl_vect_free(&changeRate_);
	pnl_vect_free(&aux_);
}