using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant une devise d'un marché étranger d'un point de
	/// vue du marché Français
	/// </summary>
	class Currency : FinancialProduct
	{
		/// <summary>
		/// Constructeur par défaut de la classe Currency (cas devise française)
		/// </summary>
		/// <param name="name"> Nom de la devise</param>
		public Currency(String name) : base(name)
		{
		}

		/// <summary>
		/// Constructeur devise étrangère 
		/// </summary>
		/// <param name="name"> Nom de la devise</param>
		/// <param name="euroPrice"> Taux de change en € </param>
		public Currency(String name, double euroPrice) : base(name)
		{
			_currentEuroPrice = euroPrice;
		}

		/// <summary>
		/// Renvoie la valeur actuelle du taux de change en € de la devise
		/// </summary>
		/// <returns> Valeur actuelle en € du taux de change</returns>
		public override double UpdatePrices()
		{
			throw new NotImplementedException();
			//TODO : récupérer (si la devise n'est pas française)
			// sa valeur dans la BDD et l'enregister dans _currentEuroPrice
			// puis return _currentEuroPrice

		}
	}
}
