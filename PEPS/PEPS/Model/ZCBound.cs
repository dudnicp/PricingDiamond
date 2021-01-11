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
	class ZCBound : FinancialProduct
	{
		private DateTime _maturity;
		public DateTime Maturity
		{
			get { return _maturity; }
		}

		/// <summary>
		/// Constructeur par défaut du zéro coupon
		/// </summary>
		/// <param name="currency"> devise du ZC</param>
		/// <param name="name"> Nom du ZC </param>
		/// <param name="initialPrice"> Prix initial du ZC </param>
		/// <param name="purchaseDate">Prix d'achat du ZC </param>
		/// <param name="maturity"> Date de maturité du ZC </param>
		public ZCBound(Currency currency, String name, double initialPrice, DateTime purchaseDate, DateTime maturity) : base(currency, name, initialPrice, purchaseDate)
		{
			_maturity = maturity;
		}

		/// <summary>
		/// Constructeur par recopie du ZC
		/// </summary>
		/// <param name="other"> ZC que l'on veut copier </param>
		public ZCBound(ZCBound other) : base(other)
		{
			_maturity = other.Maturity;
		}

		/// <summary>
		/// Actualise la valeur du ZC dans le marché auquel il appartient
		/// </summary>
		/// <returns> La valeur du ZC dans la monnaie de son marché d'origine</returns>
		public override double UpdateCurrentPrice()
		{
			// TODO : on calcule ou on va chercher la valeur dans la BDD ?
			return 1;
		}
	}
}
