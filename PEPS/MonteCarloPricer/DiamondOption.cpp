#include "DiamondOption.hpp"

DiamondOption::DiamondOption(PnlVect* observationDates, PnlVect* changeRate, int size, const PnlVect* weights)
	: Option(size, weights, observationDates, changeRate)
{
	changeRate_ = pnl_vect_copy(changeRate);
}

DiamondOption* DiamondOption::clone() const 
{
	return new DiamondOption(*this);
}

DiamondOption::~DiamondOption()
{
	Option::~Option();
}

void DiamondOption::constructDiamond(const PnlMat* path) const
{
}

double DiamondOption::payoff(const PnlMat* path) const 
{
	return 0;
}

