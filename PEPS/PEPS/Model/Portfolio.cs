using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace PEPS.Model
{
	/// <summary>
	/// Représente un portefeuille d'actif financier provenant
	/// de différents marché
	/// </summary>
	class Portfolio
	{
		private List<FinancialProduct> _products;
		public List<FinancialProduct> Products
		{
			get { return _products; }
			set { _products = new List<FinancialProduct>(value); }
		}

		/// <summary>
		/// Constructeur par défaut d'un portefeuille vide de produits
		/// financiers
		/// </summary>
		public Portfolio()
		{
			_products = new List<FinancialProduct>();
		}

		/// <summary>
		/// Constructeur d'un portefeuille avec la liste des produits
		/// financiers
		/// </summary>
		/// <param name="listProducts"> Liste des produits financiers </param>
		public Portfolio(List<FinancialProduct> listProducts)
		{
			_products = new List<FinancialProduct>(listProducts);
		}

		/// <summary>
		/// Constructeur par copie du portefeuille
		/// </summary>
		/// <param name="other"> Portefeuille que l'on veut copier </param>
		public Portfolio(Portfolio other)
		{
			_products = new List<FinancialProduct>(other.Products);
		}

		/// <summary>
		/// Calcule la valeur actuelle du portefeuille en €
		/// </summary>
		/// <returns> Somme des valeurs des produits financiers en € </returns>
		public double GetValue()
		{
			double value = 0;
			foreach (FinancialProduct f in _products)
			{
				value += f.GetEuroPrice();
			}
			return value;
		}
	}
}
