using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    class CardCombinationSanh: CardCombination
    {
        public static CardCombinationSanh Create(params CardLogical[] cards)
        {
            CardCombinationSanh t = new CardCombinationSanh();
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
            if (listCards.Count != ((CardCombinationSanh)cards).listCards.Count)
            {
                return 0;
            }
            return listCards[listCards.Count - 1].CompareValue(((CardCombinationSanh)cards).listCards[listCards.Count - 1]);
        }

        protected override bool Check(params CardLogical[] cards)
        {
            if (cards.Count() < 3)
                return false;

            if (cards[cards.Count() - 1].Rank == CardRank.Duece
                || cards[0].Rank == CardRank.None)
                return false;

            for (int i = 0; i < cards.Count() - 1; ++i)
            {
                if (cards[i].CompareRank(cards[i + 1]) == 0)
                    return false;
            }

            return true;
        }
        private CardCombinationSanh()
        {

        }
    }
}
