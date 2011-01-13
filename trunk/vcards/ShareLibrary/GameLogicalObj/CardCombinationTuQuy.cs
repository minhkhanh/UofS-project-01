using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ShareLibrary
{
    class CardCombinationTuQuy: CardCombination
    {
        public static CardCombinationTuQuy Create(params CardLogical[] cards)
        {
            CardCombinationTuQuy t = new CardCombinationTuQuy();
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
            return listCards[listCards.Count - 1].CompareValue(((CardCombinationTuQuy)cards).listCards[listCards.Count - 1]);
        }

        protected override bool Check(params CardLogical[] cards)
        {
            if (
                cards.Count() == 4
                && cards[0].CompareRank(cards[1]) == 0
                && cards[2].CompareRank(cards[3]) == 0
                && cards[0].CompareRank(cards[2]) == 0
                )
                return true;
            return false;
        }
        private CardCombinationTuQuy()
        {

        }
    }
}
