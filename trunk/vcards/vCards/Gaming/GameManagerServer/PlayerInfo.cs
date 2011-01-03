using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class PlayerInfo
    {
        //int id = -1;
        //public int ID   //ID o trong mang tuong duong IP
        //{
        //    get { return id; }
        //    set { id = value; }
        //}
        int iID = -1; // dinh danh vi tri trong ban co
        public int IdPlayer //=0 thi la key
        {
            get { return iID; }
            set { iID = value; }
        }
        string strName = "";
        public string Name
        {
            get { return strName; }
            set { strName = value; }
        }
        public PlayerInfo(string str)
        {
            strName = str;
        }
    }
}
