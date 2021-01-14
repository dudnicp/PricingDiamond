#include "Option.hpp"

Option::Option(double T, int nbTimeSteps, int size, const PnlVect* weights) : 
	T_(T), 
	nbTimeSteps_(nbTimeSteps), 
	size_(size) 
{
	assetWeights_ = pnl_vect_copy(weights);
}

Option::~Option()
{
	pnl_vect_free(&assetWeights_);
}
