using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant le produit Diamond
	/// </summary>
	class Diamond : FinancialProduct
	{
		private Share[] _diamondShares;
		public Share[] DiamondShares
		{
			get { return _diamondShares; }
		}

		/// <summary>
		/// Constructeur par défaut
		/// </summary>
		/// <param name="currency"> Devise du produit</param>
		/// <param name="name"> Nom du produit </param>
		/// <param name="initialPrice"> Prix initial </param>
		/// <param name="purchaseDate">Date d'achat </param>
		public Diamond(Currency currency, String name, double initialPrice, DateTime purchaseDate) : base(currency, name, initialPrice, purchaseDate)
		{
			//TODO Remplir _diamondShares avec les 24 actifs
		}

		/// <summary>
		/// Constructeur par recopie
		/// </summary>
		/// <param name="other"> Produit Diamond que l'on veut copier </param>
		public Diamond(Diamond other) : base(other)
		{
		}

		/// <summary>
		/// Actualise le prix du produit Diamond
		/// </summary>
		/// <returns> Valeur du prix du Diamond </returns>
		public override double UpdateCurrentPrice()
		{
			// TODO Lien avec la BDD
			throw new NotImplementedException();
		}
	}
}
