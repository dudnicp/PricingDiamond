using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class representing a share
    /// A Share is a particular type of financial Asset
    /// </summary>
    public class Share : Asset
    {
        /// <summary>
        /// Currency in which is traded the share
        /// </summary>
        public Currency Currency { get; protected set; }

        /// <summary>
        /// Price of the share in the local currency
        /// </summary>
        public double LocalPrice { get; protected set; }

        /// <summary>
        /// Constructor, creates a Share with the given name, currency and local price
        /// </summary>
        /// <param name="name">Name of the share</param>
        /// <param name="currency">Currency in which is traded the share</param>
        /// <param name="localPrice">Price of the share in the local currency</param>
        public Share(string name, Currency currency, double localPrice) : base(name)
        {
            Currency = currency;
            LocalPrice = localPrice;
        }

        public override void UpdatePrice(DateTime date)
        {
            throw new NotImplementedException();
        }
    }
}
