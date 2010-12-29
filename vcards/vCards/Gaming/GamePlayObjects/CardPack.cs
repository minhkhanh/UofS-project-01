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
    public class CardPack: ImgCtrlContainer
    {
        public CardPack(PlayerSide playside, IGraphics igp)
        {
            side = playside;
            listControls.Capacity = CARD_NUM;

            InitRegion(igp);
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

        public CardShape this[int idx]
        {
            get 
            {
                return (CardShape)(idx >= 0 && idx < CARD_NUM ? listControls[idx] : null);
            }

            set
            {
                if (idx >= 0 && idx < CARD_NUM)
                    listControls[idx] = value;
            }
        }

        public override void AddControl(ImageControl card)
        {
            if (listControls.Count == listControls.Capacity)
                return;

            base.AddControl(card);

            card.MouseMove += new EventHandler<MouseEventArgs>(card_MouseMove);
            card.MouseDown += new EventHandler<MouseEventArgs>(card_MouseDown);
        }

        public void card_MouseDown(object o, MouseEventArgs e)
        {
            CardShape card = (CardShape)o;
        }

        public void card_MouseMove(object o, MouseEventArgs e)
        {
            CardShape card = (CardShape)o;

            card.MoveTo(new System.Drawing.Point(e.X, e.Y));
        }

        const int TO_SCREEN_HORIZONS = 20;
        const int TO_SCREEN_VERTICALS = 20;
        const int MIN_CARD_SPACE = 11;
        const int LENGTH = (CARD_NUM - 1) * MIN_CARD_SPACE + CardShape.WIDTH;
        const int BREADTH = CardShape.HEIGHT;
        
        PlayerSide side = PlayerSide.None;

        public void Rearrange(IGraphics igp)
        {
            int cardSpace = (LENGTH - CardShape.WIDTH) / (listControls.Count - 1);
            if (side == PlayerSide.Bottom || side == PlayerSide.Top)
            {
                for (int i = 0; i < listControls.Count; ++i)
                {
                    listControls[i].X = region.X + i * cardSpace;
                    listControls[i].Y = igp.ScreenHeight - TO_SCREEN_HORIZONS - CardShape.HEIGHT;
                }
            }
            else if (side != PlayerSide.None)
            {
                //cardSpace = (igp.ScreenHeight - 2 * TO_SCREEN_HORIZONS - CardShape.WIDTH) / (listControls.Count - 1);

                for (int i = 0; i < listControls.Count; ++i)
                {
                    listControls[i].X = igp.ScreenWidth - TO_SCREEN_VERTICALS - CardShape.HEIGHT;
                    listControls[i].Y = region.Y + i * cardSpace;
                }
            }
        }

        public void SortByValue()
        {
            for (int i = 0; i < listControls.Count - 1; ++i)
                for (int j = i + 1; j < listControls.Count; ++j)
                {
                    CardShape card01 = (CardShape)listControls[i];
                    CardShape card02 = (CardShape)listControls[j];
                    if (card01.Value.CompareTo(card02.Value) > 0)
                    {
                        CardValue tmp = card01.Value;
                        card01.Value = card02.Value;
                        card02.Value = tmp;
                    }
                }
        }

        public override void Draw(IGraphics igp)
        {
            foreach (CardShape i in listControls)
            {
                i.Draw(igp);
            }
        }

        public override void DrawBackground(IGraphics igp)
        {
            //throw new NotImplementedException();
        }
    }
}
