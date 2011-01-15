using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImageLabel : ImageControl
    {
        string caption;

        public ImageLabel(Rectangle regn, string ibmpPath, IGraphics igp, string capt)
            : base(regn, ibmpPath, igp)
        {
            caption = capt;
        }

        public void DrawCaption(IGraphics igp, Color clr, IFont font, FontDrawOptions opts)
        {
            igp.DrawText(region, caption, clr, font, opts);
        }
    }
}
