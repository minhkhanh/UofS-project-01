using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class VongDi
    {
        private List<BuocDi> listBuocDi =  new List<BuocDi>();
        public BuocDi GetLastBuocDi()
        {
            if (listBuocDi.Count==0)
            {
                return null;
            }
            return listBuocDi[listBuocDi.Count - 1];
        }
        // gia su da kiem tra roi
        public void ThemBuoiDi(BuocDi buoc)
        {
            listBuocDi.Add(buoc);
        }
    }
}
