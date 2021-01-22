using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        private static DateTime _origin;

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
        /// 
        /// </summary>
        public static double[,] MarketData { get => _marketData; private set => _marketData = value; }
        public static double[] ChangeRates { get => _changeRates; private set => _changeRates = value; }
        public static double[] Sigmas { get => _sigmas; private set => _sigmas = value; }
        public static double[] Trends { get => _trends; private set => _trends = value; }
        public static int[] ObservationDates { get => _observationDates; private set => _observationDates = value; }
        public static double R { get => _r; private set => _r = value; }
        public static double Rho { get => _rho; private set => _rho = value; }
        public static DateTime Origin { get => _origin; private set => _origin = value; }
    }
}
