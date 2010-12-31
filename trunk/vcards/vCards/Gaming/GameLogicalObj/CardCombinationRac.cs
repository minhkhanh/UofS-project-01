using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class CardCombinationRac : CardCombination
    {
        public override int CompareTo(CardCombination cards)
        {
            if (this.GetType()!=cards.GetType())
            {
                return 0;
            }
            return listCards[0].CompareValue(((CardCombinationRac)cards).listCards[0]);
        }
        public static CardCombinationRac Create(params CardLogical[] cards)
        {
            CardCombinationRac t = new CardCombinationRac();
            CardCombination.SortCardsByValue(cards);
            if (t.Check(cards))
            {
                t.AddCards(cards);
            }
            else t = null;
            return t;
        }
        protected override bool Check(params CardLogical[] cards)
        {
            if (cards.Count() == 1)
                return true;
            else return false;
        }
        private CardCombinationRac()
        {

        }
    }
}
