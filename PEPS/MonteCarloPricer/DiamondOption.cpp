#include "DiamondOption.hpp"

DiamondOption::DiamondOption(PnlVect* observationDates, PnlVect* changeRate, int size, const PnlVect* weights)
	: Option(size, weights, observationDates)
{
	changeRate_ = pnl_vect_copy(changeRate);
}

DiamondOption* DiamondOption::clone() const 
{
	return new DiamondOption(*this);
}

DiamondOption::~DiamondOption()
{
	pnl_vect_free(&changeRate_);
}

void DiamondOption::constructDiamond(PnlMat* oberservedValues, const PnlMat* path) const
{
	int iterDate = 0, realDate = 0, i = 0, size = path->n;
	PnlVect* isFixedVector = pnl_vect_create_from_scalar(size, 0); // Représente si les actifs sont fixés(1) ou non (0)
	PnlVect* performance = pnl_vect_create(size);
	double value;
	int* iM = new int;
	double* M = new double;

	for (iterDate = 0; iterDate < oberservedValues->m; iterDate++)
	{
		realDate = (int)pnl_vect_get(observationDates_, iterDate);
		for (i = 0; i < size; i++) 
		{
			if (pnl_vect_get(isFixedVector, i) == 0) // on recopie le path
			{
				pnl_mat_set(oberservedValues, iterDate,i, pnl_mat_get(path, realDate, i));
			}
			else // La valeur est fixée -> On prends celle de l'iteration précédente
			{
				pnl_mat_set(oberservedValues, iterDate, i, pnl_mat_get(oberservedValues, iterDate - 1, i));
			}
		}
		if(realDate !=0)
		{
			// On calcule nos performances sur notre date de constation
			for (i = 0; i < size; i ++)
			{
				if (pnl_vect_get(isFixedVector, i) == 0)
				{
					value = (pnl_mat_get(path, realDate, i) - pnl_mat_get(path, 0, i)) / pnl_mat_get(path, 0, i);
				}
				else
				{
					value = -INT_MAX;
				}
				pnl_vect_set(performance, i, value);
			}
			pnl_vect_max_index(M, iM, performance);
			pnl_vect_set(isFixedVector, *iM, 1);

			pnl_mat_set(oberservedValues, iterDate, *iM, std::max(*M, 1.6 * pnl_mat_get(path, 0, *iM)));
		}
		// Il reste les 12 dernières valeurs à fixer à la dernière date de constattion
		for (i = 0; i < size; i++)
		{
			if (pnl_vect_get(isFixedVector, i) == 0) // pas encore fixée
			{
				pnl_mat_set(oberservedValues, size-1, i, std::max(pnl_mat_get(oberservedValues, size - 1, i), 0.6 * pnl_mat_get(oberservedValues, 0, i)));
			}
		}
	} 
}

double DiamondOption::payoff(const PnlMat* path) const 
{
	PnlMat* observedValues = pnl_mat_create(13, size_);
	constructDiamond(observedValues, path);
	PnlVect* constatationValues = pnl_vect_create(observedValues->m);
	double somme = 0;
	int i, j;
	for (i = 0; i < observedValues->m; i++)
	{
		somme = 0;
		for (j = 0; j < path->n; j++)
		{
			somme += pnl_mat_get(observedValues, i, j) * pnl_vect_get(changeRate_, i);
		}
		pnl_vect_set(constatationValues, i, somme);
	}
	return pnl_vect_max(constatationValues);
}

