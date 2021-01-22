#include "BlackScholesModel.hpp"
using namespace std;

BlackScholesModel::BlackScholesModel(int size, double r, double rho, const PnlVect* sigma,
	const PnlVect* spot, PnlVect* trend)
{
	size_ = size;
	r_ = r;
	rho_ = rho;
	sigma_ = pnl_vect_copy(sigma);
	spot_ = pnl_vect_copy(spot);
	trend_ = pnl_vect_copy(trend);
	G_ = pnl_vect_create(size);
	L_ = pnl_mat_create_from_scalar(size_, size_, rho_);
	pnl_mat_set_diag(L_, 1, 0);	  // L = Gamma
	pnl_mat_chol(L_);			  // L = Cholesky(Gamma)
	L_d_ = pnl_vect_create(size); // repr�sente une ligne de L_
	pastGetter_ = pnl_vect_create(size_);
	trendUsed_ = pnl_vect_create(size_);
}

BlackScholesModel::~BlackScholesModel()
{
	pnl_vect_free(&sigma_);
	pnl_vect_free(&spot_);
	pnl_vect_free(&G_);
	pnl_mat_free(&L_);
	pnl_vect_free(&L_d_);
	pnl_vect_free(&trend_);
	pnl_vect_free(&pastGetter_);
	pnl_vect_free(&trendUsed_);
}

BlackScholesModel::BlackScholesModel(const BlackScholesModel& other)
{
	size_ = other.size_;
	r_ = other.r_;
	rho_ = other.rho_;
	sigma_ = pnl_vect_copy(other.sigma_);
	spot_ = pnl_vect_copy(other.spot_);
	trend_ = pnl_vect_copy(other.trend_);
	L_ = pnl_mat_copy(other.L_);
	L_d_ = pnl_vect_copy(other.L_d_);
	G_ = pnl_vect_copy(other.G_);
	pastGetter_ = pnl_vect_copy(other.pastGetter_);
	trendUsed_ = pnl_vect_copy(other.trendUsed_);
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

void BlackScholesModel::asset(PnlMat* path, PnlRng* rng, PnlVect* observationDates)
{
	int timeIter = 0, size = observationDates->size;
	double deltaTime;
	pnl_vect_set_all(trendUsed_, r_);
	/* On remplit la 1�re ligne du path avec les spots*/
	pnl_mat_set_row(path, spot_, 0);

	/* Pour toute les autres lignes, on calcule grace � la valeur pr�c�dente*/
	for (timeIter = 0; timeIter < size; timeIter++)
	{
		deltaTime = pnl_vect_get(observationDates, timeIter + 1) - pnl_vect_get(observationDates, timeIter);
		pnl_mat_get_row(pastGetter_, path, timeIter);
		timeTrajectory(path, timeIter + 1, deltaTime, trendUsed_, pastGetter_, rng);
	}
}

void BlackScholesModel::asset(PnlMat* path, int dayIndex, PnlRng* rng, const PnlMat* past, PnlVect* observationDates)
{
	int i;
	double timeStep;
	for (i = 0; pnl_vect_get(observationDates, i) < dayIndex; i++)
	{
		pnl_mat_get_row(pastGetter_, past, i);
		pnl_mat_set_row(path, pastGetter_, i);
	}

	timeStep = (pnl_vect_get(observationDates, i) - dayIndex) / 365.0;

	pnl_mat_get_row(pastGetter_, past, i);
	if (timeStep != 0)
	{
		timeTrajectory(path, i, timeStep, trendUsed_, pastGetter_, rng);
	}
	else
	{
		pnl_mat_set_row(path, pastGetter_, i);
	}

	i++;
	for (i; i < observationDates->size; i++)
	{
		timeStep = (pnl_vect_get(observationDates, i) - pnl_vect_get(observationDates, i - 1)) / 365.0;
		pnl_mat_get_row(pastGetter_, path, i - 1);
		timeTrajectory(path, i, timeStep, trendUsed_, pastGetter_, rng);
	}
}

void BlackScholesModel::shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, int shiftIndex)
{
	for (int i = shiftIndex; i < path->m; i++)
	{
		pnl_mat_set(shift_path, i, d, pnl_mat_get(path, i, d) * (1 + h));
	}
}

void BlackScholesModel::simul_market(PnlMat* marketPath, PnlRng* rng)
{
	double deltaTime = 1 / 365.0;
	int timeIter = 0;
	int H = marketPath->m - 1;
	/* On remplit la 1�re ligne du path avec les spots*/
	pnl_mat_set_row(marketPath, spot_, 0);

	/* Pour toute les autres lignes, on calcule grace � la valeur pr�c�dente avec la proba historique*/
	for (timeIter = 0; timeIter < H; timeIter++)
	{
		pnl_mat_get_row(pastGetter_, marketPath, timeIter);
		timeTrajectory(marketPath, timeIter + 1, deltaTime, trend_, pastGetter_, rng);
	}
}
