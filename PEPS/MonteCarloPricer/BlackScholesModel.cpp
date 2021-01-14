#include "BlackScholesModel.hpp"
using namespace std;

BlackScholesModel::BlackScholesModel(int size, double r, double rho, const PnlVect* mu, const PnlVect* sigma, const PnlVect* spot)
{
	size_ = size;
	r_ = r;
	rho_ = rho;
	sigma_ = pnl_vect_copy(sigma);
	spot_ = pnl_vect_copy(spot);
	G_ = pnl_vect_create(size);
	L_ = pnl_mat_create_from_scalar(size_, size_, rho_); // L = Gamma
	pnl_mat_set_diag(L_, 1, 0);
	pnl_mat_chol(L_); // L = Cholesky(Gamma)
	L_d_ = pnl_vect_create(size);
	mu_ = pnl_vect_copy(mu);
}


BlackScholesModel::~BlackScholesModel()
{
	pnl_vect_free(&sigma_);
	pnl_vect_free(&spot_);
	pnl_vect_free(&G_);
	pnl_mat_free(&L_);
	pnl_vect_free(&L_d_);
	pnl_vect_free(&mu_);
}

BlackScholesModel::BlackScholesModel(const BlackScholesModel &other) {
	size_ = other.size_;
	r_ = other.r_;
	rho_ = other.rho_;
	sigma_ = pnl_vect_copy(other.sigma_);
	spot_ = pnl_vect_copy(other.spot_);
	mu_ = pnl_vect_copy(other.mu_);
	L_ = pnl_mat_copy(other.L_);
	L_d_ = pnl_vect_copy(other.L_d_);
	G_ = pnl_vect_copy(other.G_);
}


void BlackScholesModel::asset(PnlMat* path, double T, int nbTimeSteps, PnlRng* rng)
{
	double deltaTime = T / nbTimeSteps;
	int shareIndex = 0, timeIter = 0;
	double lastS_d_value, sigma_d, temporalPart, brownianPart;
	/* On remplit la 1ère ligne du path avec les spots*/
	pnl_mat_set_row(path, spot_, 0);

	/* Pour toute les autres lignes, on calcule grace à la valeur précédente*/
	for (timeIter = 0; timeIter < nbTimeSteps; timeIter++)
	{
		pnl_vect_rng_normal(G_, size_, rng); // On remplis le vecteur gaussien
		for (shareIndex = 0; shareIndex < size_; shareIndex++)
		{
			sigma_d = pnl_vect_get(sigma_, shareIndex);
			lastS_d_value = pnl_mat_get(path, timeIter, shareIndex);
			temporalPart = (pnl_vect_get(mu_, shareIndex) - 0.5 * pow(sigma_d, 2)) * deltaTime;
			brownianPart = sigma_d * SQR(deltaTime) * pnl_vect_scalar_prod(L_d_, G_);
			lastS_d_value *= exp(temporalPart + brownianPart);
			pnl_mat_set(path, timeIter + 1, shareIndex, lastS_d_value);
		}
	}
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
		int pastSize = past->m, timeIter = 0; 
		PnlVect* pastGetter = pnl_vect_create(size_);
		double wantedTime = pastSize * deltaTime - t; // écart entre date actuelle et prochaine date de marché
		/* Cas : wantedTime = 0 ou wantedTime > 0*/
		if (wantedTime == 0) // On remplit le path jusqu'à t
		{
			for (timeIter = 0; timeIter < pastSize; timeIter++)
			{
				pnl_mat_get_row(pastGetter, past, timeIter);
				pnl_mat_set_row(path, pastGetter, timeIter); // Pas plus simple bordel ?
			}
			pastSize++; // Lors de la poursuite de la simulation, on est 1 itération plus loin
		}
		else
		{

		}
	}
}