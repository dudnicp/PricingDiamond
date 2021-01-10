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
		public DateTime _maturity;

		public abstract double Payoff();
	}
}
