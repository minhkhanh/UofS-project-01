using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    public class PackLogical
    {
        public const int CARD_NUM = 13;
        int iID = 0;
        public int ID
        {
            get { return iID; }
            set { iID = value; }
        }
        protected List<CardLogical> listCards = new List<CardLogical>(CARD_NUM);
        public PackLogical(params CardLogical[] cards)
        {
            listCards.Clear();
            listCards.AddRange(cards);
        }
        public virtual void AddCards(params CardLogical[] cards)
        {
            if (listCards.Count + cards.Count() > CARD_NUM) return;
            listCards.AddRange(cards);
        }
    }
}
