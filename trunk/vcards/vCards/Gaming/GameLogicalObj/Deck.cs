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
        List<CardLogical> listCards = new List<CardLogical>(CARD_NUM);

        private void Initialize()
        {
            for (int i = 0; i < listCards.Capacity; ++i)
                listCards.Add(new CardLogical(CardRank.None, CardSuit.None));
        }

        public Deck()
        {
            Initialize();
            Shuffle();
        }

        public void Shuffle()
        {
            bool[] arrAssigned = new bool[CARD_NUM];
            Random rand = new Random();
            for (CardRank rank = CardRank.Three; rank <= CardRank.Duece; ++rank)
            {
                for (CardSuit suit = CardSuit.Spades; suit <= CardSuit.Hearts; ++suit)
                {   
                    bool found = false;
                    while (found == false)
                    {
                        int randIdx = rand.Next(CARD_NUM);
                        if (arrAssigned[randIdx] == false)
                        {
                            listCards[randIdx] = new CardLogical((CardRank)rank, (CardSuit)suit);
                            found = true;
                            arrAssigned[randIdx] = true;
                        }
                    }
                }
            }
        }
        // se bo ham nay
        //public void Deal(params Pack[] packs)
        //{
        //    for (int j = 0; j < packs.Count(); ++j)
        //        packs[j].Clear();

        //    for (int i = 0; i < CARD_NUM; ++i)
        //    {
        //        packs[i % packs.Count()].AddControl(new Card(listCards[i], packs[i % packs.Count()].Side));
        //    }
        //}
        public void DealAndSort(params PlayerServer[] player)
        {
            for (int j = 0; j < player.Count(); ++j)
                player[j].InitCard();

            for (int i = 0; i < CARD_NUM; ++i)
            {
                player[i % player.Count()].AddCard(new CardLogical(listCards[i].Rank, listCards[i].Suit));
            }

            for (int j = 0; j < player.Count(); ++j)
                player[j].SortCardsByValue();
        }
    }
}
