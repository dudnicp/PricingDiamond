﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PEPS.Services;
using Wrapper;

namespace PEPS.Model
{
    /// <summary>
    /// Class regroup all the hedging data used in the application
    /// </summary>
    public class HedgingData : INotifyPropertyChanged
    {
        private double _FCPDiamondPrice;
        private double _portfolioValue;
        private ObservableCollection<HedgingAsset> _shares;
        private ObservableCollection<HedgingAsset> _currencies;
        private PortfolioManager _manager;

        /// <summary>
        /// Current price of the FCPDiamond
        /// </summary>
        public double FCPDiamondPrice
        {
            get => _FCPDiamondPrice;
            protected set
            {
                if (value != _FCPDiamondPrice)
                {
                    _FCPDiamondPrice = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("FCPDiamondPrice"));
                }
            }
        }

        /// <summary>
        /// Hedging protfolio total value
        /// </summary>
        public double PortfolioValue
        {
            get => _portfolioValue;
            protected set
            {
                if (value != _portfolioValue)
                {
                    _portfolioValue = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("PortfolioValue"));
                }
            }
        }

        /// <summary>
        /// Hedging shares
        /// </summary>
        public ObservableCollection<HedgingAsset> Shares
        {
            get => _shares;
            protected set
            {
                if (value != _shares)
                {
                    _shares = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Shares"));
                }
            }
        }

        /// <summary>
        /// Hedging currencies
        /// </summary>
        public ObservableCollection<HedgingAsset> Currencies
        {
            get => _currencies;
            protected set
            {
                if (value != _currencies)
                {
                    _currencies = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Currencies"));
                }
            }
        }

        public PortfolioManager Manager { get => _manager; protected set => _manager = value; }

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Default constructor, initialize all fields
        /// </summary>
        public HedgingData()
        {
            FCPDiamondPrice = 0;
            PortfolioValue = 0;
            Shares = new ObservableCollection<HedgingAsset>();
            Currencies = new ObservableCollection<HedgingAsset>();
            Manager = new PortfolioManager();

            foreach (Share share in AppData.Shares)
            {
                Shares.Add(new HedgingAsset(share));
            }

            foreach (Currency curr in AppData.Currencies)
            {
                Currencies.Add(new HedgingAsset(curr));
            }
        }

        /// <summary>
        /// Update all prices to match the price at the given date
        /// </summary>
        /// <param name="date">Observation of observation</param>
        public void Update(DateTime date)
        {
            AppData.Update(date);
            Manager.UpdatePortfolio(date);
            FCPDiamondPrice = Manager.Price;
            PortfolioValue = Manager.PortfolioValue;
            for (int i = 0; i < Shares.Count; i++)
            {
                Shares[i].Quantity = Manager.Deltas[i];
                Shares[i].TotalPrice = Shares[i].Asset.EuroPrice * Shares[i].Quantity;
            }
            Currencies[0].Quantity = Manager.NonRiskyAsset;
            Currencies[0].TotalPrice = Manager.NonRiskyAsset;
        }
    }
}
