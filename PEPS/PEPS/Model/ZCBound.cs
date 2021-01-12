using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant un Zéro Coupon dans une devise du marché
	/// </summary>
	class ZCBound : Option
	{
		private double _rate;
		/// <summary>
		/// Taux d'interet du Zéro coupon
		/// </summary>
		public double Rate
		{
			get { return _rate; }
		}

		/// <summary>
		/// Constructeur par défaut du Zéro coupon
		/// </summary>
		/// <param name="name"> Nom du ZC</param>
		/// <param name="localPrice"> prix dans la monnaie locale</param>
		/// <param name="currency"> Devise associée au ZC</param>
		/// <param name="maturity"> Date de maturité du ZC</param>
		/// <param name="rate"> Taux d'interêt du ZC</param>
		public ZCBound(String name, double localPrice, Currency currency, DateTime maturity, double rate)
			: base(name, localPrice, currency, maturity)
		{
			_rate = rate;
		}

		/// <summary>
		/// renvoie la valeur actuelle en € du ZC
		/// </summary>
		/// <returns>Valeur actualisée en € du ZC </returns>
		public override double UpdatePrices()
		{
			throw new NotImplementedException();
			//TODO Chercher le prix actuel local dans la BDD
			// l'enregistrer dans _currentLocalPrice
			// renregister _currentEuroPrice = _currentLocalPrice * _currency.currentEuroPrice
			// return _currentEuroPrice
		}

		public override double Payoff()
		{
			return 1;
		}
	}
}
