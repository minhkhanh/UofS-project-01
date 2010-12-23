using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImageButton: ImageControl
    {
        public ImageButton(Rectangle regn, bool visi, string capt, IBitmap ibmp, string iimgPath, IGraphics igr)
            : base(regn, visi, capt, ibmp, igr)
        {
            iimgHover = igr.CreateIImage(iimgPath);
        }

        IImage iimgHover;

        public void DrawHover(IGraphics igr)
        {
            igr.DrawImageAlphaChannel(iimgHover, Region);
        }
    }
}
