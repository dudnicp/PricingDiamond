#include "Transition.h"

#include <iostream>
#include <time.h>
#include "BlackScholesModel.hpp"
#include "MonteCarlo.hpp"
#include "DiamondOption.hpp"

using namespace std;


void Transition::diamondEuro(PnlVect*  price, PnlMat* deltas, int nbSamples, double T, double r, 
	double rho,PnlVect * spot, PnlVect* sigma)
{
}




