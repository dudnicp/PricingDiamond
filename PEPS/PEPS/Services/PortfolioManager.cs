using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Wrapper;

namespace PEPS.Services
{
    class PortfolioManager
    {
        private DateTime _lastUpdateDate;
        public DateTime LastUpdateDate
        {
            get { return _lastUpdateDate; }
            protected set { _lastUpdateDate = value; }
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
            protected set { value.CopyTo(_deltas, 0); }
        }

        public PortfolioManager()
        {

            Deltas = Pricer.deltas(0, AppData.MarketData);
            LastUpdateDate = AppData.StartingDate;
            double risky = 0;
            int i;
            for (i = 0; i < AppData.NbShares; i++)
            {
                risky += Deltas[i] * AppData.InitialSpots[i];
            }
            NonRiskyAsset = Pricer.price(0, AppData.MarketData) - risky;
        }

        public void UpdatePortfolio(DateTime date)
        {
            int LastUpdateDateIndex = AppData.DaysFromStart(LastUpdateDate);
            int NewUpdateDateIndex = AppData.DaysFromStart(date);
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
            LastUpdateDate = date;
        }
    }
}
