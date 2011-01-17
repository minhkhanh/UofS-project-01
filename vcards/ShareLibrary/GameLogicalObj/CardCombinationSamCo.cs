using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ShareLibrary
{
    class CardCombinationSamCo: CardCombination
    {
        public static CardCombinationSamCo Create(params CardLogical[] cards)
        {
            CardCombinationSamCo t = new CardCombinationSamCo();
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
            return listCards[listCards.Count - 1].CompareValue(((CardCombinationSamCo)cards).listCards[listCards.Count - 1]);
        }

        protected override bool Check(params CardLogical[] cards)
        {
            if (
                cards.Count() == 3
                && cards[0].CompareRank(cards[1]) == 0
                && cards[0].CompareRank(cards[2]) == 0
                )
                return true;

            return false;
        }
        private CardCombinationSamCo()
        {

        }
    }
}
