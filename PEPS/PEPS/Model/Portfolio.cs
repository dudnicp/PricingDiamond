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
		private List<Position> _listPositions;
		/// <summary>
		/// Liste des positions du portefeuilles
		/// </summary>
		public List<Position> ListPositions
		{
			get { return _listPositions; }
		}

		/// <summary>
		/// Constructeur d'un portefeuille vide
		/// </summary>
		public Portfolio()
		{
			_listPositions = new List<Position>();
		}

		/// <summary>
		/// Construction du portefeuille avec une liste de position
		/// </summary>
		/// <param name="listPositions"> Liste des positions</param>
		public Portfolio(List<Position> listPositions)
		{
			_listPositions = new List<Position>(ListPositions);
		}

		/// <summary>
		/// Renvoie la valeur actuelle du portefeuille en €
		/// </summary>
		/// <returns> Valeur en € du portefeuille</returns>
		public double GetValue()
		{
			double value = 0;
			foreach (Position p in _listPositions)
			{
				value += p.getEuroValue();
			}
			return value;
		}
	}
}
