#pragma once
#define DLLEXP   __declspec( dllexport )
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

namespace Transition
{
	DLLEXP void diamondEuro(double &price, PnlVect *deltas, int nbSamples, double T, 
		PnlVect *spots, PnlMat *sigma, PnlVect *mu);
};

