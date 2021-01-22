using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Wrapper;

namespace PEPS.Services
{
    public class PortfolioManager 
    {
        private Pricer _pricer;
        public Pricer Pricer
        {
            get { return _pricer; }
            protected set { _pricer = value; }
        }

        private double _portfolioValue;
        public double PortfolioValue
        {
            get { return _portfolioValue; }
            protected set { _portfolioValue = value; }
        }

        private double _nonRiskyAsset;
        public double NonRiskyAsset
        {
            get { return _nonRiskyAsset; }
            protected set { _nonRiskyAsset = value; }
        }

        private double[] _deltas;
        public double[] Deltas
        {
            get { return _deltas; }
            protected set { _deltas = value; }
        }

        private double _price;
        public double Price
        {
            get { return _price; }
            protected set { _price = value; }
        }

        public PortfolioManager()
        {
            Pricer = new Pricer(AppData.ChangeRates, AppData.ObservationDates, AppData.R, AppData.Rho, 
                AppData.Sigmas, AppData.InitialSpots, AppData.Trends);
            Deltas = Pricer.deltas(0, AppData.MarketData);
            double risky = 0;
            int i;
            for (i = 0; i < AppData.NbShares; i++)
            {
                risky += Deltas[i] * AppData.InitialSpots[i];
            }
            NonRiskyAsset = Pricer.price(0, AppData.MarketData) - risky;
        }

        public void UpdatePortfolio(DateTime lastUpdateDate, DateTime newUpdateDate)
        {
            int LastUpdateDateIndex = AppData.DaysFromStart(lastUpdateDate);
            int NewUpdateDateIndex = AppData.DaysFromStart(newUpdateDate);

            Price = Pricer.price(NewUpdateDateIndex, AppData.MarketData);

            double riskyAsset;
            int i, t;
            for (t = LastUpdateDateIndex + 1; t <= NewUpdateDateIndex; t++)
            {
                PortfolioValue = 0;
                riskyAsset = 0;
                for (i = 0; i < AppData.NbShares; i++)
                {
                    PortfolioValue += Deltas[i] * AppData.MarketData[t, i];
                }
                PortfolioValue += NonRiskyAsset * Math.Exp(AppData.R / 365.0); // car deltaTime = 1/365.0
                Deltas = Pricer.deltas(t, AppData.MarketData);
                for (i = 0; i < AppData.NbShares; i++)
                {
                    riskyAsset += Deltas[i] * AppData.MarketData[t, i]; // nouveau delta calculés
                }
                NonRiskyAsset = PortfolioValue - riskyAsset;
            }
        }
    }
}
