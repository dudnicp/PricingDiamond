#pragma once
#define DLLEXP   __declspec( dllexport )

#include "Option.hpp"
#include "BlackScholesModel.hpp"
#include "pnl/pnl_random.h"

/// <summary>
/// Monte Carlo estimator used for pricing options and computing deltas 
/// </summary>
class MonteCarlo
{
    public:

        BlackScholesModel* mod_; /// Black-Scholes model used for generating asset trajectories
        Option* opt_;           /// Option which price is computed
        PnlRng* rng_;            /// Random number generator
        double fdStep_;          /// Finite difference step
        int nbSamples_;          /// Number of Monte-Carlo samples
        PnlMat* assetPath_;      ///
        PnlMat* shiftedPath_;    ///

        /// <summary>
        /// Coomptues the profit and loss of the market trajectory according to the model
        /// </summary>
        /// <param name="marketPath"> Historical trajectories of the market</param>
        /// <param name="T"> Maturity </param>
        /// <param name="N"> Number of date of rebalancement </param>
        /// <param name="p0"> initial value in € set in the portfolio</param>
        /// <returns> The value of the profit and loss of the historical trajectory of the market</returns>
       // DLLEXP double profitAndLoss(const PnlMat* marketPath);

        DLLEXP void price(const PnlMat* past, int dayIndex, double& estimatedPrice);


        DLLEXP void delta(const PnlMat* past, int dayIndex, PnlVect* delta);
        /// <summary>
        /// Constructor, creates a Monte-Carlo estimator
        /// </summary>
        /// <param name="mod">Black-Scholes model used for generating asset trajectories</param>
        /// <param name="opt">Option which price is computed</param>
        /// <param name="rng">Random number generator</param>
        /// <param name="fdStep">Finite Difference step</param>
        /// <param name="nbSamples">Number of Monte-Carlo samples</param>
        DLLEXP MonteCarlo(const BlackScholesModel* mod, const Option* opt, PnlRng* rng,
            double fdStep, int nbSamples);

        /// <summary>
        /// Destructor
        /// </summary>
        DLLEXP ~MonteCarlo();

        DLLEXP void priceAndDelta(const PnlMat* past, int dayIndex, double& price, PnlVect* delta, PnlVect* changeRate);
};
