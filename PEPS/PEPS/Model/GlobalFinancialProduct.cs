using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant un produit financier peut importe son marché
	/// </summary>
	class GlobalFinancialProduct : FinancialProduct
	{
		protected double _currentLocalPrice;
		/// <summary>
		/// Prix dans le marché local du produit financier
		/// </summary>
		public double CurrentLocalPrice
		{
			get { return _currentLocalPrice; }
		}

		protected Currency _localCurrency;
		/// <summary>
		/// Devise associée au produit financier. Cette devise 
		/// à un prix de 1 si le produit est dans le marché français
		/// </summary>
		public Currency LocalCurrency
		{
			get { return _localCurrency; }
		}

		/// <summary>
		/// Constructeur par défaut de la classe Produit financier global
		/// </summary>
		/// <param name="name"> nom du produit financier</param>
		/// <param name="localPrice"> prix du produit dans son marché</param>
		/// <param name="currency"> Devise associé au produit</param>
		public GlobalFinancialProduct(String name, double localPrice, Currency currency) : base(name)
		{
			_currentLocalPrice = localPrice;
			_localCurrency = currency;
			_currentEuroPrice = localPrice * currency.CurrentEuroPrice;
		}

		/// <summary>
		/// Renvoie la valeur actuelle en € du produit financier
		/// après avoir actualiser son prix dans son marché local
		/// </summary>
		/// <returns> La valeur actuelle en € du produit financier
		/// après actualisation </returns>
		public override double UpdatePrices()
		{
			throw new NotImplementedException();
			// TODO récupérer currentLocalPrice dans la BDD
			// et la mettre dans _currentLocalPrice
			// puis _currentEuroPrice = _currentLocalPrice * currency.CurrentEuroPrice
			// puis return _currentEuroPrice
		}
	}
}
