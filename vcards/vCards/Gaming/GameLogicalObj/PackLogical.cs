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
        public List<CardLogical> ListCards
        {
            get { return listCards; }
            set { listCards = value; }
        }
        public int CardsCount
        {
            get { return listCards.Count; }            
        }
        public CardLogical this[int idx]
        {
            get
            {
                return (CardLogical)(idx >= 0 && idx < CARD_NUM ? listCards[idx] : null);
            }

            set
            {
                if (idx >= 0 && idx < CARD_NUM)
                    listCards[idx] = value;
            }
        }
        public CardLogical GetMinCard()
        {
            if (listCards.Count<=0)
            {
                return null;
            }
            CardLogical t = listCards[0];
            for (int i = 1; i < listCards.Count; ++i )
            {
                if (t.CompareValue(listCards[i])<0)
                {
                    t = listCards[i];
                }
            }
            return t;
        }
        public bool IsHave(params CardLogical[] cards)
        {
            foreach (CardLogical card in cards)
            {
                bool bHave = false;
                for (int i = 0; i < listCards.Count; ++i )
                {
                    if (listCards[i].CompareValue(card)==0)
                    {
                        bHave = true;
                        break;
                    }
                }
                if (!bHave)
                {
                    return false;
                }
            }
            return true;
        }
        public bool IsChua(CardCombination cards)
        {
            foreach (CardLogical card in cards.listCards)
            {
                if (!IsHave(card))
                {
                    return false;
                }
            }
            return true;
        }
        public PackLogical(params CardLogical[] cards)
        {
            listCards.Clear();
            listCards.AddRange(cards);
        }
        public void SortByValue()
        {
            for (int i = 0; i < listCards.Count() - 1; ++i)
                for (int j = i + 1; j < listCards.Count(); ++j)
                {
                    if (listCards[i].CompareValue(listCards[j]) > 0)
                    {
                        CardLogical tmp = listCards[i];
                        listCards[i] = listCards[j];
                        listCards[j] = tmp;
                    }
                }
        }
        public void Clear()
        {
            listCards.Clear();
        }
        public virtual void AddCards(params CardLogical[] cards)
        {
            if (listCards.Count + cards.Count() > CARD_NUM) return;
            listCards.AddRange(cards);
        }
    }
}
