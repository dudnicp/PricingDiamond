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
		public DateTime _purchaseDate;
		public double _currentPrice;
		public double _initialPrice;
		public Currency _currency;
		public String _name;

		/// <summary>
		/// Renvoie le prix du produit financier en €
		/// </summary>
		/// <returns> prix en € du produit financier </returns>
		public abstract double GetEuroPrice();

		/// <summary>
		/// Renvoie la valeur actuelle du prix du produit dans son marché
		/// </summary>
		/// <returns> prix du produit dans la devise de son marché</returns>
		public abstract double UpdateCurrentPrice();
	}
}
