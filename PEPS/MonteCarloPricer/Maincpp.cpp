#include "MonteCarlo.hpp"
#include "DiamondOption.hpp"

int main()
{
	int nbObservationDates = 10;
	int nbShares = 4;

	PnlVect* changeRatesPnl = pnl_vect_create(2);
	for (int i = 0; i < changeRatesPnl->size; i++)
	{
		pnl_vect_set(changeRatesPnl, i, 1);
	}

	PnlVect* observationDatesPnl = pnl_vect_create(nbObservationDates);
	for (int i = 0; i < nbObservationDates; i++)
	{
		pnl_vect_set(observationDatesPnl, i, 10);
	}

	PnlVect* sigmasPnl = pnl_vect_create(nbShares);
	for (int i = 0; i < nbShares; i++)
	{
		pnl_vect_set(sigmasPnl, i, 0.2);
	}

	PnlVect* spotsPnl = pnl_vect_create(nbShares);
	for (int i = 0; i < nbShares; i++)
	{
		pnl_vect_set(spotsPnl, i, 100);
	}

	PnlVect* trendsPnl = pnl_vect_create(nbShares);
	for (int i = 0; i < nbShares; i++)
	{
		pnl_vect_set(trendsPnl, i, 0.04);
	}

	BlackScholesModel* bsm = new BlackScholesModel(nbShares, 0.01, 0, sigmasPnl, spotsPnl, trendsPnl);

	PnlVect* weights = pnl_vect_create_from_scalar(nbShares, 1.0 / nbShares);
	DiamondOption* diamond = new DiamondOption(observationDatesPnl, changeRatesPnl, nbShares, weights);

	PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
	pnl_rng_sseed(rng, 0);
	double fdStep = 0.01;
	int nbSamples = 50000;
	MonteCarlo* mc = new MonteCarlo(bsm, diamond, rng, fdStep, nbSamples);

	pnl_vect_free(&observationDatesPnl);
	pnl_vect_free(&changeRatesPnl);
	pnl_vect_free(&sigmasPnl);
	pnl_vect_free(&spotsPnl);
	pnl_vect_free(&trendsPnl);
	pnl_vect_free(&weights);
	pnl_rng_free(&rng);
	delete bsm;
	delete diamond;
	delete mc;

	return EXIT_SUCCESS;
}