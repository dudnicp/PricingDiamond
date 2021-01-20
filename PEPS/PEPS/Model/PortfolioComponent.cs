using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class represnting a hedging portfolio component
    /// </summary>
    class PortfolioComponent
    {
        /// <summary>
        /// Portfolio asset
        /// </summary>
        public Asset Asset { get; protected set; }

        /// <summary>
        /// Number of assets (of this type) in the portfolio
        /// </summary>
        public double Quantity { get; protected set; }

        /// <summary>
        /// Total price of this component in euros (= Asset.EuroPrice * Quantity)
        /// <see cref="Asset.EuroPrice"/>
        /// </summary>
        public double TotalPrice { get; protected set; }

        /// <summary>
        /// Constructor, creates a PortfolioComponent with the given Asset and quantity
        /// </summary>
        /// <param name="asset"></param>
        /// <param name="quantity"></param>
        public PortfolioComponent(Asset asset, double quantity)
        {
            Asset = asset;
            Quantity = quantity;
        }
    }
}
