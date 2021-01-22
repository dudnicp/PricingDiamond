using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using PEPS.Model;
using PEPS.Services;

namespace PEPS.ViewModel
{
    /// <summary>
    /// ViewModel for managing BasicPricerView
    /// </summary>
    public class BasicPricerViewModel : INotifyPropertyChanged
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
                if (value != _hedgingData)
                {
                    _hedgingData = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("HedgingData"));
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Command to execute when the Update button of the ui is clicked
        /// </summary>
        private ICommand _update;
        public ICommand Update
        {
            get
            {
                if (_update == null)
                {
                    _update = new RelayCommand<DateTime>(date =>
                    {
                        HedgingData.Update(date);
                    });
                }
                return _update;
            }
        }

        /// <summary>
        /// Constructor (place holder)
        /// </summary>
        public BasicPricerViewModel()
        {
            AppData.Init();
            HedgingData = new HedgingData();
        }

    }
}
