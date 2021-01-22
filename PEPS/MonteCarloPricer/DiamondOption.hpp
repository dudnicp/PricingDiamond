#pragma once
#define DLLEXP   __declspec( dllexport )
#include "Option.hpp"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <stdint.h>

/// <summary>
/// Class representing Diamond FCP
/// </summary>
class DiamondOption : public Option
{
public:

	PnlVect* aux_;
	PnlVect* getter_;
	PnlVect* spot_;
	PnlMat* constructedPath_;

	/// <summary>
	/// Creates a Diamond FCP
	/// </summary>
	/// <param name="T">Option maturity</param>
	/// <param name="nbTimeSteps">Number of discretization steps</param>
	/// <param name="size">size of the model</param>
	DLLEXP DiamondOption(PnlVect* observationDates, PnlVect* changeRate,int size = 24, const PnlVect* weights = pnl_vect_create_from_double(24, 1 / 24));

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <returns> the DiamondOption object copy from an other one </returns>
	DLLEXP virtual DiamondOption* clone() const;

	///
	///<summary>
	/// Destructor
	/// </summary>
	DLLEXP ~DiamondOption();

	/// <summary>
	/// Payoff function of the FCP Diamond
	/// </summary>
	/// <param name="path"> Trajectories of diamond</param>
	/// <returns> Value of the payoff according to the trajectory </returns>
	DLLEXP double payoff(const PnlMat* path) const;

	/// <summary>
	/// From a trajectory, get the fixed assets and the observations value
	/// for the value of the payoff
	/// </summary>
	/// <param name="observedValues"> PnlMat containing fixed trajectory</param>
	/// <param name="path"> PnlMat containing assets trajectory</param>
	DLLEXP void constructDiamond(PnlMat* constructedPath, const PnlMat* path) const;

	DLLEXP void searchMax(double& maxValue, int& maxIndex) const;
};

