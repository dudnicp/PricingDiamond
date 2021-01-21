#include "pch.h"
#include "Wrapper.h"
#include "pnl/pnl_vector.h";
#include "pnl/pnl_matrix.h";

namespace Wrapper {
	void WrapperClass::getPriceDiamondEuro(int sampleNb, double T, PnlVect *spots, PnlMat *sigma, PnlVect *mu) {
		double price;
		PnlVect *deltas = pnl_vect_create(24);
		this->price = price;
		for (int i = 0; i < 24; i++)
		{
			this->deltasArray[i] = pnl_vect_get(deltas, i);

		}
	}
}

