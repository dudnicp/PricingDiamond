#pragma once
#define DLLEXP   __declspec( dllexport )
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

namespace Transition
{
	/// <summary>
	/// Fonction de transition entre C++ et C# o� price et deltas seront remplis gr�ce � MC
	/// Les vecteurs spot et sigma sont � r�cup�r� en amont gr�ce � un parseur sur le BDD
	/// </summary>
	/// <param name="price">Vecteur des prix � chaque date t</param>
	/// <param name="deltas">Matrice des delta pour chaque actif et chaque date t </param>
	/// <param name="nbSamples"> Nombre de simulation pour MC</param>
	/// <param name="T">date de maturit�</param>
	/// <param name="spot">Liste des spots des sous-jacents</param>
	/// <param name="sigma">Liste des volatilit�s des sous-jacents</param>
	DLLEXP void diamondEuro(PnlVect* price, PnlMat* deltas, int nbSamples, double T, double r, double rho,PnlVect* spot, PnlVect* sigma);
};

