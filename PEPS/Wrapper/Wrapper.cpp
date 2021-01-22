#include "pch.h"

#include "BlackScholesModel.hpp"
#include "DiamondOption.hpp"
#include "Wrapper.hpp"


namespace Wrapper {

	Pricer::Pricer(System::DateTime origin, array<double, 1>^ changeRates, array<int, 1>^ observationDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends)
	{
		origin_ = origin;
		nbObservationDates_ = observationDates->Length;
		nbShares_ = sigmas->Length;

		changeRates_ = pnl_vect_create(changeRates->Length);
		for (int i = 0; i < changeRates_->size; i++)
		{
			pnl_vect_set(changeRates_, i, changeRates[i]);
		}

		observationDates_ = pnl_vect_create(nbObservationDates_);
		for (int i = 0; i < nbObservationDates_; i++)
		{
			pnl_vect_set(observationDates_, i, observationDates[i]);
		}

		PnlVect* sigmasPnl = pnl_vect_create(nbShares_);
		for (int i = 0; i < nbShares_; i++)
		{
			pnl_vect_set(sigmasPnl, i, sigmas[i]);
		}

		PnlVect* spotsPnl = pnl_vect_create(nbShares_);
		for (int i = 0; i < nbShares_; i++)
		{
			pnl_vect_set(spotsPnl, i, initialSpots[i]);
		}

		PnlVect* trendsPnl = pnl_vect_create(nbShares_);
		for (int i = 0; i < nbShares_; i++)
		{
			pnl_vect_set(trendsPnl, i, trends[i]);
		}

		BlackScholesModel* bsm = new BlackScholesModel(nbShares_, r, rho, sigmasPnl, spotsPnl, trendsPnl);

		PnlVect* weights = pnl_vect_create_from_scalar(nbShares_, 1.0 / nbShares_);
		DiamondOption* diamond = new DiamondOption(observationDates_, changeRates_, nbShares_, weights);

		PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
		pnl_rng_sseed(rng, (int)time(NULL));
		double fdStep = 0.01;
		int nbSamples = 50000;
		monteCarlo_ = new MonteCarlo(bsm, diamond, rng, fdStep, nbSamples);

		pnl_vect_free(&sigmasPnl);
		pnl_vect_free(&spotsPnl);
		pnl_vect_free(&trendsPnl);
		pnl_vect_free(&weights);
		pnl_rng_free(&rng);
		delete bsm;
		delete diamond;
	}

	PnlMat* Pricer::buildPast(int date, const array<double, 2>^ marketData)
	{
		PnlMat* past = pnl_mat_create_from_scalar(nbObservationDates_, nbShares_, 0);

		int i = 0;
		for (i; pnl_vect_get(observationDates_, i) < date; i++)
		{
			for (int d = 0; d < nbShares_; d++)
			{
				pnl_mat_set(past, i, d, marketData[i, (int)pnl_vect_get(observationDates_, i)]);
			}
		}
		for (int d = 0; d < nbShares_; d++)
		{
			pnl_mat_set(past, i, d, marketData[i, date]);
		}

		return past;
	}

	double Pricer::price(const System::DateTime date, const array<double, 2>^ marketData)
	{
		double price = 0;
		
		int dateIndex = (date - origin_).Days;
		PnlMat* past = buildPast(dateIndex, marketData);
		monteCarlo_->price(past, dateIndex, price);

		pnl_mat_free(&past);

		return price;
	}

	array<double, 1>^ Pricer::deltas(System::DateTime date, const array<double, 2>^ marketData)
	{
		auto deltas = gcnew array<double, 1>(nbShares_);

		int dateIndex = (date - origin_).Days;
		PnlMat* past = buildPast(dateIndex, marketData);

		PnlVect* deltasPnl = pnl_vect_create(nbShares_);
		monteCarlo_->delta(past, dateIndex, deltasPnl);

		for (int i = 0; i < nbShares_; i++)
		{
			deltas[i] = pnl_vect_get(deltasPnl, i);
		}

		pnl_mat_free(&past);
		pnl_vect_free(&deltasPnl);

		return deltas;
	}
	array<double, 2>^ SimulateMarket(int nbDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends)
	{
		int nbShares = sigmas->Length;

		PnlVect* sigmasPnl = pnl_vect_create(nbShares);
		for (int i = 0; i < nbShares; i++)
		{
			pnl_vect_set(sigmasPnl, i, sigmas[i]);
		}

		PnlVect* spotsPnl = pnl_vect_create(nbShares);
		for (int i = 0; i < nbShares; i++)
		{
			pnl_vect_set(spotsPnl, i, initialSpots[i]);
		}

		PnlVect* trendsPnl = pnl_vect_create(nbShares);
		for (int i = 0; i < nbShares; i++)
		{
			pnl_vect_set(trendsPnl, i, trends[i]);
		}

		BlackScholesModel* bsm = new BlackScholesModel(nbShares, r, rho, sigmasPnl, spotsPnl, trendsPnl);

		PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
		pnl_rng_sseed(rng, (int)time(NULL));

		PnlMat* simulatedMarket = pnl_mat_create(nbDates, nbShares);
		bsm->simul_market(simulatedMarket, rng);


		auto marketData = gcnew array<double, 2>(nbDates, nbShares);
		for (int i = 0; i < nbDates; i++)
		{
			for (int d = 0; d < nbShares; d++)
			{
				marketData[i, d] = pnl_mat_get(simulatedMarket, i, d);
			}
		}

		pnl_vect_free(&sigmasPnl);
		pnl_vect_free(&spotsPnl);
		pnl_vect_free(&trendsPnl);
		pnl_rng_free(&rng);
		delete bsm;

		return marketData;
	}
}

