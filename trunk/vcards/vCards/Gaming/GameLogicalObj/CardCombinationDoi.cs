using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class CardCombinationDoi: CardCombination
    {
        public static CardCombinationDoi Create(params CardLogical[] cards)
        {
            CardCombinationDoi t = new CardCombinationDoi();
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
                return 0;
            }
            if (listCards.Count != ((CardCombinationDoi)cards).listCards.Count)
            {
                return 0;
            }
            return listCards[listCards.Count - 1].CompareValue(((CardCombinationDoi)cards).listCards[listCards.Count - 1]);
        }

        protected override bool Check(params CardLogical[] cards)
        {
            if (cards.Count() % 2 != 0)
            {
                return false;
            }
            if (cards.Count() == 4)
            {
                return false;
            }
            for (int i = 0; i < cards.Count() - 2; i += 2)
            {
                if (cards[i].RankText != cards[i + 1].RankText)
                {
                    return false;
                }
                if (cards[i].CompareRank(cards[i + 2]) == -1)
                {
                    return false;
                }
            }
            return true;
        }
        private CardCombinationDoi()
        {

        }
    }
}
