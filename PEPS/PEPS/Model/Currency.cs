using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class represnting a currency
    /// A Currency is a particular type of financial Asset
    /// </summary>
    public class Currency : Asset
    {
        /// <summary>
        /// Constructor, creates a Currency with the given name and euro price (change rate)
        /// </summary>
        /// <param name="name">Name of the Currency</param>
        /// <param name="euroPrice">Currency/Euros change rate</param>
        public Currency(string name, double euroPrice) : base(name)
        {
            EuroPrice = euroPrice;
        }
    }
}
