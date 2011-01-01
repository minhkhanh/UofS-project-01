using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{   //6 doi
    class CardCombinationNhieuDoi: CardCombination
    {
        public static CardCombinationNhieuDoi Create(params CardLogical[] cards)
        {
            CardCombinationNhieuDoi t = new CardCombinationNhieuDoi();
            CardCombination.SortCardsByValue(cards);
            if (t.Check(cards))
            {
                t.AddCards(cards);
            }
            else t = null;
            return t;
        }
        public override int CompareTo(CardCombination cards)
        {
            if (this.GetType() != cards.GetType())
            {
                return 1;
            }
            if (listCards.Count != ((CardCombinationNhieuDoi)cards).listCards.Count)
            {
                return 0;
            }
            return listCards[listCards.Count - 1].CompareValue(((CardCombinationNhieuDoi)cards).listCards[listCards.Count - 1]);
        }

        protected override bool Check(params CardLogical[] cards)
        {
            if (cards.Count() != 12)
            {
                return false;
            }
            for (int i = 0; i < cards.Count() - 1; i += 2)
            {
                if (cards[i].RankText != cards[i + 1].RankText)
                {
                    return false;
                }
            }
            return true;
        }
        private CardCombinationNhieuDoi()
        {

        }
    }
}
