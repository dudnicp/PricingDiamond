#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"

public ref class Pricer
{
	private:
		PnlMat* simulatedMarketData_;
		PnlVect* observationDates_;
		PnlVect* currentSpots_;
		PnlVect* changeRates_;
};

