#include "pch.h"

#include "BlackScholesModel.hpp"
#include "DiamondOption.hpp"
#include "BasketOption.hpp"
#include "Wrapper.h"


namespace Wrapper
{
	Pricer::Pricer(array<double, 1>^ changeRates, array<int, 1>^ observationDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends)
	{
		int nbObservationDates = observationDates->Length;
		int nbShares = sigmas->Length;

		PnlVect* changeRatesPnl = pnl_vect_create(changeRates->Length);
		for (int i = 0; i < changeRatesPnl->size; i++)
		{
			pnl_vect_set(changeRatesPnl, i, changeRates[i]);
		}
		PnlVect* observationDatesPnl = pnl_vect_create(nbObservationDates);
		for (int i = 0; i < nbObservationDates; i++)
		{
			pnl_vect_set(observationDatesPnl, i, observationDates[i]);
		}
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

		PnlVect* weights = pnl_vect_create_from_scalar(nbShares, 1.0 / nbShares);
		DiamondOption* diamond = new DiamondOption(observationDatesPnl, changeRatesPnl, nbShares, weights);

		PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
		pnl_rng_sseed(rng, 0);
		double fdStep = 0.01;
		int nbSamples = 50000;
		monteCarlo_ = new MonteCarlo(bsm, diamond, rng, fdStep, nbSamples);

		pnl_vect_free(&observationDatesPnl);
		pnl_vect_free(&changeRatesPnl);
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
		int nbShares = monteCarlo_->opt_->size_;
		PnlVect* observationDates = monteCarlo_->opt_->observationDates_;
		PnlMat* past = pnl_mat_create_from_scalar(observationDates->size, nbShares, 0);

		int i = 0;
		for (i; pnl_vect_get(observationDates, i) < date; i++)
		{
			for (int d = 0; d < nbShares; d++)
			{
				pnl_mat_set(past, i, d, marketData[i, (int)pnl_vect_get(observationDates, i)]);
			}
		}
		for (int d = 0; d < nbShares; d++)
		{
			pnl_mat_set(past, i, d, marketData[i, date]);
		}

		return past;
	}

	double Pricer::price(int date, array<double, 2>^ marketData)
	{
		double price = 0;

		PnlMat* past = buildPast(date, marketData);
		monteCarlo_->price(past, date, price);

		pnl_mat_free(&past);

		return price;
	}

	array<double, 1>^ Pricer::deltas(int date, array<double, 2>^ marketData)
	{
		int nbShares = marketData->GetLength(1);
		auto deltas = gcnew array<double, 1>(nbShares);
		PnlMat* past = buildPast(date, marketData);

		PnlVect* deltasPnl = pnl_vect_create(nbShares);
		monteCarlo_->delta(past, date, deltasPnl);

		for (int i = 0; i < nbShares; i++)
		{
			deltas[i] = pnl_vect_get(deltasPnl, i);
		}

		pnl_mat_free(&past);
		pnl_vect_free(&deltasPnl);

		return deltas;
	}
	array<double, 2>^  MarketSimulator::SimulateMarket(int nbDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends)
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

	Pricer::~Pricer()
	{
		delete monteCarlo_;
	}
}

