using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImageLabel : BmpControl
    {
        string caption;

        public ImageLabel(Rectangle regn, bool enabled, string ibmpPath, IGraphics igr, string capt)
            : base(regn, enabled, ibmpPath, igr)
        {
            caption = capt;
        }

        public void DrawCaption(IGraphics igr, Color clr, IFont font, FontDrawOptions opts)
        {
            igr.DrawText(region, caption, clr, font, opts);
        }
    }
}
