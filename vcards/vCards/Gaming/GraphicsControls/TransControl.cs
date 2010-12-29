using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class TransControl: ImageControl
    {
        protected IImage iimgBkgr;

        public TransControl(Rectangle regn, string iimgPath, IGraphics igp)
            : base(regn)
        {
            igp.CreateIImage(iimgPath, out iimgBkgr);
        }

        public TransControl(){}

        public override void DrawBackground(IGraphics igp)
        {
            igp.DrawImageAlphaChannel(iimgBkgr, region);
        }

        public override void Draw(IGraphics igp)
        {
            DrawBackground(igp);
        }
    }
}
