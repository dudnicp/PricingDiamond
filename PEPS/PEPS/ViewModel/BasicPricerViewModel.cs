using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PEPS.Model;

namespace PEPS.ViewModel
{
    /// <summary>
    /// ViewModel for managing BasicPricerView
    /// </summary>
    class BasicPricerViewModel : INotifyPropertyChanged
    {
        protected HedgingData _hedgingData;
        /// <summary>
        /// Binding Data
        /// </summary>
        public HedgingData HedgingData
        {
            get => _hedgingData;
            protected set
            {
                if (value != HedgingData)
                {
                    HedgingData = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("HedgingData"));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }
}
