using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ShareLibrary
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
                if (listCards[0].Rank == CardRank.Duece && cards.GetType() == typeof(CardCombinationDoiThong) && ((CardCombinationDoiThong)cards).ListCards.Count==8)
                {
                    return -1;
                }
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
            if (cards.Count() != 2)
            {
                return false;
            }
            if (cards[0].RankText != cards[1].RankText)
            {
                return false;
            }
            return true;
        }
        private CardCombinationDoi()
        {

        }
        //private static CardCombination TimDoiNhoNhatTrong(PackLogical cards)
        //{

        //}
        //public override CardCombination TimCaiVuaDuDeThangToiTrong(PackLogical cards)
        //{
            
        //}
    }
}
