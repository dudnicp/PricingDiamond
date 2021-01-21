using PEPS.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PEPS.Services
{
    public static class AppInit
    {
        static (List<Currency>, List<Share>) GetDiamondCurrenciesBeta()
        {
            var currencies = new List<Currency>();
            var shares = new List<Share>();

            var euro = new Currency("Euro €", 1);
            var dollar = new Currency("Dollar $", 0.8);

            currencies.Add(euro);
            currencies.Add(dollar);

            shares.Add(new Share("ActionEuro1", euro, 100));
            shares.Add(new Share("ActionEuro2", euro, 50));
            shares.Add(new Share("DollarShare1", dollar, 100));
            shares.Add(new Share("DollarShare2", dollar, 50));

            return (currencies, shares);
        }
    }
}
