using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class ImageControl: MyControl
    {
        protected IImage _iimgBkgr;

        public ImageControl(Rectangle regn, string iimgPath, IGraphics igp)
            : base(regn)
        {
            igp.CreateIImage(iimgPath, out _iimgBkgr);
        }

        public ImageControl(Rectangle regn, IImage iimgBkgr)
            : base(regn)
        {
            _iimgBkgr = iimgBkgr;
        }

        public ImageControl(){}

        public override void DrawBackground(IGraphics igp)
        {
            igp.DrawImageAlphaChannel(_iimgBkgr, region);
        }

        public override void DoDrawing(IGraphics igp)
        {
            DrawBackground(igp);
        }
    }
}
