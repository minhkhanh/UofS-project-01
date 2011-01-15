using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    class NhomBaiDanhRa: ImgCtrlContainer
    {
        public const int CARD_NUM = 13;
        public NhomBaiDanhRa(IGraphics igp)
            : base(igp)
        {
            listControls.Capacity = CARD_NUM;

            enabled = false;
        }

        public NhomBaiDanhRa(IGraphics igp, PackLogical packLogic)
            : base(igp)
        {
            listControls.Capacity = CARD_NUM;
            //InitRegion(igp);

            foreach (CardLogical card in packLogic.ListCards)
            {
                this.ManageControl(new Card(card, PlayerSide.Bottom));
            }

            enabled = false;
        }       

        public override int ManageControl(MyControl cardControl)
        {
            if (listControls.Count == listControls.Capacity)
                return -1;

            base.ManageControl(cardControl);

            Card card = (Card)cardControl;
            card.Index = listControls.Count - 1;
            return listControls.Count - 1;
        }

        //const int TO_SCREEN_HORIZONS = 20;
        const int TO_SCREEN_HORIZONS = 100;
        const int TO_SCREEN_VERTICALS = 20;
        const int MIN_CARD_SPACE = 11;
        const int MAX_CARD_SPACE = 22;
        const int LENGTH = (CARD_NUM - 1) * MIN_CARD_SPACE + Card.BREADTH;
        const int BREADTH = Card.LENGTH;

        public void Rearrange(IGraphics igp)
        {
            int cardSpace = listControls.Count <= 1 ? 0 : (LENGTH - Card.BREADTH) / (listControls.Count - 1);
            if (cardSpace>MAX_CARD_SPACE)
            {
                cardSpace = MAX_CARD_SPACE;
            }
            for (int i = 0; i < listControls.Count; ++i)
            {
                listControls[i].X = (igp.ScreenWidth-LENGTH)/2 + i * cardSpace;
                listControls[i].Y = igp.ScreenHeight - TO_SCREEN_HORIZONS - Card.LENGTH;
            }
        }
    }
}
