using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Services
{
    public class AppData
    {
        private int _nbShares;
        private int _nbCurrencies;
        private double[] _initialSpots;
        private double[,] _marketData;
        private double[] _changeRates;
        private double[] _sigmas;
        private double[] _trends;
        private int[] _observationDates;
        private double _r;
        private double _rho;
        private DateTime _origin;

        public int NbShares { get => _nbShares; protected set => _nbShares = value; }
        public int NbCurrencies { get => _nbCurrencies; protected set => _nbCurrencies = value; }
        public double[] InitialSpots { get => _initialSpots; set => _initialSpots = value; }
        public double[,] MarketData { get => _marketData; protected set => _marketData = value; }
        public double[] ChangeRates { get => _changeRates; protected set => _changeRates = value; }
        public double[] Sigmas { get => _sigmas; protected set => _sigmas = value; }
        public double[] Trends { get => _trends; protected set => _trends = value; }
        public int[] ObservationDates { get => _observationDates; protected set => _observationDates = value; }
        public double R { get => _r; protected set => _r = value; }
        public double Rho { get => _rho; protected set => _rho = value; }
        public DateTime Origin { get => _origin; protected set => _origin = value; }
    }
}
