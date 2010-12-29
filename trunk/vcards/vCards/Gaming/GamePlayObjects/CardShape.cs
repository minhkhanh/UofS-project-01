using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class CardShape : TransControl
    {
        public const int WIDTH = 29;
        public const int HEIGHT = 41;

        CardValue cardValue;
        public CardValue Value
        {
            get { return cardValue; }
            set { cardValue = value; }
        }

        public CardShape(CardValue val)
        {
            region = new Rectangle(-1, -1, WIDTH, HEIGHT);           

            cardValue = val;

            iimgBkgr = MyResourceManager.GetCardImage(cardValue.Suit);
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

        Rectangle RANKTEXT_OFFSET = new Rectangle(3, 3, 13, 10);
        IFont RANKTEXT_FONT = null;

        private void DrawRankText(IGraphics igp)
        {
            if (RANKTEXT_FONT == null)
                RANKTEXT_FONT = igp.CreateFont("Tahoma", 8, FontStyle.Regular);

            igp.DrawText(
                new Rectangle(region.X+RANKTEXT_OFFSET.X, region.Y+RANKTEXT_OFFSET.Y, RANKTEXT_OFFSET.Width, RANKTEXT_OFFSET.Height)
                , cardValue.RankText
                , Color.Black
                , RANKTEXT_FONT
                , FontDrawOptions.DrawTextLeft | FontDrawOptions.DrawTextMiddle
                );
        }

        public override void Draw(IGraphics igp)
        {
            base.Draw(igp);

            DrawRankText(igp);
        }
    }
}
