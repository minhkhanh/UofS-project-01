using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    class VongDi
    {
        private List<BuocDi> listBuocDi =  new List<BuocDi>();
        public int Count
        {
            get { return listBuocDi.Count; }
        }
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
        public void Clear()
        {
            listBuocDi.Clear();
        }
    }
}
