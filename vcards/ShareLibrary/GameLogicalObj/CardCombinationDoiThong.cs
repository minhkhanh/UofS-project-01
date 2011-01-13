using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ShareLibrary
{
    class CardCombinationDoiThong: CardCombination
    {
        public static CardCombinationDoiThong Create(params CardLogical[] cards)
        {
            CardCombinationDoiThong t = new CardCombinationDoiThong();
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
                if (cards.GetType() == typeof(CardCombinationRac) && ((CardCombinationRac)cards).ListCards[0].Rank == CardRank.Duece)
                {
                    return 1;
                }
                if (cards.GetType() == typeof(CardCombinationDoi) && ((CardCombinationDoi)cards).ListCards[0].Rank == CardRank.Duece && listCards.Count>6)
                {
                    return 1;
                }
                return 0;
            }
            if (listCards.Count != ((CardCombinationDoiThong)cards).listCards.Count)
            {
                return (listCards.Count > ((CardCombinationDoiThong)cards).listCards.Count)? 1 : -1;
            }
            return listCards[listCards.Count - 1].CompareValue(((CardCombinationDoiThong)cards).listCards[listCards.Count - 1]);
        }

        protected override bool Check(params CardLogical[] cards)
        {
            if (cards.Count() % 2 != 0)
            {
                return false;
            }
            if (cards.Count() < 6)
            {
                return false;
            }
            for (int i = 0; i < cards.Count() - 2; i += 2)
            {
                if (cards[i].RankText != cards[i + 1].RankText)
                {
                    return false;
                }
                if (cards[i].CompareRank(cards[i + 2]) != -1)
                {
                    return false;
                }
            }
            return true;
        }
        private CardCombinationDoiThong()
        {

        }
    }
}
