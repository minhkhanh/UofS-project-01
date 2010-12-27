using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class CardShape : TransControl
    {
        CardValue cardValue;
        public CardValue Value
        {
            get { return cardValue; }
            set { cardValue = value; }
        }

        public CardShape(Rectangle regn, bool isEnabled, string ibmpPath, IGraphics igr, CardValue cardVal)
            : base(regn, isEnabled, ibmpPath, igr)
        {
            cardValue = cardVal;
        }

        Point clickOffset = new Point(0, 0);
        public override void OnMouseDown(object o, System.Windows.Forms.MouseEventArgs e)
        {
            base.OnMouseDown(o, e);

            if (mouseState == MouseState.MouseDown)
            {
                clickOffset = new Point(this.X - e.X, this.Y - e.Y);
            }
        }

        public void MoveTo(Point des)
        {
            this.X = des.X + clickOffset.X;
            this.Y = des.Y + clickOffset.Y;
        }
    }
}
