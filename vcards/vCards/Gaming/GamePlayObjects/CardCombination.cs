using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    /// <summary>
    /// Chua to hop cac quan bai hop le theo luat
    /// </summary>
    public class CardCombination
    {
        List<Card> listCards = new List<Card>();
        public static CardCombination CreateCombination(params Card[] cards)
        {
            CardCombination combination = new CardCombination();

            combination.listCards.AddRange(cards);

            return combination;
        }

        /// <summary>
        /// Kiem tra to hop cac quan bai co dung luat hay khong.
        /// </summary>
        /// <param name="cards">Mang cac quan bai.</param>
        /// <returns>true neu dung theo luat, nguoc lai la false.</returns>
        public bool Check(params Card[] cards)
        {
            return IsRac(cards)||IsDoi(cards)||IsSanh(cards)||IsTuQuy(cards);
        }

        bool IsRac(params Card[] cards)
        {
            if (cards.Count() == 1)
                return true;
            else return false;
        }

        bool IsDoi(params Card[] cards)
        {
            if (cards.Count()%2 != 0)
            {
                return false;
            }
            if (IsTuQuy(cards))
            {
                return false;
            }
            SortByValue(cards);
            for (int i = 0; i < cards.Count(); i +=2 )
            {
                if (cards[i].Value.RankText != cards[i+1].Value.RankText)
                {
                    return false;
                }
            }
            return true;
        }

        bool IsTuQuy(params Card[] cards)
        {
            if (
                cards.Count() == 4
                && cards[0].Value.CompareRank(cards[1].Value) == 0
                && cards[2].Value.CompareRank(cards[3].Value) == 0
                && cards[0].Value.CompareRank(cards[2].Value) == 0
                )
                return true;

            return false;
        }

        bool IsSanh(params Card[] cards)
        {
            if (cards.Count() < 3)
                return false;

            SortByValue(cards);

            if (cards[cards.Count()-1].Value.Rank == CardRank.Duece
                || cards[0].Value.Rank == CardRank.None)
                return false;

            for (int i = 0; i < cards.Count() - 1; ++i)
            {
                if (cards[i].Value.CompareRank(cards[i + 1].Value) == 0)
                    return false;
            }

            return true;
        }

        void SortByValue(params Card[] cards)
        {
            for (int i = 0; i < cards.Count() - 1; ++i)
                for (int j = i + 1; j < cards.Count(); ++j)
                {
                    if (cards[i].Value.CompareValue(cards[j].Value) > 0)
                    {
                        Card tmp = cards[i];
                        cards[i] = cards[j];
                        cards[j] = tmp;
                    }
                }
        }
    }
}
