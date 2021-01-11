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
	class Swap : FinancialProduct
	{
		private DateTime _maturity;
		public DateTime Maturity
		{
			get { return _maturity; }
		}

		/// <summary>
		/// Constructeur par défaut de la classe Swap
		/// </summary>
		/// <param name="currency"> nom de la devise du Swap </param>
		/// <param name="name"> Nom du Swap </param>
		/// <param name="initialPrice"> Prix initial </param>
		/// <param name="purchaseDate"> Date d'achat du Swap </param>
		/// <param name="maturity"> Date de maturité du Swap </param>
		public Swap(Currency currency, String name, double initialPrice, DateTime purchaseDate, DateTime maturity) : base(currency, name, initialPrice, purchaseDate)
		{
			_maturity = maturity;
		}

		/// <summary>
		/// Constructeur par recopie de la classe Swap
		/// </summary>
		/// <param name="other"> Swap que l'on veut copier </param>
		public Swap(Swap other): base(other)
		{
			_maturity = other.Maturity;
		}

		/// <summary>
		/// Renvoie la valeur du prix du Swap dans sa monnaie locale
		/// </summary>
		/// <returns> Prix du Swap dans la monnaie de son marché </returns>
		public override double UpdateCurrentPrice()
		{
			//TODO Lien avec la BDD pour actualisation
			throw new NotImplementedException();
		}
	}
}
