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
	class Diamond : Option
	{
		private Position[] _sharesPositions;
		/// <summary>
		/// Liste des 24 actifs du produit structuré diamond
		/// </summary>
		public Position[] SharesPositions
		{
			get { return _sharesPositions; }
		}

		
		/// <summary>
		/// Constructeur de la Classe Diamond
		/// Il serait interressant d'initialiser directement currency = currency Francaise 
		/// et maturity = date de fin du diamond
		/// </summary>
		/// <param name="name">Diamond</param>
		/// <param name="localPrice"> Prix du Diamond (à calculer)</param>
		/// <param name="currency">Devise -> Francaise</param>
		/// <param name="maturity">Date de maturité -> à remplacer</param>
		public Diamond(String name, double localPrice, Currency currency, DateTime maturity)
			: base(name, localPrice, currency, maturity)
		{
			_sharesPositions = new Position[24];
			int i;
			for (i = 0; i < 24; i++) 
			{
				//TODO Remplir _diamondShares avec les 24 actifs
			}

		}

		/// <summary>
		/// Actualise le prix du produit Diamond
		/// </summary>
		/// <returns> Valeur du prix du Diamond </returns>
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
			//TODO Il va falloir lier la trajectoires des actifs avec la valeur du 
			// portefeuille diamond
			throw new NotImplementedException();
		}
	}
}
