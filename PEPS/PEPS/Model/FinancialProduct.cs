using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant un produit financier quelconque
	/// </summary>
	abstract class FinancialProduct
	{
		protected DateTime _purchaseDate;
		public DateTime PurchaseDate 
		{
			get { return _purchaseDate; }
		}

		protected double _currentPrice;
		public double CurrentPrice
		{
			get { return _currentPrice; }
			set { _currentPrice = value; }
		}

		protected double _initialPrice;
		public double InitialPrice
		{
			get { return _initialPrice; }
		}

		protected Currency _financialCurrency;
		public Currency FinancialCurrency
		{
			get { return _financialCurrency; }
		}

		protected String _name;
		public String Name
		{
			get { return _name; }
		}

		/// <summary>
		/// Constructeur de la classe abstraite pour l'initialisation
		/// </summary>
		/// <param name="currency"> Nom de la devise du produit </param>
		/// <param name="name"> Nom du produit financier </param>
		/// <param name="initialPrice"> Prix intial </param>
		/// <param name="purchaseDate"> Date d'achat du produit </param>
		public FinancialProduct(Currency currency, String name, double initialPrice, DateTime purchaseDate)
		{
			_financialCurrency = new Currency(currency);
			_name = name;
			_initialPrice = initialPrice;
			_purchaseDate = purchaseDate;
			_currentPrice = UpdateCurrentPrice();
		}

		/// <summary>
		/// Constructeur par recopie de la classe Produit financier
		/// </summary>
		/// <param name="other"> Produit financier que l'on veut copier</param>
		public FinancialProduct(FinancialProduct other)
		{
			_financialCurrency = new Currency(other._financialCurrency);
			_name = other.Name;
			_initialPrice = other.InitialPrice;
			_purchaseDate = other.PurchaseDate;
			_currentPrice = other.CurrentPrice;
		}
		/// <summary>
		/// Renvoie le prix du produit financier en €
		/// </summary>
		/// <returns> prix en € du produit financier </returns>
		public double GetEuroPrice()
		{
			if (_financialCurrency.Name != "€")
			{
				return UpdateCurrentPrice() * _financialCurrency.ChangeRate;
			}
			else
			{
				return UpdateCurrentPrice();
			}
		}

		/// <summary>
		/// Renvoie la valeur actuelle du prix du produit dans son marché
		/// </summary>
		/// <returns> prix du produit dans la devise de son marché</returns>
		public abstract double UpdateCurrentPrice();
	}
}
