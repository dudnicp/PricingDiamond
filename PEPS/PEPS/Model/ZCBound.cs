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
		public DateTime _maturity;

		/// <summary>
		/// Constructeur par défaut du zéro coupon
		/// </summary>
		/// <param name="currency"> devise du ZC</param>
		/// <param name="name"> Nom du ZC </param>
		/// <param name="initialPrice"> Prix initial du ZC </param>
		/// <param name="purchaseDate">Prix d'achat du ZC </param>
		/// <param name="maturity"> Date de maturité du ZC </param>
		public ZCBound(Currency currency, String name, double initialPrice, DateTime purchaseDate, DateTime maturity)
		{
			_currency = new Currency(currency);
			_name = name;
			_initialPrice = initialPrice;
			_purchaseDate = purchaseDate;
			//TODO récupérer currentPrice dans la BDD ? ou la calculer.
		}

		/// <summary>
		/// Constructeur par recopie du ZC
		/// </summary>
		/// <param name="other"> ZC que l'on veut copier </param>
		public ZCBound(ZCBound other)
		{
			_currency = new Currency(other._currency);
			_name = other._name;
			_initialPrice = other._initialPrice;
			_purchaseDate = other._purchaseDate.Date;
			_maturity = other._maturity;
			_currency = other._currency;
		}

		/// <summary>
		/// Récupère le prix du ZC du marché étranger en €
		/// </summary>
		/// <returns> Renvoie la valeur du ZC en € </returns>
		public override double GetEuroPrice()
		{
			if (_currency._name != "€")
			{
				return UpdateCurrentPrice() * _currency.ChangeRate;
			}
			else
			{
				return UpdateCurrentPrice();
			}
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
