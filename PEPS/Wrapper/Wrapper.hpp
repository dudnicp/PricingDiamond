#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"

#include "MonteCarlo.hpp"

namespace Wrapper {

	public ref class Pricer
	{

	private:
		MonteCarlo* monteCarlo_;
		PnlVect* observationDates_;
		PnlVect* changeRates_;
		int nbShares_;
		int nbObservationDates_;
		System::DateTime origin_;

		PnlMat* buildPast(int date, const array<double, 2>^ marketData);

	public:
		Pricer(System::DateTime origin, array<double, 1>^ changeRates, array<int, 1>^ observationDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends);

		double price(const System::DateTime date, const array<double, 2>^ marketData);
		array<double, 1>^ deltas(const System::DateTime date, const array<double, 2>^ marketData);
	};

	array<double, 2>^ SimulateMarket(int nbDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends);
}
