#include "DiamondOption.hpp"

DiamondOption::DiamondOption(PnlVect* observationDates, PnlVect* changeRate, int size,
	const PnlVect* weights): Option(size, weights, observationDates, changeRate)
{
	aux_ = pnl_vect_create_from_scalar(size, 0);
	getter_ = pnl_vect_create(size);
	spot_ = pnl_vect_create(size);
	constructedPath_ = pnl_mat_create(observationDates_->size, size);
}

DiamondOption::DiamondOption(const DiamondOption& other) : Option(other)
{
	aux_ = pnl_vect_copy(other.aux_);
	getter_ = pnl_vect_copy(other.getter_);
	spot_ = pnl_vect_copy(other.spot_);
	constructedPath_ = pnl_mat_copy(other.constructedPath_);
}

DiamondOption* DiamondOption::clone() const 
{
	return new DiamondOption(*this);
}

DiamondOption::~DiamondOption()
{
	Option::~Option();
	pnl_vect_free(&aux_);
	pnl_vect_free(&getter_);
	pnl_vect_free(&spot_);
	pnl_mat_free(&constructedPath_);
}

void DiamondOption::constructDiamond(PnlMat* constructedPath,const PnlMat* path) const
{
	int i, d;
	pnl_mat_get_row(spot_, path, 0);
	pnl_mat_set_row(constructedPath, spot_, 0);
	double maxValue;
	int maxIndex;
	for (i = 1; i < path->m; i ++)
	{
		for (d = 0; d < size_; d++)
		{
			if (pnl_vect_get(aux_, d) == 0) // if not fixed
			{
				pnl_mat_set(constructedPath, i, d, pnl_mat_get(path, i, d));
			}
			else // if fixed
			{
				pnl_mat_set(constructedPath, i, d, pnl_mat_get(constructedPath, i - 1, d));
			}
		}
		pnl_mat_get_row(getter_, path, i);
		searchMax(maxValue, maxIndex);
		pnl_vect_set(aux_, maxIndex, 1);
		pnl_mat_set(constructedPath, i, maxIndex, std::max(maxValue, 1.6 * pnl_vect_get(spot_, maxIndex)));
	}
	for (d = 0; d < size_; d++)
	{
		if (pnl_vect_get(aux_, d) == 0)
		{
			pnl_mat_set(constructedPath, i, d, std::max(pnl_mat_get(constructedPath, i, d), 0.6 * pnl_vect_get(spot_, d)));
		}
	}
}

void DiamondOption::searchMax(double& maxValue, int& maxIndex) const
{
	double perf, spot_d;
	maxValue = 0.0;
	maxIndex = 0;
	int d;
	for (d = 0; d < size_; d++)
	{
		if (pnl_vect_get(aux_, d) == 0) // asset not fixed yet
		{
			spot_d = pnl_vect_get(spot_, d);
			perf = (pnl_vect_get(getter_, d) - spot_d) / spot_d;
			if (perf > maxValue)
			{
				maxValue = perf;
				maxIndex = d;
			}
		}
	}
}

double DiamondOption::payoff(const PnlMat* path) const 
{
	int i;
	double payoff;
	constructDiamond(constructedPath_, path);
	for (i = 0; i < path->m; i++)
	{
		pnl_mat_get_row(getter_, constructedPath_, i);
		pnl_vect_set(aux_, i, pnl_vect_sum(getter_));
	}
	payoff = pnl_vect_max(aux_);
	return payoff;
}

