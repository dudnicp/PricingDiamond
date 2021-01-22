using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Model
{
    /// <summary>
    /// Class representing a financial asset
    /// </summary>
    public abstract class Asset : INotifyPropertyChanged

    {
        private string _name;
        private double _euroPrice;

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Name of the asset
        /// </summary>
        public string Name
        {
            get => _name;
            protected set
            {
                if (value != _name)
                {
                    _name = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Name"));
                }
            }
        }

        /// <summary>
        /// Price of the asset in euros
        /// </summary>
        public double EuroPrice
        {
            get => _euroPrice;
            set
            {
                if (value != _euroPrice)
                {
                    _euroPrice = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("EuroPrice"));
                }
            }
        }

        /// <summary>
        /// Constructor, creates an Asset with the given name
        /// </summary>
        /// <param name="name">Name of the asset</param>
        public Asset(string name)
        {
            Name = name;
        }
    }
}
