#include "pch.h"

#include "Pricer.hpp"

namespace Pricer {
	PricerClass::PricerClass(PnlMat* simulatedMarketData, PnlVect* observationDates, PnlVect* currentSpots, PnlVect* changeRates) {
		this->simulatedMarketData_ = simulatedMarketData;
		this->observationDates_ = observationDates;
		this->currentSpots_ = currentSpots;
		this->changeRates_ = changeRates;


		/// -- Paramètre BlackSholes model
		int size;       /// nombre d'actifs du modèle
		double r;       /// taux d'intérêt
		double rho;     /// paramètre de corrélation
		PnlVect* sigma; /// vecteur de volatilités
		PnlVect* spot;  /// vecteur des S(t0)
		PnlVect* mu;    /// tendance
		int H;          /// hedging date number

		/// -- Paramètre Option
		double T;        /// maturité
		int nbTimeSteps; /// nombre de pas de temps de discrétisation
		double strike;
		PnlVect* weights; /// payoff coefficients

		/// -- Paramètre Monte Carlo
		size_t n_samples;
		double fd_step = 0.1;

		PnlVect* divid;

		// Construction BlackSholes
		BlackScholesModel* bsm = new BlackScholesModel(size, r, rho, sigma, spot, mu);

		Option* opt = nullptr;

		// Pricing avec MonteCarlo
		PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
		pnl_rng_sseed(rng, (int)time(NULL));
		MonteCarlo mc(bsm, opt, rng, fd_step, (int)n_samples);

		this->delta = pnl_vect_create_from_scalar(size, 0);
		this->std_dev_vect = pnl_vect_create_from_scalar(size, 0);

	}

	void PricerClass::getPrice(int date) {
		int nbTimeSteps = observationDates_->size;
		int size = currentSpots_->size;

		PnlMat* past = pnl_mat_create(nbTimeSteps + 1, size);

		for (size_t i = 0; i < date; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				pnl_mat_set(past, i, j, pnl_mat_get(this->simulatedMarketData_, i, j));
			}
		}

		this->monteCarlo->price(past, date, this->price, this->std_dev);
	}

	void PricerClass::getDelta(int date) {
		// TODO problème avec date

		int nbTimeSteps = observationDates_->size;
		int size = currentSpots_->size;

		PnlMat* past = pnl_mat_create(nbTimeSteps + 1, size);

		for (size_t i = 0; i < date; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				pnl_mat_set(past, i, j, pnl_mat_get(this->simulatedMarketData_, i, j));
			}
		}

		this->monteCarlo->delta(past, date, this->delta, this->std_dev_vect);

	}
}

