using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace PEPS.Model
{
    /// <summary>
    /// Class represnting a hedging portfolio component
    /// </summary>
    public class HedgingAsset : INotifyPropertyChanged
    {
        private Asset _asset;
        private double _quantity;
        private double _totalPrice;

        /// <summary>
        /// Portfolio asset
        /// </summary>
        public Asset Asset
        {
            get => _asset;
            protected set
            {
                if (value != _asset)
                {
                    _asset = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Asset"));
                }
            }
        }

        /// <summary>
        /// Number of assets (of this type) in the portfolio
        /// </summary>
        public double Quantity
        {
            get => _quantity;
            protected set
            {
                if (value != _quantity)
                {
                    _quantity = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Quantity"));
                }
            }
        }

        /// <summary>
        /// Total price of this component in euros (= Asset.EuroPrice * Quantity)
        /// <see cref="Asset.EuroPrice"/>
        /// </summary>
        public double TotalPrice
        {
            get => _totalPrice;
            protected set
            {
                if (value != _totalPrice)
                {
                    _totalPrice = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("TotalPrice"));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Constructor, initialize all fields
        /// </summary>
        /// <param name="asset">Asset used for hedging</param>
        public HedgingAsset(Asset asset)
        {
            Asset = asset;
            Quantity = 0;
            TotalPrice = 0;
        }
    }
}
