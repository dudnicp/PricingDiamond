#include "BlackScholesModel.hpp"
using namespace std;

BlackScholesModel::BlackScholesModel(int size, double r, double rho, const PnlVect* sigma, const PnlVect* spot, PnlVect* trend)
{
	size_ = size;
	r_ = r;
	rho_ = rho;
	sigma_ = pnl_vect_copy(sigma);
	spot_ = pnl_vect_copy(spot);
	trend_ = pnl_vect_copy(trend);
	G_ = pnl_vect_create(size);
	L_ = pnl_mat_create_from_scalar(size_, size_, sqrt(rho_/size_)); 
	pnl_mat_set_diag(L_, 1, 0); // L = Gamma
	//pnl_mat_chol(L_); // L = Cholesky(Gamma)
	L_d_ = pnl_vect_create(size); // repr�sente une ligne de L_
}


BlackScholesModel::~BlackScholesModel()
{
	pnl_vect_free(&sigma_);
	pnl_vect_free(&spot_);
	pnl_vect_free(&G_);
	pnl_mat_free(&L_);
	pnl_vect_free(&L_d_);
	pnl_vect_free(&trend_);
}

BlackScholesModel::BlackScholesModel(const BlackScholesModel &other) {
	size_ = other.size_;
	r_ = other.r_;
	rho_ = other.rho_;
	sigma_ = pnl_vect_copy(other.sigma_);
	spot_ = pnl_vect_copy(other.spot_);
	trend_ = pnl_vect_copy(other.trend_);
	L_ = pnl_mat_copy(other.L_);
	L_d_ = pnl_vect_copy(other.L_d_);
	G_ = pnl_vect_copy(other.G_);
}


void BlackScholesModel::timeTrajectory(PnlMat* path, int timeIter, double deltaTime, PnlVect* trendUsed, const PnlVect* lastSharesValue, PnlRng* rng)
{
	int d = 0;
	double lastS_d_value, sigma_d, temporalPart, brownianPart;

	pnl_vect_rng_normal(G_, size_, rng);
	for (d = 0; d < size_; d++)
	{
		sigma_d = pnl_vect_get(sigma_, d);
		pnl_mat_get_row(L_d_, L_, d);
		lastS_d_value = pnl_vect_get(lastSharesValue, d);
		temporalPart = (pnl_vect_get(trendUsed, d) - pow(sigma_d, 2) / 2) * deltaTime;
		brownianPart = sigma_d * std::sqrt(deltaTime) * pnl_vect_scalar_prod(L_d_, G_);
		lastS_d_value *= exp(temporalPart + brownianPart);
		pnl_mat_set(path, timeIter, d, lastS_d_value);
	}
}

void BlackScholesModel::asset(PnlMat* path, double T, int nbTimeSteps, PnlRng* rng)
{
	double deltaTime = T / nbTimeSteps;
	PnlVect* pastGetter = pnl_vect_create(size_);
	int timeIter = 0;
	PnlVect* trendUsed = pnl_vect_create_from_double(size_, r_);
	/* On remplit la 1�re ligne du path avec les spots*/
	pnl_mat_set_row(path, spot_, 0);

	/* Pour toute les autres lignes, on calcule grace � la valeur pr�c�dente*/
	for (timeIter = 0; timeIter < nbTimeSteps; timeIter++)
	{
		pnl_mat_get_row(pastGetter, path, timeIter);
		timeTrajectory(path, timeIter + 1, deltaTime, trendUsed, pastGetter, rng);
	}

	pnl_vect_free(&pastGetter);
	pnl_vect_free(&trendUsed);
}

void BlackScholesModel::asset(PnlMat* path, double t, double T, int nbTimeSteps, PnlRng* rng, const PnlMat* past)
{
	if (t == 0) 
	{
		asset(path, T, nbTimeSteps, rng);
	}
	else
	{
		double deltaTime = T / nbTimeSteps;
		int pastSize = (int)floor(t/deltaTime)+1, timeIter = 0; 
		PnlVect* pastGetter = pnl_vect_create(size_);
		PnlVect* trendUsed = pnl_vect_create_from_double(size_, r_);
		double wantedTime = pastSize * deltaTime - t; // �cart entre date actuelle et prochaine date de march�

		// On remplis le path jusqu'a t_i (< t <= t_i+1 )
		for (timeIter = 0; timeIter < pastSize - 1; timeIter++) 
		{
			pnl_mat_get_row(pastGetter, past, timeIter);
			pnl_mat_set_row(path, pastGetter, timeIter);
		}
		pnl_mat_get_row(pastGetter, past, pastSize - 1);

		/* Cas : wantedTime = 0 ou wantedTime > 0*/
		if (wantedTime == 0) // On remplit le path jusqu'� t sans simuler
		{
			pnl_mat_set_row(path, pastGetter, pastSize - 1);
		}
		else // On simule entre la date actuelle et la prochaine date de march�
		{
			timeTrajectory(path, pastSize - 1, wantedTime, trendUsed, pastGetter, rng);
		}
		
		// Enfin on continue normalement
		for (timeIter = pastSize; timeIter < nbTimeSteps; timeIter ++)
		{
			pnl_mat_get_row(pastGetter, path, timeIter - 1);
			timeTrajectory(path, timeIter, deltaTime, trendUsed, pastGetter, rng);
		}
		pnl_vect_free(&pastGetter);
		pnl_vect_free(&trendUsed);
	}
}

void BlackScholesModel::shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, int shiftIndex)
{
	for (int i = shiftIndex; i < path->m; i++)
	{
		pnl_mat_set(shift_path, i, d, pnl_mat_get(path, i, d) * (1 + h));
	}
}

void BlackScholesModel::simul_market(PnlMat* marketPath, double H, double T, PnlRng* rng)
{
	double deltaTime = T / H;
	PnlVect* pastGetter = pnl_vect_create(size_);
	int timeIter = 0;
	/* On remplit la 1�re ligne du path avec les spots*/
	pnl_mat_set_row(marketPath, spot_, 0);

	/* Pour toute les autres lignes, on calcule grace � la valeur pr�c�dente avec la proba historique*/
	for (timeIter = 0; timeIter < H; timeIter++)
	{
		pnl_mat_get_row(pastGetter, marketPath, timeIter);
		timeTrajectory(marketPath, timeIter + 1, deltaTime, trend_, pastGetter, rng);
	}

	pnl_vect_free(&pastGetter);
}
