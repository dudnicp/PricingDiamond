using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant un Swap
	/// </summary>
	abstract class Swap : Option
	{
		/// <summary>
		/// Constructeur par défaut de la classe Swap
		/// </summary>
		/// <param name="name"> Nom du Swap</param>
		/// <param name="localPrice"> prix dans la monnaie locale</param>
		/// <param name="currency"> Devise associée au Swap </param>
		/// <param name="maturity">Date de maturité du Swap</param>
		public Swap(String name, double localPrice, Currency currency, DateTime maturity)
			: base(name, localPrice, currency, maturity)
		{
		}

		/// <summary>
		/// Renvoie la valeur du prix du Swap dans sa monnaie locale
		/// </summary>
		/// <returns> Prix du Swap dans la monnaie de son marché </returns>
		public override double UpdatePrices()
		{
			throw new NotImplementedException();
			//TODO Chercher le prix actuel local dans la BDD
			// l'enregistrer dans _currentLocalPrice
			// renregister _currentEuroPrice = _currentLocalPrice * _currency.currentEuroPrice
			// return _currentEuroPrice
		}

		/// <summary>
		/// Renvoie le payoff du Swap à maturité
		/// </summary>
		/// <returns> Payoff du Swap</returns>
		public abstract override double Payoff();
	}
}
