using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace vCards
{
    public abstract class MyUserControl
    {
        public MyUserControl()
        {

        }

        string text = "";
        public string Text
        {
            get { return text; }
            set { text = value; }
        }

        Rectangle region;
        public Rectangle Region
        {
            get { return region; }
            set { region = value; }
        }

        public MyUserControl(string cap, Rectangle loc)
        {
            text = cap;
            region = loc;
        }

        public void DrawText(IGraphics igr)
        {
            IFont font = igr.CreateFont("Tahoma", 10, FontStyle.Bold);
            //igr.DrawString(text, font, new SolidBrush(Color.Black), region);
            igr.DrawText(Region, text, Color.Black, font, FontDrawOptions.DrawTextCenter | FontDrawOptions.DrawTextMiddle);
        }
    }
}
