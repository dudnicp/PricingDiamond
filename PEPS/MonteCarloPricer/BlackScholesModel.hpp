#pragma once

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <iostream>

/// <summary>
/// Black-Scholes model used for generating assets price trajectories
/// </summary>
class BlackScholesModel
{
public:
    int size_;       /// Number of assets in the model
    double r_;       /// Interest rate
    double rho_;     /// Correlation parameter
    PnlVect* sigma_; /// Vector of volatilities 
    PnlVect* spot_;  /// Inital underlying assets values
    PnlMat* L_;      /// Covariance matrix aafter Cholesky decompostion
    PnlVect* L_d_;   /// Line d of matrix L
    PnlVect* mu_;    /// Vector of rates for each underlying asset (trend)
    PnlVect* G_;     /// Gaussian Vector

    /// <summary>
    /// Constructeur par défaut 
    /// </summary>
    /// <param name="size"> Nombre de sous jacents</param>
    /// <param name="r"> taux sans risque</param>
    /// <param name="rho"> valeur de covariance des actifs</param>
    /// <param name="mu"> Vecteur tendance des actifs</param>
    /// <param name="sigma">Vecteur des volatilités des actifs</param>
    /// <param name="spot"> S_0 de chaque actif</param>
    BlackScholesModel(int size, double r, double rho, const PnlVect* mu, const PnlVect* sigma, const PnlVect * spot);

    /// <summary>
    /// Constructeur par recopie
    /// </summary>
    /// <param name="other"> Modèle de BlackSchols que l'on veut copier</param>
    BlackScholesModel(const BlackScholesModel &other);

    /// <summary>
    /// Destructeur de la classe
    /// </summary>
    ~BlackScholesModel();

    /// <summary>
    /// Computes the next iter value of all share from their actual value
    /// between date t and date t+deltaTime.
    /// </summary>
    /// <param name="path">Asset trajectory</param>
    /// <param name="timeIter">Index of the line of path to fill</param>
    /// <param name="deltaTime">Time between current and next values</param>
    /// <param name="lastSharesValues">List of current asset values</param>
    void timeTrajectory(PnlMat* path, int timeIter ,double deltaTime,const  PnlVect* lastSharesValues, PnlRng* rng);

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
    /// <param name="shiftIndex">Index from which to apply the shift</param>
    void shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, int shiftIndex);
};
