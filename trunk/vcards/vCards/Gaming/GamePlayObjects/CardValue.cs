using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    /// <summary>
    /// Hoa cua la bai (da duoc sap xep be -> lon de su dung trong luc so sanh)
    /// </summary>
    public enum CardSuit
    {
        None,
        Spades,
        Clubs,
        Diamonds,
        Hearts
    }

    /// <summary>
    /// So nut cua la bai (da duoc sap xep be -> lon de su dung trong luc so sanh)
    /// </summary>
    public enum CardRank
    {
        None,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace,
        Duece
    }

    public class CardValue
    {
        CardSuit suit;
        public CardSuit Suit
        {
            get { return suit; }
        }

        CardRank rank;

        public CardValue(CardRank rnk, CardSuit sui)
        {
            suit = sui;
            rank = rnk;
        }

        public int CompareTo(CardValue target)
        {
            return rank - target.rank == 0 ? suit - target.suit : rank - target.rank;
        }

        public string RankText
        {
            get 
            {
                switch (rank)
                {
                case CardRank.None:
                        return "";
                    case CardRank.Jack:
                        return "J";
                    case CardRank.Queen:
                        return "Q";
                    case CardRank.King:
                        return "K";
                    case CardRank.Ace:
                        return "A";
                    case CardRank.Duece:
                        return "2";
                    default:
                        return ((int)rank + 2).ToString();
                }
            }
        }
    }
}
