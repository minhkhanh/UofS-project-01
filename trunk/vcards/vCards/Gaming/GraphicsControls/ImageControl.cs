using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class ImageControl: MyControl
    {
        protected IImage iimgBkgr;

        public ImageControl(Rectangle regn, string iimgPath, IGraphics igp)
            : base(regn)
        {
            igp.CreateIImage(iimgPath, out iimgBkgr);
        }

        public ImageControl(Rectangle regn, IImage iimgPath)
            : base(regn)
        {
            iimgBkgr = iimgPath;
        }

        public ImageControl(){}

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
