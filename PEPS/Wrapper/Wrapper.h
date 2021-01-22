#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"

#include "MonteCarlo.hpp"

namespace Wrapper
{

	public ref class Pricer
	{

	private:
		static MonteCarlo* monteCarlo_;

		static PnlMat* buildPast(int date, const array<double, 2>^ marketData);

	public:
		static void InitPricer(array<double, 1>^ changeRates, array<int, 1>^ observationDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends);

		static double price(int date, array<double, 2>^ marketData);
		static array<double, 1>^ deltas(int date, array<double, 2>^ marketData);
	};

	public ref class MarketSimulator
	{
	public:
		static array<double, 2>^ SimulateMarket(int nbDates, double r, double rho, array<double, 1>^ sigmas, array<double, 1>^ initialSpots, array<double, 1>^ trends);
	};
}
