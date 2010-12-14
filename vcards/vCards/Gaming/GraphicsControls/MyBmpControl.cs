using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class MyBmpControl : MyUserControl
    {
        IBitmap ibmpBkgr;
        public IBitmap BmpBackground
        {
            get { return ibmpBkgr; }
            set { ibmpBkgr = value; }
        }

        public MyBmpControl()
        {

        }

        public MyBmpControl(string cap, Rectangle loc, IBitmap ibmp)
            : base(cap, loc)
        {
            ibmpBkgr = ibmp;
        }

        public void DrawBkgr(IGraphics igr)
        {
            igr.DrawBitmap(Region, ibmpBkgr);
        }
    }
}
