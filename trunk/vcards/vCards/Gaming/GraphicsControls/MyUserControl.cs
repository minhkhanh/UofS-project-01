using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace vCards
{
    public abstract class MyUserControl
    {
        public MyUserControl()
        {

        }

        Rectangle region;
        public Rectangle Region
        {
            get { return region; }
            set { region = value; }
        }

        public MyUserControl(Rectangle loc)
        {
            //text = cap;
            region = loc;
        }
    }
}
