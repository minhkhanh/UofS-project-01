using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace vCards
{
    /// <summary>
    /// Lop mo ta co bai 13 la
    /// </summary>
    public class Pack: ImgCtrlContainer
    {
        int[] selectedCards = new int[CARD_NUM];
        public Pack(PlayerSide playside, IGraphics igp)
            : base(igp)
        {
            side = playside;
            listControls.Capacity = CARD_NUM;
            //InitRegion(igp);

            if (side != PlayerSide.Bottom)
            {
                enabled = false;
            }
        }

        private void InitRegion(IGraphics igp)
        {
            switch (side)
            {
                case PlayerSide.Bottom:
                region = new Rectangle((igp.ScreenWidth - LENGTH)/2, igp.ScreenHeight - TO_SCREEN_HORIZONS - BREADTH, LENGTH, BREADTH);
            	break;
                case PlayerSide.Top:
                region = new Rectangle((igp.ScreenWidth - LENGTH) / 2, TO_SCREEN_HORIZONS, LENGTH, BREADTH);
                break;
                case PlayerSide.Left:
                region = new Rectangle(TO_SCREEN_VERTICALS, (igp.ScreenHeight - LENGTH)/2, BREADTH, LENGTH);
                break;
                case PlayerSide.Right:
                region = new Rectangle(igp.ScreenWidth - TO_SCREEN_VERTICALS - BREADTH, (igp.ScreenHeight - LENGTH) / 2, BREADTH, LENGTH);
                break;
            }
        }

        public const int CARD_NUM = 13;

        public Card this[int idx]
        {
            get 
            {
                return (Card)(idx >= 0 && idx < CARD_NUM ? listControls[idx] : null);
            }

            set
            {
                if (idx >= 0 && idx < CARD_NUM)
                    listControls[idx] = value;
            }
        }

        public override void AddControl(ImageControl cardControl)
        {
            if (listControls.Count == listControls.Capacity)
                return;

            base.AddControl(cardControl);

            cardControl.MouseMove += new EventHandler<MouseEventArgs>(card_MouseMove);
            cardControl.MouseDown += new EventHandler<MouseEventArgs>(card_MouseDown);
            cardControl.MouseUp += new EventHandler<MouseEventArgs>(card_MouseUp);

            Card card = (Card)cardControl;
            card.Pack = this;
            card.Index = listControls.Count - 1;
        }

        public void card_MouseUp(object o, MouseEventArgs e)
        {
            Card card = (Card)o;
            if (idxSelected == card.Index)
            {
                card.Selected = !card.Selected;
                idxSelected = -1;
            }
        }

        int idxSelected = -1;
        public void card_MouseDown(object o, MouseEventArgs e)
        {
            Card card = (Card)o;

            if (card.Index > idxSelected)
                idxSelected = card.Index;
        }

        public void card_MouseMove(object o, MouseEventArgs e)
        {
            Card card = (Card)o;

            if (card.Index == idxSelected)
                card.MoveTo(new System.Drawing.Point(e.X, e.Y));
        }

        const int TO_SCREEN_HORIZONS = 20;
        const int TO_SCREEN_VERTICALS = 20;
        const int MIN_CARD_SPACE = 11;
        const int LENGTH = (CARD_NUM - 1) * MIN_CARD_SPACE + Card.BREADTH;
        const int BREADTH = Card.LENGTH;

        PlayerSide side = PlayerSide.None;
        public PlayerSide Side
        {
            get { return side; }
            //set { side = value; }
        }

        public PackLogical GetSelectedCard()
        {
            PackLogical pl = new PackLogical();
            for (int i = 0; i < listControls.Count; ++i )
            {
                if (((Card)listControls[i]).Selected)
                {
                    pl.AddCards(((Card)listControls[i]).Value);
                }
            }
            pl.SortByValue();
            return pl;
        }

        public void RemoveSelectedCard()
        {
            for (int i = 0; i < listControls.Count; )
            {
                if (((Card)listControls[i]).Selected)
                {
                    RemoveAt(i);
                }
                else ++i;
            }
        }

        public void Rearrange(IGraphics igp)
        {
            int cardSpace = (LENGTH - Card.BREADTH) / (listControls.Count - 1);

            switch (side)
            {
                case PlayerSide.Bottom:
                    for (int i = 0; i < listControls.Count; ++i)
                    {
                        listControls[i].X = (igp.ScreenWidth-LENGTH)/2 + i * cardSpace;
                        listControls[i].Y = igp.ScreenHeight - TO_SCREEN_HORIZONS - Card.LENGTH;
                    }
                    break;
                case PlayerSide.Top:
                    for (int i = 0; i < listControls.Count; ++i)
                    {
                        listControls[i].X = (igp.ScreenWidth - LENGTH) / 2 + i * cardSpace;
                        listControls[i].Y = TO_SCREEN_HORIZONS;
                    }
                    break;
                case PlayerSide.Left:
                    for (int i = 0; i < listControls.Count; ++i)
                    {
                        listControls[i].X = TO_SCREEN_VERTICALS;
                        listControls[i].Y = (igp.ScreenHeight - LENGTH)/2 + i * cardSpace;
                    }
                    break;
                case PlayerSide.Right:
                    for (int i = 0; i < listControls.Count; ++i)
                    {
                        listControls[i].X = igp.ScreenWidth - TO_SCREEN_VERTICALS - Card.LENGTH;
                        listControls[i].Y = (igp.ScreenHeight - LENGTH) / 2 + i * cardSpace;
                    }
                    break;
            }
        }

        public void SortByValue()
        {
            for (int i = 0; i < listControls.Count - 1; ++i)
                for (int j = i + 1; j < listControls.Count; ++j)
                {
                    Card card01 = (Card)listControls[i];
                    Card card02 = (Card)listControls[j];
                    if (card01.Value.CompareValue(card02.Value) > 0)
                    {
                        Card tmp = card01;
                        card01 = card02;
                        card02 = tmp;

                        card01.Index = i;
                        card02.Index = j;

                        listControls[i] = card01;
                        listControls[j] = card02;
                    }
                }
        }

        //public override void Draw(IGraphics igp)
        //{
        //    base.Draw(igp);

        //    igp.DrawFilledRect(region, Color.Red);
        //}
    }
}
