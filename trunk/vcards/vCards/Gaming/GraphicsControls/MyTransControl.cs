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

        public MyTransControl(Rectangle loc, IImage iimg)
            : base(loc)
        {
            iimgBkgr = iimg;
        }

        public void DrawBkgr(IGraphics igr)
        {
            igr.DrawImageAlphaChannel(iimgBkgr, Region);
        }

        #region IDisposable Members

        public override void Dispose()
        {

        }

        #endregion
    }
}
