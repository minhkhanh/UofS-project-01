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

        public MyBmpControl(Rectangle loc, IBitmap ibmp)
            : base(loc)
        {
            ibmpBkgr = ibmp;
        }

        public virtual void DrawBkgr(IGraphics igr)
        {
            igr.DrawBitmap(Region, ibmpBkgr);
        }
    }
}
