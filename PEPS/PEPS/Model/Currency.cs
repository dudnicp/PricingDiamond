using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
	/// <summary>
	/// Classe représentant une devise d'un marché étranger d'un point de
	/// vue du marché Français
	/// </summary>
	class Currency
	{
		private double _changeRate;
		public double ChangeRate
		{
			get { return _changeRate; }
			set { _changeRate = value; }
		}

		private String _name;
		public String Name
		{
			get { return _name; }
		}

		/// <summary>
		/// Constructeur par défaut pour une devise française en €
		/// </summary>
		public Currency()
		{
			_name = "€";
			_changeRate = 1;
		}

		/// <summary>
		/// Constructeur de la classe Currency pour une devise étrangère
		/// </summary>
		/// <param name="name"> Nom de la devise </param>
		/// <param name="value"> Prix en € de la devise </param>
		public Currency(String name, double value)
		{
			_name = name;
			_changeRate = value;
		}

		/// <summary>
		/// Constructeur par recopie
		/// </summary>
		/// <param name="other"> Devise que l'on veut copier </param>
		public Currency(Currency other)
		{
			_name = other._name;
			_changeRate = other._changeRate;
		}

		/// <summary>
		/// Actualise via la base de donnée la valeur du prix de la devise
		/// en €
		/// </summary>
		public void UpdateChange()
		{
			if (_name != "€")
			{
				//TODO :  Accéder à la base de donner pour 
				//récupérer le taux de change 
				// à la date actuelle
			}
		}
	}
}
