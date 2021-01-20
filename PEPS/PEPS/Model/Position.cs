using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant une position sur le marché local
	/// </summary>
	class Position
	{
		private DateTime _purchaseDate;
		/// <summary>
		/// Date d'achat liée à la position
		/// </summary>
		public DateTime PurchaseDate
		{
			get { return _purchaseDate; }
		}

		private double _quantity;
		/// <summary>
		/// Quantité de produit financier liés à la position
		/// </summary>
		public double Quantity
		{
			get { return _quantity; }
		}

		private double _initialLocalValue;
		/// <summary>
		/// Valeur de la position le jour de l'achat dans la monnaie locale
		/// </summary>
		public double InitialLocalValue
		{
			get { return _initialLocalValue; }
		}

		private double _initialEuroValue;
		/// <summary>
		/// Valeur de la position le jour de l'achat en €
		/// </summary>
		public double InitialEuroValue
		{
			get { return _initialEuroValue; }
		}

		private GlobalFinancialProduct _product;
		/// <summary>
		/// Produit financier associé à la position
		/// </summary>
		public GlobalFinancialProduct Product {
			get { return _product; }
		}

		private Boolean _isOpen;
		/// <summary>
		/// Représente si la position est ouverte (valeur à actualiser)
		/// ou fermée (valeur à ne pas actualiser)
		/// </summary>
		public Boolean IsOpen
		{
			get { return _isOpen; }
		}

		/// <summary>
		/// Constructeur par défaut de la classe Position
		/// </summary>
		/// <param name="product"> Produit financié considéré dans la position</param>
		/// <param name="purchaseDate"> Date d'achat du produit financier</param>
		/// <param name="initialLocalPrice"> Prix d'achat dans la monnaie locale</param>
		/// <param name="quantity"> Nombre de part du produit acheté </param>
		public Position(GlobalFinancialProduct product, DateTime purchaseDate, double initialLocalPrice, double quantity)
		{
			_product = product;
			_purchaseDate = purchaseDate;
			_quantity = quantity;
			_initialLocalValue = initialLocalPrice * _quantity;
			_initialEuroValue = initialLocalPrice * product.CurrentEuroPrice;
			_isOpen = true;
		}

		/// <summary>
		/// Renvoie la valeur actuelle dans la monnaie locale de la position
		/// </summary>
		/// <returns> Valeur de la position dans sa monnaie locale </returns>
		public double getLocalValue()
		{
			return _product.CurrentLocalPrice * _quantity;
		}

		/// <summary>
		/// Renvoie la valeur actuelle en € du produit acheté
		/// </summary>
		/// <returns> Valeur du produit dans sa monnaie locale </returns>
		public double getEuroValue()
		{
			return _product.CurrentEuroPrice * _quantity;
		}

		/// <summary>
		/// Renvoie le % d'évolution du prix du produit depuis le départ 
		/// </summary>
		/// <returns>Ecart relatif entre le prix initial et l'actuel </returns>
		public double getEvolution()
		{
			return (getLocalValue() - _initialLocalValue)/InitialLocalValue * 100;
		}
	}
}
