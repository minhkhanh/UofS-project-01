using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImageButton: BmpControl
    {
        public ImageButton(Rectangle regn, bool enabled, string ibmpPath, IGraphics igr, string iimgPath)
            : base(regn, enabled, ibmpPath, igr)
        {
            igr.CreateIImage(iimgPath, out iimgHover);
        }

        IImage iimgHover;

        public void DrawHover(IGraphics igr)
        {
            igr.DrawImageAlphaChannel(iimgHover, region);
        }

        public override void Draw(IGraphics igr)
        {
            base.Draw(igr);

            if (mouseState == MouseState.MouseDown)
                DrawHover(igr);
        }
    }
}
