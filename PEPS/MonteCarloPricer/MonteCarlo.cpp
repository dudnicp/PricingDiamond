#include "MonteCarlo.hpp"

void MonteCarlo::price(double& estimatedPrice, double& std_dev)
{
	double payoffSum = 0.0;
	double payoffSquaredSum = 0.0;
	double payoff;
	PnlMat* assetPath = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, opt_->T_, opt_->nbTimeSteps_, rng_);
		payoff = opt_->payoff(assetPath);
		payoffSum += payoff;
		payoffSquaredSum += std::pow(payoff, 2);
	}
	
	double discount = std::exp(-mod_->r_ * opt_->T_);
	double payoffMean = payoffSum / nbSamples_;
	estimatedPrice = discount * payoffMean;
	std_dev = std::sqrt(std::pow(discount, 2)/nbSamples_ * (payoffSquaredSum / nbSamples_ - std::pow(payoffMean, 2)));

	pnl_mat_free(&assetPath);
}

void MonteCarlo::price(const PnlMat* past, double t, double& estimatedPrice, double& std_dev)
{
	double payoffSum = 0.0;
	double payoffSquaredSum = 0.0;
	double payoff = 0.0;
	PnlMat* assetPath = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);
		payoff = opt_->payoff(assetPath);
		payoffSum += payoff;
		payoffSquaredSum += std::pow(payoff, 2);
	}

	double discount = std::exp(-mod_->r_ * (opt_->T_ - t));
	double payoffMean = payoffSum / nbSamples_;
	estimatedPrice = discount * payoffMean;
	std_dev = std::sqrt(std::pow(discount, 2) / nbSamples_ * (payoffSquaredSum / nbSamples_ - std::pow(payoffMean, 2)));

	pnl_mat_free(&assetPath);
}

void MonteCarlo::delta(PnlVect* delta, PnlVect* std_dev)
{
	PnlMat* assetPath = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
	PnlMat* shiftedPath = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
	double timestep = opt_->T_ / (opt_->nbTimeSteps_);

	double payoffShiftPlusH, payoffShiftMinusH;
	pnl_vect_set_zero(delta);
	pnl_vect_set_zero(std_dev);

	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, opt_->T_, opt_->nbTimeSteps_, rng_);
		for (int d = 0; d < opt_->size_; d++)
		{
			mod_->shiftAsset(shiftedPath, assetPath, d, fdStep_, 0);
			payoffShiftPlusH = opt_->payoff(shiftedPath);
			mod_->shiftAsset(shiftedPath, assetPath, d, -fdStep_, 0);
			payoffShiftMinusH = opt_->payoff(shiftedPath);
			mod_->shiftAsset(shiftedPath, assetPath, d, 0, 0);

			pnl_vect_set(delta, d, pnl_vect_get(delta, d) + payoffShiftPlusH - payoffShiftMinusH);
			pnl_vect_set(std_dev, d, pnl_vect_get(std_dev, d) + std::pow(payoffShiftPlusH - payoffShiftMinusH, 2));
		}
	}
	
	double aux = std::exp(-mod_->r_ * opt_->T_) / (2 * fdStep_);

	// Delta calculation
	pnl_vect_mult_scalar(delta, aux/nbSamples_);
	pnl_vect_div_vect_term(delta, mod_->spot_);

	// delta std_dev calculation
	pnl_vect_mult_scalar(std_dev, std::pow(aux, 2)/nbSamples_);
	auto f = [](double x, double y)
	{
		return x / std::pow(y, 2);
	};
	pnl_vect_map_vect_inplace(std_dev, mod_->spot_, f);

	auto g = [](double x, double y)
	{
		return x - std::pow(y, 2);
	};
	pnl_vect_map_vect_inplace(std_dev, delta, g);

	pnl_vect_div_scalar(std_dev, nbSamples_);
	pnl_vect_map_inplace(std_dev, std::sqrt);

	pnl_mat_free(&assetPath);
	pnl_mat_free(&shiftedPath);

}

void MonteCarlo::delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev)
{
	PnlMat* assetPath = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
	PnlMat* shiftedPath = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
	double timestep = (double)(opt_->T_ / (opt_->nbTimeSteps_));

	double payoffShiftPlusH, payoffShiftMinusH;
	pnl_vect_set_zero(delta);
	pnl_vect_set_zero(std_dev);

	int shiftIndex = (int)std::ceil(t / timestep);

	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);
		for (int d = 0; d < opt_->size_; d++)
		{
			mod_->shiftAsset(shiftedPath, assetPath, d, fdStep_, shiftIndex);
			payoffShiftPlusH = opt_->payoff(shiftedPath);
			mod_->shiftAsset(shiftedPath, assetPath, d, -fdStep_, shiftIndex);
			payoffShiftMinusH = opt_->payoff(shiftedPath);
			mod_->shiftAsset(shiftedPath, assetPath, d, 0, shiftIndex);

			pnl_vect_set(delta, d, pnl_vect_get(delta, d) + payoffShiftPlusH - payoffShiftMinusH);
			pnl_vect_set(std_dev, d, pnl_vect_get(std_dev, d) + std::pow(payoffShiftPlusH - payoffShiftMinusH, 2));
		}
	}

	double aux = std::exp(-mod_->r_ * (opt_->T_ - t)) / (2 * fdStep_);

	// Delta calculation
	pnl_vect_mult_scalar(delta, aux / nbSamples_);
	pnl_vect_div_vect_term(delta, mod_->spot_);

	// delta std_dev calculation
	pnl_vect_mult_scalar(std_dev, (double)(std::pow(aux, 2) / nbSamples_));
	auto f = [](double x, double y)
	{
		return x / std::pow(y, 2);
	};
	pnl_vect_map_vect_inplace(std_dev, mod_->spot_, f);
	auto g = [](double x, double y)
	{
		return x - std::pow(y, 2);
	};
	pnl_vect_map_vect_inplace(std_dev, delta, g);
	pnl_vect_div_scalar(std_dev, nbSamples_);
	pnl_vect_map_inplace(std_dev, std::sqrt);

	pnl_mat_free(&assetPath);
	pnl_mat_free(&shiftedPath);
}

MonteCarlo::MonteCarlo(const BlackScholesModel* mod, const Option* opt, PnlRng* rng, double fdStep, int nbSamples)
{
	mod_ = new BlackScholesModel(*mod);
	opt_ = opt->clone();
	rng_ = pnl_rng_copy(rng);
	fdStep_ = fdStep;
	nbSamples_ = nbSamples;
}

MonteCarlo::~MonteCarlo()
{
	delete mod_;
	delete opt_;
	pnl_rng_free(&rng_);
}
