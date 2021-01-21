using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class regroup all the hedging data used in the application
    /// </summary>
    public class HedgingData : INotifyPropertyChanged
    {
        private double _FCPDiamondPrice;
        private double _portfolioValue;
        private ObservableCollection<PortfolioComponent> _shares;
        private ObservableCollection<PortfolioComponent> _currencies;

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
        public ObservableCollection<PortfolioComponent> Shares
        {
            get => _shares;
            protected set
            {
                if (value != _shares)
                {
                    _shares = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("Shares"));
                }
            }
        }

        /// <summary>
        /// Hedging currencies
        /// </summary>
        public ObservableCollection<PortfolioComponent> Currencies
        {
            get => _currencies;
            protected set
            {
                if (value != _currencies)
                {
                    _currencies = value;
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("Currencies"));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Constructor (todo)
        /// </summary>
        public HedgingData()
        {
            // TODO
        }

        /// <summary>
        /// Update all prices to match the price at the given date
        /// </summary>
        /// <param name="date">Observation of observation</param>
        public void Update(DateTime date)
        {
            throw new NotImplementedException();
        }
    }
}
