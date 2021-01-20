using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class representing a financial asset
    /// </summary>
    public abstract class Asset
    {
        /// <summary>
        /// Name of the asset
        /// </summary>
        public string Name { get; protected set; }

        /// <summary>
        /// Price of the asset in euros
        /// </summary>
        public double EuroPrice { get; protected set; }

        /// <summary>
        /// Constructor, creates an Asset with the given name
        /// </summary>
        /// <param name="name">Name of the asset</param>
        public Asset(string name)
        {
            Name = name;
        }

        /// <summary>
        /// Updates the price of the asset. The new price is the one observed at the given date.
        /// </summary>
        /// <param name="date">Date of observation</param>
        public virtual void UpdatePrice(DateTime date)
        {
            throw new NotImplementedException();
        }
    }
}
