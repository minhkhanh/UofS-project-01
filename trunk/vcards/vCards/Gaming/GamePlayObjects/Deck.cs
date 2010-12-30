using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Collections;

namespace vCards
{
    public class Deck
    {
        public const int CARD_NUM = 52;
        List<CardValue> listCards = new List<CardValue>(CARD_NUM);

        private void Initialize()
        {
            for (int i = 0; i < listCards.Capacity; ++i)
                listCards.Add(new CardValue(CardRank.None, CardSuit.None));
        }

        public Deck()
        {
            Initialize();
            Shuffle();
        }

        public void Shuffle()
        {
            bool[] arrAssigned = new bool[CARD_NUM];
            for (CardRank rank = CardRank.Three; rank <= CardRank.Duece; ++rank)
            {
                for (CardSuit suit = CardSuit.Spades; suit <= CardSuit.Hearts; ++suit)
                {
                    Random rand = new Random();
                    bool found = false;
                    while (found == false)
                    {
                        int randIdx = rand.Next(CARD_NUM);
                        if (arrAssigned[randIdx] == false)
                        {
                            listCards[randIdx] = new CardValue((CardRank)rank, (CardSuit)suit);
                            found = true;
                            arrAssigned[randIdx] = true;
                        }
                    }
                }
            }
        }

        public void Deal(params Pack[] packs)
        {
            for (int j = 0; j < packs.Count(); ++j)
                packs[j].Clear();

            for (int i = 0; i < CARD_NUM; ++i)
            {
                packs[i % packs.Count()].AddControl(new Card(listCards[i], packs[i % packs.Count()].Side));
            }
        }
    }
}
