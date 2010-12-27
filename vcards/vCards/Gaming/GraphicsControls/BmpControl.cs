using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class BmpControl: ImageControl
    {
        protected IBitmap bmpBkgr;

        public BmpControl(Rectangle regn, bool enabled, string bmpPath, IGraphics igr)
            : base(regn, enabled)
        {
            bmpBkgr = igr.CreateBitmap(bmpPath, true);
        }

        public override void DrawBackground(IGraphics igr)
        {
            igr.DrawBitmap(region, bmpBkgr);
        }

        public override void Draw(IGraphics igr)
        {
            DrawBackground(igr);
        }
    }
}
