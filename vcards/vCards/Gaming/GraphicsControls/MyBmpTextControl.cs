using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public abstract class MyBmpTextControl: MyBmpControl
    {
        string text = "";
        public string Text
        {
            get { return text; }
            set { text = value; }
        }

        public MyBmpTextControl(string cap, Rectangle loc, IBitmap im)
            : base(loc, im)
        {
            text = cap;
        }

        public void DrawText(IGraphics igr)
        {
            IFont font = igr.CreateFont("Tahoma", 10, FontStyle.Bold);
            //igr.DrawString(text, font, new SolidBrush(Color.Black), region);
            igr.DrawText(Region, text, Color.Black, font, FontDrawOptions.DrawTextCenter | FontDrawOptions.DrawTextMiddle);
        }
    }
}
