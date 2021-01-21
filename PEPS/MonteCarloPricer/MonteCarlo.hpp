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
        Option* opt_;            /// Option which price is computed
        PnlRng* rng_;            /// Random number generator
        double fdStep_;          /// Finite difference step
        int nbSamples_;          /// Number of Monte-Carlo samples
        PnlMat* assetPath_;      ///
        PnlMat* shiftedPath_;    ///

        /// <summary>
        /// Computes the initial (date 0) price of the option
        /// </summary>
        /// <param name="estimatedPrice">Price returned by the Monte Carlo estimator</param>
        /// <param name="std_dev">Price standard deviation</param>
        DLLEXP void price(double& estimatedPrice, double& std_dev);

        /// <summary>
        /// Computes the price of the option at the date t
        /// </summary>
        /// <param name="past">Underlying asset trajectory until t</param>
        /// <param name="t">Computation date</param>
        /// <param name="estimatedPrice">Price returned by the Monte Carlo estimator</param>
        /// <param name="std_dev">Price standard deviation</param>
        DLLEXP void price(const PnlMat* past, int dayIndex, double& estimatedPrice, double& std_dev);

        /// <summary>
        /// Computes the initial deltas of the option
        /// </summary>
        /// <param name="delta">Deltas vector returned by the Monte Carlo estimator</param>
        /// <param name="std_dev">Deltas standard deviation</param>
        DLLEXP void delta(PnlVect* delta, PnlVect* std_dev);

        /// <summary>
        /// Computes the option deltas at date t
        /// </summary>
        /// <param name="past">Underlying asset trajectory until t</param>
        /// <param name="t">Computation date</param>
        /// <param name="delta">Deltas vector returned by the Monte Carlo estimator</param>
        /// <param name="std_dev">Deltas standard deviation</param>
        DLLEXP void delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev);

        /// <summary>
        /// Coomptues the profit and loss of the market trajectory according to the model
        /// </summary>
        /// <param name="marketPath"> Historical trajectories of the market</param>
        /// <param name="T"> Maturity </param>
        /// <param name="N"> Number of date of rebalancement </param>
        /// <param name="p0"> initial value in € set in the portfolio</param>
        /// <returns> The value of the profit and loss of the historical trajectory of the market</returns>
        DLLEXP double profitAndLoss(const PnlMat* marketPath);

        /// <summary>
        /// Constructor, creates a Monte-Carlo estimator
        /// </summary>
        /// <param name="mod">Black-Scholes model used for generating asset trajectories</param>
        /// <param name="opt">Option which price is computed</param>
        /// <param name="rng">Random number generator</param>
        /// <param name="fdStep">Finite Difference step</param>
        /// <param name="nbSamples">Number of Monte-Carlo samples</param>
        DLLEXP MonteCarlo(const BlackScholesModel* mod, const Option* opt, PnlRng* rng, double fdStep, int nbSamples);

        /// <summary>
        /// Destructor
        /// </summary>
        DLLEXP ~MonteCarlo();

        void priceAndDelta(const PnlMat* past, int dayIndex, double& price, PnlVect* delta, PnlVect* changeRate);
};
