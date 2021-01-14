#pragma once

#include "Option.hpp"
#include "BlackScholesModel.hpp"
#include "pnl/pnl_random.h"

/// <summary>
/// Monte Carlo estimator used for pricing options and computing deltas 
/// </summary>
class MonteCarlo
{
public:
    BlackScholesModel* mod_; /// Black-Scholes model
    Option* opt_; /// Option
    PnlRng* rng_; /// Random number generator
    double fdStep_; /// Finite difference step
    int nbSamples_; /// Number of Monte-Carlo samples

    /// <summary>
    /// Computes the initial (date 0) price of the option
    /// </summary>
    /// <param name="estimatedPrice">Price returned by the Monte Carlo estimator</param>
    /// <param name="std_dev">Price standard deviation</param>
    void price(double& estimatedPrice, double& std_dev);

    /// <summary>
    /// Computes the price of the option at the date t
    /// </summary>
    /// <param name="past">Underlying asset trajectory until t</param>
    /// <param name="t">Computation date</param>
    /// <param name="estimatedPrice">Price returned by the Monte Carlo estimator</param>
    /// <param name="std_dev">Price standard deviation</param>
    void price(const PnlMat* past, double t, double& estimatedPrice, double& std_dev);

    /// <summary>
    /// Computes the initial deltas of the option
    /// </summary>
    /// <param name="delta">Deltas vector returned by the Monte Carlo estimator</param>
    /// <param name="std_dev">Deltas standard deviation</param>
    void delta(PnlVect* delta, PnlVect* std_dev);

    /// <summary>
    /// Computes the option deltas at date t
    /// </summary>
    /// <param name="past">Underlying asset trajectory until t</param>
    /// <param name="t">Computation date</param>
    /// <param name="delta">Deltas vector returned by the Monte Carlo estimator</param>
    /// <param name="std_dev">Deltas standard deviation</param>
    void delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev);
};
