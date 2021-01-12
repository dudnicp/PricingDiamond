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
	abstract class Option : GlobalFinancialProduct
	{
		protected DateTime _maturity;
		/// <summary>
		/// Date de maturité de l'option
		/// </summary>
		public DateTime Maturity
		{
			get { return _maturity; }
		}

		/// <summary>
		/// Constructeur de la classe Option
		/// </summary>
		/// <param name="name">Nom de l'option</param>
		/// <param name="localPrice"> Prix de l'option dans son marché </param>
		/// <param name="currency">Devise associée à l'option</param>
		/// <param name="maturity"> Date de maturité de l'option</param>
		public Option(String name, double localPrice, Currency currency, DateTime maturity)
			   : base(name, localPrice, currency)
		{
			_maturity = maturity;
		}

		/// <summary>
		/// Renvoie le payoff de l'option à la date de maturité
		/// </summary>
		/// <returns> Payoff à maturité </returns>
		public abstract double Payoff();
	}
}
