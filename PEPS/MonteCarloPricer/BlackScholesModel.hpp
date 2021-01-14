#pragma once

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/// <summary>
/// Black-Scholes model used for generating assets price trajectories
/// </summary>
class BlackScholesModel
{
public:
    int size_;       /// number of assets in the model
    double r_;       /// interest rate
    double rho_;     /// correlation parameter
    PnlVect* sigma_; /// volatilties vector
    PnlVect* spot_;  /// inital underlying assets values

    /// <summary>
    /// Generates a trajectory for the model and stores it in path
    /// </summary>
    /// <param name="path">Contains the models trajectory. path is a matrix of size (nbTimeSteps + 1) x d</param>
    /// <param name="T">Maturity</param>
    /// <param name="nbTimeSteps">Number of observation dates</param>
    /// <param name="rng">Random number generator</param>
    void asset(PnlMat* path, double T, int nbTimeSteps, PnlRng* rng);

    /// <summary>
    /// Generates a trajectory for the model based on values anterior to t, and stores it in path
    /// </summary>
    /// <param name="path">Contains the models trajectory</param>
    /// <param name="t">Date until which model values are known</param>
    /// <param name="T">Maturity</param>
    /// <param name="nbTimeSteps">Number of observation dates</param>
    /// <param name="rng">Random number generator</param>
    /// <param name="past">Model values observed until t</param>
    void asset(PnlMat* path, double t, double T, int nbTimeSteps, PnlRng* rng, const PnlMat* past);

    /// <summary>
    /// Shift of an underlying asset trajectory
    /// </summary>
    /// <param name="shift_path">Asset trajectory after the shift</param>
    /// <param name="path">Asset trajectory</param>
    /// <param name="d">Index of the underlying asset to shift</param>
    /// <param name="h">Finite difference step</param>
    /// <param name="t">Date from which to shift</param>
    /// <param name="timestep">Underlying asset observation step</param>
    void shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, double t, double timestep);
};
