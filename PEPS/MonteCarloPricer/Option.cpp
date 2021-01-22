#include "Option.hpp"

Option::Option(int size, const PnlVect* weights, PnlVect* observationDates, PnlVect* changeRate) : 
	size_(size) 
{
	assetWeights_ = pnl_vect_copy(weights);
	observationDates_ = pnl_vect_copy(observationDates);
	lastObservedDay_ = (int)pnl_vect_get(observationDates, observationDates->size - 1);
	changeRate_ = pnl_vect_copy(changeRate);
}

Option::Option(const Option& other) :
	size_(other.size_)
{
	assetWeights_ = pnl_vect_copy(other.assetWeights_);
	observationDates_ = pnl_vect_copy(other.observationDates_);
	lastObservedDay_ = other.lastObservedDay_;
	changeRate_ = pnl_vect_copy(changeRate_);
}

Option::~Option()
{
	pnl_vect_free(&assetWeights_);
	pnl_vect_free(&observationDates_);
	pnl_vect_free(&changeRate_);
}
