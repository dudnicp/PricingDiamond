#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"

#include "MonteCarlo.hpp"

namespace Pricer {

	public ref class PricerClass
	{
	private:
		MonteCarlo* monteCarlo;
		PnlMat* simulatedMarketData_;
		PnlVect* observationDates_;
		PnlVect* currentSpots_;
		PnlVect* changeRates_;

		double& price;
		double& std_dev;
		PnlVect* delta;
		PnlVect* std_dev_vect;

	public:
		PricerClass(PnlMat* simulatedMarketData, PnlVect* observationDates, PnlVect* currentSpots, PnlVect* changeRates);
		void getPrice(double date);
		void getDelta(double date);
	};
}
