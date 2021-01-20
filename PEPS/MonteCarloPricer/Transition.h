#pragma once
#define DLLEXP   __declspec( dllexport )
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

namespace Transition
{
	/// <summary>
	/// Fonction de transition entre C++ et C# où price et deltas seront remplis grâce à MC
	/// Les vecteurs spot et sigma sont à récupéré en amont grâce à un parseur sur le BDD
	/// </summary>
	/// <param name="price">Vecteur des prix à chaque date t</param>
	/// <param name="deltas">Matrice des delta pour chaque actif et chaque date t </param>
	/// <param name="nbSamples"> Nombre de simulation pour MC</param>
	/// <param name="T">date de maturité</param>
	/// <param name="spot">Liste des spots des sous-jacents</param>
	/// <param name="sigma">Liste des volatilités des sous-jacents</param>
	DLLEXP void diamondEuro(PnlVect* price, PnlMat* deltas, int nbSamples, double T, double r, double rho,PnlVect* spot, PnlVect* sigma);
};

