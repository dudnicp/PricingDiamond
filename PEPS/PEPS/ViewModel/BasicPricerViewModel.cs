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
using Wrapper;

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
                    _update = new RelayCommand<DateTime?>(date =>
                    {
                        try
                        {
                            if (date == null)
                            {
                                throw new Exception("Impossible ! Aucune nouvelle date de rebalancement n'a été choisie.");
                            }
                            DateTime d = (DateTime)date;
                            if (DateTime.Compare(d, HedgingData.LastUpdateDate) < 0)
                            {
                                throw new Exception("Impossible ! La date chosie est antérieure à la date actuelle.");
                            }
                            if (AppData.DaysFromStart(d) > AppData.ObservationDates[AppData.ObservationDates.Length - 1])
                            {
                                throw new Exception("Impossible ! La date chosie est postérieure à la maturité de l'option.");
                            }
                            HedgingData.Update(d);
                        }
                        catch (Exception e)
                        {
                            MessageBox.Show(e.Message, "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                        }

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
