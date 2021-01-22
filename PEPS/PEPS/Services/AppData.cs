using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PEPS.Model;
using Wrapper;

namespace PEPS.Services
{
    public static class AppData
    {
        private static int _nbShares;
        private static int _nbCurrencies;
        private static double[] _initialSpots;
        private static double[,] _marketData;
        private static double[] _changeRates;
        private static double[] _sigmas;
        private static double[] _trends;
        private static int[] _observationDates;
        private static double _r;
        private static double _rho;
        private static DateTime _startingDate;
        private static List<Share> _shares;
        private static List<Currency> _currencies;

        /// <summary>
        /// Number of shares used in the app
        /// </summary>
        public static int NbShares { get => _nbShares; private set => _nbShares = value; }

        /// <summary>
        /// Number of currencies used in the app
        /// </summary>
        public static int NbCurrencies { get => _nbCurrencies; private set => _nbCurrencies = value; }

        /// <summary>
        /// Share spots observed at origin
        /// </summary>
        public static double[] InitialSpots { get => _initialSpots; private set => _initialSpots = value; }

        /// <summary>
        /// Simulated Assets trajectories
        /// </summary>
        public static double[,] MarketData { get => _marketData; private set => _marketData = value; }

        /// <summary>
        /// Currencies change rates
        /// </summary>
        public static double[] ChangeRates { get => _changeRates; private set => _changeRates = value; }

        /// <summary>
        /// Shares sigmas
        /// </summary>
        public static double[] Sigmas { get => _sigmas; private set => _sigmas = value; }

        /// <summary>
        /// Shares trends
        /// </summary>
        public static double[] Trends { get => _trends; private set => _trends = value; }

        /// <summary>
        /// List of all the observation dates
        /// </summary>
        public static int[] ObservationDates { get => _observationDates; private set => _observationDates = value; }

        /// <summary>
        /// Risk Free Rate
        /// </summary>
        public static double R { get => _r; private set => _r = value; }

        /// <summary>
        /// Correlation factor
        /// </summary>
        public static double Rho { get => _rho; private set => _rho = value; }

        /// <summary>
        /// First Observation Date
        /// </summary>
        public static DateTime StartingDate { get => _startingDate; private set => _startingDate = value; }

        /// <summary>
        /// List of all the shares used in the app
        /// </summary>
        public static List<Share> Shares { get => _shares; private set => _shares = value; }

        /// <summary>
        /// List of all the currencies used in the app
        /// </summary>
        public static List<Currency> Currencies { get => _currencies; private set => _currencies = value; }

        public static void Init()
        {
            NbCurrencies = 2;
            NbShares = 4;

            Currencies = new List<Currency>();
            Shares = new List<Share>();

            var euro = new Currency("Euro €", 1);
            var dollar = new Currency("Dollar $", 0.8);

            Currencies.Add(euro);
            Currencies.Add(dollar);

            Shares.Add(new Share("ActionEuro1", euro, 100));
            Shares.Add(new Share("ActionEuro2", euro, 50));
            Shares.Add(new Share("DollarShare1", dollar, 100));
            Shares.Add(new Share("DollarShare2", dollar, 50));

            InitialSpots = new double[NbShares];
            for (int i = 0; i < NbShares; i++)
            {
                InitialSpots[i] = Shares[i].EuroPrice;
            }

            ChangeRates = new double[NbCurrencies];
            for (int i = 0; i < NbCurrencies; i++)
            {
                ChangeRates[i] = Currencies[i].EuroPrice;
            }

            Sigmas = new double[NbShares];
            for (int i = 0; i < NbShares; i++)
            {
                Sigmas[i] = 0.2;
            }

            Trends = new double[NbShares];
            for (int i = 0; i < NbShares; i++)
            {
                Trends[i] = 0.04;
            }

            R = 0.01;

            Rho = 0;

            StartingDate = new DateTime(2005, 1, 1);

            ObservationDates = new int[13];
            ObservationDates[0] = 0;
            ObservationDates[1] = 31;
            ObservationDates[2] = 59;
            ObservationDates[3] = 90;
            ObservationDates[4] = 120;
            ObservationDates[5] = 151;
            ObservationDates[6] = 181;
            ObservationDates[7] = 212;
            ObservationDates[8] = 243;
            ObservationDates[9] = 273;
            ObservationDates[10] = 304;
            ObservationDates[11] = 334;
            ObservationDates[12] = 365;

            MarketData = MarketSimulator.SimulateMarket(366, R, Rho, Sigmas, InitialSpots, Trends);
        }

        public static int DaysFromStart(DateTime date)
        {
            return (date - StartingDate).Days;
        }

        public static void Update(DateTime date)
        {
            int dateIndex = DaysFromStart(date);
            for (int i = 0; i < NbShares; i++)
            {
                Shares[i].EuroPrice = MarketData[dateIndex, i];
            }
        }
    }
}
