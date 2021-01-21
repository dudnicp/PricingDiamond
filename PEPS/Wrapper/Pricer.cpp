#include "pch.h"

#include "Pricer.hpp"


using namespace MonteCarloPricer;
namespace Pricer {
	PricerClass::PricerClass(PnlMat* simulatedMarketData, PnlVect* observationDates, PnlVect* currentSpots, PnlVect* changeRates) {
		//TODO
	}

	void PricerClass::getPrice(double date) {
		int nbTimeSteps = observationDates_->size;
		int size = currentSpots_->size;

		size_t t = 0;
		while (t < nbTimeSteps && pnl_vect_get(this->observationDates_, t) < date) {
			t++;
		}

		PnlMat* past = pnl_mat_create(nbTimeSteps + 1, size);

		for (size_t i = 0; i < t; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				pnl_mat_set(past, i, j, pnl_mat_get(this->simulatedMarketData_, i, j));
			}
		}


		this->monteCarlo->price(past, date, this->price, this->std_dev);
	}

	void PricerClass::getDelta(double date) {
		int nbTimeSteps = observationDates_->size;
		int size = currentSpots_->size;

		size_t t = 0;
		while (t < nbTimeSteps && pnl_vect_get(this->observationDates_, t) < date) {
			t++;
		}

		PnlMat* past = pnl_mat_create(nbTimeSteps + 1, size);

		for (size_t i = 0; i < t; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				pnl_mat_set(past, i, j, pnl_mat_get(this->simulatedMarketData_, i, j));
			}
		}


		this->monteCarlo->delta(past, date, this->delta, this->std_dev_vect);

	}
}

