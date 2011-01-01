using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    public class PlayerServer
    {
        int iIndex;
        PackLogical packLogic;
        public vCards.PackLogical PackLogic
        {
            get { return packLogic; }
            set { packLogic = value; }
        }
        PlayerInfo info;
        public PlayerServer(PlayerInfo inf, int i)
        {
            info = inf;
            iIndex = i;
        }
        //public CardLogical this[int idx]
        //{
        //    get
        //    {
        //        return (CardLogical)(idx >= 0 && idx < CARD_NUM ? listCards[idx] : null);
        //    }

        //    set
        //    {
        //        if (idx >= 0 && idx < CARD_NUM)
        //            listCards[idx] = value;
        //    }
        //}
        public void InitCard()//(params CardLogical[] cards)
        {
            //if (cards.Count() < PackLogical.CARD_NUM) return;
            packLogic = new PackLogical();
        }
        public void AddCard(params CardLogical[] cards)
        {
            packLogic.AddCards(cards);
        }
        public void SortCardsByValue()
        {
            packLogic.SortByValue();
        }
    }
}
