#include <iostream>
#include <ctime>
#include <string>
#include "parser.hpp"

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "MonteCarlo.hpp"
#include "Option.hpp"
#include "BasketOption.hpp"
#include "AsianOption.hpp"
#include "PerformanceOption.hpp"
#include "BlackScholesModel.hpp"
#include "PricingResults.hpp"
#include "HedgingResults.hpp"

using namespace std;

void hedge()
{
    /// -- Paramètre BlackSholes model
    int size;       /// nombre d'actifs du modèle
    double r;       /// taux d'intérêt
    double rho;     /// paramètre de corrélation
    PnlVect* sigma; /// vecteur de volatilités
    PnlVect* spot;  /// vecteur des S(t0)
    PnlVect* mu;    /// tendance
    int H;          /// hedging date number

    /// -- Paramètre Option
    string type;     /// type de l'option
    double T;        /// maturité
    int nbTimeSteps; /// nombre de pas de temps de discrétisation
    double strike;
    PnlVect* weights; /// payoff coefficients

    /// -- Paramètre Monte Carlo
    size_t n_samples;
    double fd_step = 0.1;

    PnlVect* divid;

    char infile[] = "data_hedge/asian.dat";
    Param* P = new Parser(infile);

    P->extract("option size", size);

    P->extract("interest rate", r);
    P->extract("correlation", rho);
    P->extract("volatility", sigma, size);
    P->extract("spot", spot, size);
    P->extract("trend", mu, size, true);
    P->extract("hedging dates number", H);

    P->extract("option type", type);
    P->extract("maturity", T, true);
    P->extract("timestep number", nbTimeSteps);
    P->extract("strike", strike, true);
    P->extract("payoff coefficients", weights, size, true);

    P->extract("sample number", n_samples);

    if (P->extract("dividend rate", divid, size, true) == false)
    {
        divid = pnl_vect_create_from_zero(size);
    }

    // Construction BlackSholes
    BlackScholesModel* bsm = new BlackScholesModel(size, r, rho, sigma, spot, mu);

    Option* opt = nullptr;
    // Construction Option
    if (type == "basket")
    {
        opt = new BasketOption(T, nbTimeSteps, size, weights, strike);
    }
    else if (type == "asian")
    {
        opt = new AsianOption(T, nbTimeSteps, size, weights, strike);
    }
    else if (type == "performance")
    {
        opt = new PerformanceOption(T, nbTimeSteps, size, weights);
    }

    // Pricing avec MonteCarlo
    PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, (int)time(NULL));
    MonteCarlo mc(bsm, opt, rng, fd_step, (int)n_samples);

    double prix;
    double prix_std_dev;
    double erreur_couverture = 0;
    PnlMat* path = pnl_mat_create(H + 1, size);
    bsm->simul_market(path, H, T, rng);
    mc.price(prix, prix_std_dev);
    erreur_couverture = mc.profitAndLoss(path, T, nbTimeSteps);
    std::cout << erreur_couverture << std::endl;

    HedgingResults res(prix, prix_std_dev, erreur_couverture);
    cout << res << endl;

    pnl_mat_free(&path);
    pnl_vect_free(&spot);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    pnl_rng_free(&rng);
    delete opt;
    delete bsm;
    delete P;
}

void price0()
{
    /// -- Paramètre BlackSholes model
    int size;       /// nombre d'actifs du modèle
    double r;       /// taux d'intérêt
    double rho;     /// paramètre de corrélation
    PnlVect* sigma; /// vecteur de volatilités
    PnlVect* spot;  /// vecteur des S(t0)
    PnlVect* mu;    /// tendance

    /// -- Paramètre Option
    string type;     /// type de l'option
    double T;        /// maturité
    int nbTimeSteps; /// nombre de pas de temps de discrétisation
    double strike;
    PnlVect* weights; /// payoff coefficients

    /// -- Paramètre Monte Carlo
    size_t n_samples;
    double fd_step = 0.1;

    PnlVect* divid;

    char infile[] = "data/perf.dat";
    Param* P = new Parser(infile);
    P->extract("option size", size);

    P->extract("interest rate", r);
    P->extract("correlation", rho);
    P->extract("volatility", sigma, size);
    P->extract("spot", spot, size);
    P->extract("trend", mu, size, true);

    P->extract("option type", type);
    P->extract("maturity", T, true);
    P->extract("timestep number", nbTimeSteps);
    P->extract("strike", strike, true);
    P->extract("payoff coefficients", weights, size, true);

    P->extract("sample number", n_samples);

    if (P->extract("dividend rate", divid, size, true) == false)
    {
        divid = pnl_vect_create_from_zero(size);
    }
    PnlVect* trend = pnl_vect_create(size);
    // Construction BlackSholes
    BlackScholesModel* bsm = new BlackScholesModel(size, r, rho, sigma, spot, trend);

    Option* opt = nullptr;
    // Construction Option
    if (type == "basket")
    {
        opt = new BasketOption(T, nbTimeSteps, size, weights, strike);
    }
    else if (type == "asian")
    {
        opt = new AsianOption(T, nbTimeSteps, size, weights, strike);
    }
    else if (type == "performance")
    {
        opt = new PerformanceOption(T, nbTimeSteps, size, weights);
    }

    // Pricing avec MonteCarlo
    PnlRng* rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, (int)time(NULL));
    MonteCarlo mc(bsm, opt, rng, fd_step, (int)n_samples);

    double prix;
    double prix_std_dev;
    PnlVect* delta = pnl_vect_create_from_scalar(size, 0);
    PnlVect* delta_std_dev = pnl_vect_create_from_scalar(size, 0);
    mc.price(prix, prix_std_dev);
    mc.delta(delta, delta_std_dev);

    PricingResults res(prix, prix_std_dev, delta, delta_std_dev);
    cout << res << endl;

    pnl_vect_free(&spot);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    pnl_vect_free(&trend);
    pnl_rng_free(&rng);
    pnl_vect_free(&delta);
    pnl_vect_free(&delta_std_dev);
    delete opt;
    delete bsm;
    delete P;
}

int main(int argc, char** argv)
{
    hedge();
    return EXIT_SUCCESS;
}