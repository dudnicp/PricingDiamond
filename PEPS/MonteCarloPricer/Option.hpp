#pragma once

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/// <summary>
/// Abstract class representing an option
/// </summary>
class Option
{
public:
    double T_; /// Option maturity
    int nbTimeSteps_; /// Number of discretization steps
    int size_; /// Size of the model (Redundant with <see>BlackScholesModel::size_</see>)
    PnlVect* assetWeights_; /// Weights of the underlying assets

    /// <summary>
    /// Computes the payoff of the option based on the given underlying asset trajectory
    /// </summary>
    /// <param name="path">Underlying asset trajectory</param>
    /// <returns>The option payoff</returns>
    virtual double payoff(const PnlMat* path) const = 0;

    /// <summary>
    /// Constructor, creates an Option
    /// </summary>
    /// <param name="T">Option maturity</param>
    /// <param name="nbTimeSteps">Number of discretization steps</param>
    /// <param name="size">size of the model</param>
    /// <param name="weights">Weights of the underlying assets</param>
    Option(double T, int nbTimeSteps, int size, const PnlVect* weights);

    /// <summary>
    /// Copy constructor, creates a copy of another option
    /// </summary>
    /// <param name="other">Option to copy</param>
    Option(const Option& other);

    /// <summary>
    /// Clones an option
    /// </summary>
    /// <returns>A pointer to a new replica option</returns>
    virtual Option* clone() const = 0;

    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~Option();
};


