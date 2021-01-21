using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class regroup all the hedging data used in the application
    /// </summary>
    class HedgingData
    {
        /// <summary>
        /// Current price of the FCPDiamond
        /// </summary>
        public double FCPDiamondPrice { get; protected set; }

        /// <summary>
        /// Hedging protfolio total value
        /// </summary>
        public double PortfolioValue { get; protected set; }

        /// <summary>
        /// Hedging shares
        /// </summary>
        public List<PortfolioComponent>  Shares { get; protected set; }

        /// <summary>
        /// Hedging currencies
        /// </summary>
        public List<PortfolioComponent> Currencies { get; protected set; }

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
