#include "Option.hpp"

Option::Option(double T, int nbTimeSteps, int size, const PnlVect* weights) : 
	T_(T), 
	nbTimeSteps_(nbTimeSteps), 
	size_(size) 
{
	assetWeights_ = pnl_vect_copy(weights);
}

Option::Option(const Option& other) :
	T_(other.T_),
	nbTimeSteps_(other.nbTimeSteps_),
	size_(other.size_)
{
	assetWeights_ = pnl_vect_copy(other.assetWeights_);
}

Option::~Option()
{
	pnl_vect_free(&assetWeights_);
}
