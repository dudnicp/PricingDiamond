using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class representing a share
    /// A Share is a particular type of financial Asset
    /// </summary>
    public class Share : Asset
    {
        private Currency _currency;
        private double _localPrice;

        /// <summary>
        /// Currency in which is traded the share
        /// </summary>
        public Currency Currency
        {
            get => _currency;
            protected set
            {
                if (value != _currency)
                {
                    _currency = value;
                    PropertyChanged1?.Invoke(this, new PropertyChangedEventArgs("Currency"));
                }
            }
        }

        /// <summary>
        /// Price of the share in the local currency
        /// </summary>
        public double LocalPrice
        {
            get => _localPrice;
            protected set
            {
                if (value != _localPrice)
                {
                    _localPrice = value;
                    PropertyChanged1?.Invoke(this, new PropertyChangedEventArgs("LocalPrice"));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged1;

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
            EuroPrice = localPrice * Currency.EuroPrice;
        }

        public override void UpdatePrice(DateTime date)
        {
            throw new NotImplementedException();
        }
    }
}
