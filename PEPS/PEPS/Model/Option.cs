using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Représente une Option avec un payoff en général
	/// </summary>
	abstract class Option : FinancialProduct
	{
		protected DateTime _maturity;
		public DateTime Maturity
		{
			get { return _maturity; }
		}

		/// <summary>
		/// Constructeur par défaut de la classe Option
		/// </summary>
		/// <param name="currency"> Devise de l'option</param>
		/// <param name="name"> Nom de l'option </param>
		/// <param name="initialPrice"> Prix initial </param>
		/// <param name="purchaseDate"> Date d'achat de l'option </param>
		/// <param name="maturity"> Date de maturité </param>
		public Option(Currency currency, String name, double initialPrice, DateTime purchaseDate, DateTime maturity) : base(currency, name, initialPrice, purchaseDate)
		{
			_maturity = maturity;
		}

		/// <summary>
		/// Constructeur par recopie de l'option
		/// </summary>
		/// <param name="other"> Option que l'on veut recopier </param>
		public Option(Option other) : base(other)
		{
			_maturity = other.Maturity;
		}

		/// <summary>
		/// Fonction Payoff de l'option étudiée
		/// </summary>
		/// <returns> La valeur du Payoff que récupère le possesseur
		/// de l'option à maturité </returns>
		public abstract double Payoff();
	}
}
