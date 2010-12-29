using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImageButton: BmpControl
    {
        public ImageButton(Rectangle regn, string ibmpPath, IGraphics igp, string iimgPath)
            : base(regn, ibmpPath, igp)
        {
            igp.CreateIImage(iimgPath, out iimgHover);
        }

        IImage iimgHover;

        public void DrawHover(IGraphics igp)
        {
            igp.DrawImageAlphaChannel(iimgHover, region);
        }

        public override void Draw(IGraphics igp)
        {
            base.Draw(igp);

            if (mouseState == MouseState.MouseDown)
                DrawHover(igp);
        }
    }
}
