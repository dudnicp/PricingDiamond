#include "MonteCarlo.hpp"

void MonteCarlo::price(double& estimatedPrice, double& std_dev)
{
	double payoffSum = 0.0;
	double payoffSquaredSum = 0.0;
	PnlMat* assetPath = pnl_mat_create(opt_->nbTimeSteps_, opt_->size_);
	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, opt_->T_, opt_->nbTimeSteps_, rng_);
		double payoff = opt_->payoff(assetPath);
		payoffSum += payoff;
		payoffSquaredSum += std::pow(payoff, 2);
	}
	double auxExp = std::exp(-mod_->r_ * opt_->T_);
	estimatedPrice = auxExp * (payoffSum / nbSamples_);
	std_dev = std::pow(auxExp, 2) * payoffSquaredSum / nbSamples_ - std::pow(estimatedPrice, 2);
}

MonteCarlo::MonteCarlo(const BlackScholesModel* mod, const Option* opt, const PnlRng* rng, double fdStep, int nbSamples)
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
