using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant un actif risqué dans son marché
	/// </summary>
	class Share : GlobalFinancialProduct
	{
		/// <summary>
		/// Constructeur par défaut de la classe Share
		/// </summary>
		/// <param name="name"> Nom de l'actif risqué </param>
		/// <param name="localPrice">Prix de l'actif dans sa monnaie locale </param>
		/// <param name="currency">Devise associée à l'actif </param>
		public Share(String name, double localPrice, Currency currency)
			: base(name, localPrice, currency)
		{
		}

		/// <summary>
		/// Renvoie le prix actuel en € du Share après actualisation
		/// </summary>
		/// <returns>Le prix actuel en € du Share </returns>
		public override double UpdatePrices()
		{
			throw new NotImplementedException();
			//TODO Chercher le prix actuel local dans la BDD
			// l'enregistrer dans _currentLocalPrice
			// renregister _currentEuroPrice = _currentLocalPrice * _currency.currentEuroPrice
			// return _currentEuroPrice
		}
	}
}
