using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class TransControl: ImageControl
    {
        IImage iimgBkgr;

        public TransControl(Rectangle regn, bool enabled, string iimgPath, IGraphics igr)
            : base(regn, enabled)
        {
            igr.CreateIImage(iimgPath, out iimgBkgr);
        }

        public override void DrawBackground(IGraphics igr)
        {
            igr.DrawImageAlphaChannel(iimgBkgr, region);
        }

        public override void Draw(IGraphics igr)
        {
            DrawBackground(igr);
        }
    }
}
