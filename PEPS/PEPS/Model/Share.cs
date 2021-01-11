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
	class Share : FinancialProduct
	{
		/// <summary>
		/// Constructeur de la classe Share
		/// </summary>
		/// <param name="currency"> Devise utilisée par l'actif</param>
		/// <param name="name"> Nom de l'actif </param>
		/// <param name="initialPrice"> Prix initial de l'actif</param>
		/// <param name="purchaseDate"> Date d'achat de l'actif </param>
		public Share(Currency currency, String name, double initialPrice, DateTime purchaseDate) : base(currency,  name, initialPrice, purchaseDate)
		{
		}

		/// <summary>
		/// Constructeur par recopie de la classe Share
		/// </summary>
		/// <param name="other"> Actif que l'on veut copier </param>
		public Share(Share other) : base(other)
		{
		}
	
		/// <summary>
		/// Renvoie le prix actuel de l'actif dans sa monnaie locale
		/// </summary>
		/// <returns> rix de l'actif dans la monnaie de sa devise </returns>
		public override double UpdateCurrentPrice()
		{
			//TODO : Chercher la valeur dans la BDD
			throw new NotImplementedException();
		}
	}
}
