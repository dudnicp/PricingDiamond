using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using PEPS.Services;

namespace PEPS.Model
{
    /// <summary>
    /// Class storing all the application data
    /// </summary>
    public class AppData : INotifyPropertyChanged
    {
        private HedgingData _hedgingData;
        private List<Share> _shares;
        private List<Currency> _currencies;

        /// <summary>
        /// Data used for hedging the FCP Diamond
        /// </summary>
        public HedgingData HedgingData
        {
            get => _hedgingData;
            protected set
            {
                if (value != _hedgingData)
                {
                    _hedgingData = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("HedgingData"));
                }
            }
        }

        /// <summary>
        /// List of all the shares used in the app
        /// </summary>
        public List<Share> Shares
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
        /// List of all the currencies used in the app
        /// </summary>
        public List<Currency> Currencies
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

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Default constructor, initialize all fields
        /// </summary>
        public AppData()
        {
            var initData = AppInit.GetDiamondCurrenciesBeta();
            Currencies = initData.Item1;
            Shares = initData.Item2;

            HedgingData = new HedgingData();
            foreach (Share share in Shares)
            {
                HedgingData.AddHedgingShare(new HedgingAsset(share));
            }
        }

        /// <summary>
        /// Sets all values to the ones observed at the given date
        /// </summary>
        /// <param name="date">Observation date</param>
        public void Update(DateTime date)
        {
            foreach (Currency cur in Currencies)
            {
                cur.UpdatePrice(date);
            }

            foreach (Share share in Shares)
            {
                share.UpdatePrice(date);
            }

            HedgingData.Update(date);
        }
    }
}
