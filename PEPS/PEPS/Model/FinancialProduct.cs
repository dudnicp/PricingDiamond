using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant un produit financier du marché français
	/// </summary>
	abstract class FinancialProduct
	{
		protected double _currentEuroPrice;
		/// <summary>
		/// Valeur en € du produit financier
		/// </summary>
		public double CurrentEuroPrice
		{
			get { return _currentEuroPrice; }
		}

		protected String _name;
		/// <summary>
		/// Nom du produit financier
		/// </summary>
		public String Name
		{
			get { return _name; }
		}

		/// <summary>
		/// Constructeur par défaut du produit financier.
		/// Le prix en euro est fixé à 1 au départ et sera modifié par la
		/// fonction updateCurrentPrices()
		/// </summary>
		/// <param name="name"></param>
		public FinancialProduct(String name)
		{
			_name = name;
			_currentEuroPrice = 1;
		}

		/// <summary>
		/// Renvoie la valeur actuelle du prix du produit dans son marché
		/// </summary>
		/// <returns> prix du produit dans la devise de son marché</returns>
		public abstract double UpdatePrices();
	}
}
