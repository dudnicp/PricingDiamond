#include "MonteCarlo.hpp"
#include "DiamondOption.hpp"

MonteCarlo::MonteCarlo(const BlackScholesModel* mod, const Option* opt,
	PnlRng* rng, double fdStep, int nbSamples)
{
	mod_ = new BlackScholesModel(*mod);
	opt_ = opt->clone();
	rng_ = pnl_rng_copy(rng);
	fdStep_ = fdStep;
	nbSamples_ = nbSamples;
	assetPath_ = pnl_mat_create(opt_->observationDates_->size, opt_->size_);
	shiftedPath_ = pnl_mat_create(opt_->observationDates_->size, opt_->size_);
}

MonteCarlo::~MonteCarlo()
{
	delete mod_;
	delete opt_;
	pnl_rng_free(&rng_);
	pnl_mat_free(&shiftedPath_);
	pnl_mat_free(&assetPath_);
}


void MonteCarlo::price(const PnlMat* past, int dayIndex, double& estimatedPrice)
{
	double payoffSum = 0.0;
	double discount;
	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath_, dayIndex, rng_, past, opt_->observationDates_);
		payoffSum += opt_->payoff(assetPath_);
	}

	discount = std::exp(-mod_->r_ * ((double)opt_->lastObservedDay_ - dayIndex)/365.0);
	estimatedPrice = discount * payoffSum / nbSamples_;
}


void MonteCarlo::delta(const PnlMat* past, int dayIndex, PnlVect* delta)
{
	double payoffShiftPlusH, payoffShiftMinusH;
	double aux;
	pnl_vect_set_zero(delta);
	int d, i;
	int shiftIndex;
	for (shiftIndex = 0; pnl_vect_get(opt_->observationDates_, shiftIndex) < dayIndex; shiftIndex++);

	for (i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath_, dayIndex, rng_, past, opt_->observationDates_);
		pnl_mat_clone(shiftedPath_, assetPath_);
		for (d = 0; d < opt_->size_; d++)
		{
			mod_->shiftAsset(shiftedPath_, assetPath_, d, fdStep_, shiftIndex);
			payoffShiftPlusH = opt_->payoff(shiftedPath_);
			mod_->shiftAsset(shiftedPath_, assetPath_, d, -fdStep_, shiftIndex);
			payoffShiftMinusH = opt_->payoff(shiftedPath_);
			mod_->shiftAsset(shiftedPath_, assetPath_, d, 0, shiftIndex);
			pnl_vect_set(delta, d, pnl_vect_get(delta, d) + payoffShiftPlusH - payoffShiftMinusH);
		}
	}

	aux = std::exp(-mod_->r_ * ((double)opt_->lastObservedDay_ - (double)dayIndex) / 365.0)
		/(2.0*nbSamples_*fdStep_);

	pnl_vect_mult_scalar(delta, aux);
	pnl_vect_div_vect_term(delta, mod_->spot_);
}

void MonteCarlo::priceAndDelta(const PnlMat* past, int dayIndex, double& price, PnlVect* delta, PnlVect* changeRate)
{
	double payoffShiftPlusH, payoffShiftMinusH, payoff = 0;
	double aux;
	pnl_vect_set_zero(delta);
	int d, i;
	int shiftIndex;
	for (shiftIndex = 0; pnl_vect_get(opt_->observationDates_, shiftIndex) < dayIndex; shiftIndex++);

	for (i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath_, dayIndex, rng_, past, opt_->observationDates_);
		payoff += opt_->payoff(assetPath_);
		pnl_mat_clone(shiftedPath_, assetPath_);
		for (d = 0; d < opt_->size_; d++)
		{
			mod_->shiftAsset(shiftedPath_, assetPath_, d, fdStep_, shiftIndex);
			payoffShiftPlusH = opt_->payoff(shiftedPath_);
			mod_->shiftAsset(shiftedPath_, assetPath_, d, -fdStep_, shiftIndex);
			payoffShiftMinusH = opt_->payoff(shiftedPath_);
			mod_->shiftAsset(shiftedPath_, assetPath_, d, 0, shiftIndex);
			pnl_vect_set(delta, d, pnl_vect_get(delta, d) + payoffShiftPlusH - payoffShiftMinusH);
		}
	}

	aux = std::exp(-mod_->r_ * ((double)opt_->lastObservedDay_ - (double)dayIndex)/365.0);
	price = aux * payoff / nbSamples_;
	aux /= 2 * fdStep_;
	// Delta calculation
	pnl_vect_mult_scalar(delta, aux / nbSamples_);
	pnl_vect_div_vect_term(delta, mod_->spot_);
	pnl_vect_div_vect_term(delta, changeRate);
}
