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

		private Pricer _pricer;
		public Pricer Pricer
		{
			get { return _pricerResult; }
		}

		public PortfolioManager()
		{
			// Pricer = new Pricer();
			Deltas = new double[2]; // taille à récup dans appdata
									//LastUpdateDate = dateOrigin à récup à récup dans appdata
			//NonRiskyAsset = Pricer.price(dateOrigin, marketData) - delta*Spot; 
		}

		public void UpdatePortfolio(DateTime date, double[] spots, double r)
		{
			int dayCount = (date - LastUpdateDate).Days;
			// en réalité les spots sont récupéré depuis le DataProvider mais pour l'insant spot = cste = argument entré
			// idem pour r
			double riskyAsset;
			int i, size = spots.Length, t;
			for (t = 0; t < dayCount; t++)
			{
				PortfolioValue = 0;
				riskyAsset = 0;
				for (i = 0; i < size; i++)
				{
					PortfolioValue += Deltas[i] * spots[i];
				}
				PortfolioValue += NonRiskyAsset * Math.Exp(r / 365.0); // car deltaTime = 1/365.0
				//Deltas = Pricer.deltas(date, maketData); ;
				for (i = 0; i < size; i++)
				{
					riskyAsset += Deltas[i] * spots[i]; // nouveau delta calculés
				}
				NonRiskyAsset = PortfolioValue - riskyAsset;
			}
			LastUpdateDate = date;
		}
	}
}
