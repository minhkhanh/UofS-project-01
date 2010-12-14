using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class MyTransControl : MyUserControl
    {
        IImage iimgBkgr;

        public MyTransControl(string cap, Rectangle loc, IImage iimg)
            : base(cap, loc)
        {
            iimgBkgr = iimg;
        }

        public void DrawBkgr(IGraphics igr)
        {
            igr.DrawImageAlphaChannel(iimgBkgr, Region);
        }
    }
}
