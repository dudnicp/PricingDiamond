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
	int d, i;
	double payoffShiftPlusH, payoffShiftMinusH;
	pnl_vect_set_zero(delta);
	pnl_vect_set_zero(std_dev);

	for (i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, opt_->T_, opt_->nbTimeSteps_, rng_);
		pnl_mat_clone(shiftedPath, assetPath);
		for (d = 0; d < opt_->size_; d++)
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
	int d;
	int shiftIndex = (int)std::ceil(t / timestep);

	for (int i = 0; i < nbSamples_; i++)
	{
		mod_->asset(assetPath, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);
		pnl_mat_clone(shiftedPath, assetPath);
		for (d = 0; d < opt_->size_; d++)
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


double MonteCarlo::profitAndLoss(const PnlMat* marketPath, double T, double N)
{
	int size = marketPath->n, timeIter, i = 0;
	double H = (double)marketPath->m - 1, stepInN = H/N;
	double t; // date dans le numéraire N
	double V = 0, aux = exp(mod_->r_*T/H);
	double payoff, p0, std_dev_value;
	price(p0, std_dev_value);

	/*Calcul des deltas sur les H dates*/
	PnlMat* deltas = pnl_mat_create((int)H+1, size);
	PnlMat* past = pnl_mat_create((int)N + 1, size);
	PnlVect* delta_t = pnl_vect_create(size);
	PnlVect* std_dev = pnl_vect_create(size);
	PnlVect* pathGetter = pnl_vect_create(size);
	PnlVect* lastDelta = pnl_vect_create(size);
	for (timeIter = 0; timeIter <= H; timeIter++)
	{
		t = timeIter * N / H;
		/*On remplit avec la valeur en t, les valeurs précédentes étant déja enregistrées*/
		pnl_mat_get_row(pathGetter, marketPath, timeIter);
		pnl_mat_set_row(past, pathGetter, (int)floor(t));

		pnl_vect_print(pathGetter);

		/*On apelle la fonction delta pour remplir le vecteur*/
		this->delta(past, t, delta_t, std_dev);
		pnl_mat_set_row(deltas, delta_t, timeIter);

		pnl_vect_print(delta_t);

		if (timeIter == 0)
		{
			V = p0 - pnl_vect_scalar_prod(delta_t, pathGetter);
			lastDelta = pnl_vect_copy(delta_t);
		}
		else 
		{
			pnl_vect_minus_vect(delta_t, lastDelta); // On met dans delta delta-lastdelta
			V *= aux;
			V -= pnl_vect_scalar_prod(delta_t, pathGetter);
			pnl_mat_get_row(lastDelta, deltas, timeIter); // On met dans lastDelta le dernier vecteur de delta calculé
		}
	}
	payoff = opt_->payoff(past);

	pnl_mat_free(&deltas);
	pnl_mat_free(&past);
	pnl_vect_free(&delta_t);
	pnl_vect_free(&std_dev);
	pnl_vect_free(&pathGetter);
	pnl_vect_free(&lastDelta);

	return V + pnl_vect_scalar_prod(lastDelta, pathGetter) - payoff;
}