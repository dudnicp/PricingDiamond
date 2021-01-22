using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using PEPS.Model;

namespace PEPS.ViewModel
{
    /// <summary>
    /// ViewModel for managing BasicPricerView
    /// </summary>
    public class BasicPricerViewModel : INotifyPropertyChanged
    {
        protected AppData _appData;
        /// <summary>
        /// Binding Data
        /// </summary>
        public AppData AppData
        {
            get => _appData;
            protected set
            {
                if (value != _appData)
                {
                    _appData = value;
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
                        AppData.Update(date);
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
            AppData = new AppData();
        }

    }
}
