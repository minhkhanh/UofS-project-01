using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    /// <summary>
    /// Chua to hop cac quan bai hop le theo luat
    /// </summary>
    public abstract class CardCombination : PackLogical
    {
        public static CardCombination CreateCombination(params CardLogical[] cards)
        {
            CardCombination t;
            SortCardsByValue(cards);
            t = CardCombinationDoi.Create(cards);
            if (t!=null)
            {
                return t;
            }
            t = CardCombinationRac.Create(cards);
            if (t != null)
            {
                return t;
            }
            t = CardCombinationSamCo.Create(cards);
            if (t != null)
            {
                return t;
            }
            t = CardCombinationSanh.Create(cards);
            if (t != null)
            {
                return t;
            }
            t = CardCombinationTuQuy.Create(cards);
            if (t != null)
            {
                return t;
            }
            t = CardCombinationDoi.Create(cards);
            if (t != null)
            {
                return t;
            }
            t = CardCombinationDoiThong.Create(cards);
            if (t != null)
            {
                return t;
            }
            t = CardCombinationNhieuDoi.Create(cards);
            if (t != null)
            {
                return t;
            }
            return null;
        }
        public static CardCombination CreateCombination(params Card[] cards)
        {
            List<CardLogical> list = new List<CardLogical>();
            foreach (Card c in cards)
            {
                list.Add((CardLogical)c);
            }
            return CreateCombination(list.ToArray());
        }
        public abstract int CompareTo(CardCombination cards);
        protected abstract bool Check(params CardLogical[] cards);
        //public abstract CardCombination TimCaiVuaDuDeThangToiTrong(PackLogical cards);
        public static void SortCardsByValue(params CardLogical[] cards)
        {
            for (int i = 0; i < cards.Count() - 1; ++i)
                for (int j = i + 1; j < cards.Count(); ++j)
                {
                    if (cards[i].CompareValue(cards[j]) > 0)
                    {
                        CardLogical tmp = cards[i];
                        cards[i] = cards[j];
                        cards[j] = tmp;
                    }
                }
        }
    }
}
