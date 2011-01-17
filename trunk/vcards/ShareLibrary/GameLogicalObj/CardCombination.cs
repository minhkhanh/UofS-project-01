using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ShareLibrary
{
    /// <summary>
    /// Chua to hop cac quan bai hop le theo luat
    /// </summary>
    public class CardCombination : PackLogical
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
        /// <summary>
        /// Ham tra ve danh sach cac tap bai hop le co chua cac la bai truyen vao
        /// </summary>
        /// <param name="cards"></param>
        /// <param name="card"></param>
        /// <returns></returns>
        public static CardCombination[] GetCombinationCoChua(PackLogical pack, CardCombination cards) 
        {
            //if nay co the bo???
            //if (!pack.IsHave(cards))
            //{
            //    return null;
            //}
            PackLogical packNew = new PackLogical(pack);
            List<CardCombination> listKQ = new List<CardCombination>();
            listKQ.Add(cards);
            packNew.PhepHieu(cards);
            if (cards.GetType()==typeof(CardCombinationRac))
            {
                //co the mo thanh doi hoac sanh

                //doi thanh doi
                foreach (CardLogical card in packNew.ListCards)
                {
                    if (card.CompareRank(cards[0])==0)
                    {
                        CardCombination temp = CardCombinationDoi.Create(card, cards[0]);
                        if (temp != null)
                        {
                            CardCombination[] list = GetCombinationCoChua(packNew, temp);
                            if (list!=null && list.Count()>0) listKQ.AddRange(list);
                        }
                    }
                }
                //doi thanh sanh
                foreach (CardLogical card1 in packNew.ListCards)
                {
                    if (card1.Rank == cards[0].Rank + 1)
                    {
                        foreach (CardLogical card2 in packNew.ListCards)
                        {
                            if (card2.Rank == cards[0].Rank + 2)
                            {
                                CardCombination temp = CardCombinationSanh.Create(cards[0], card1, card2);
                                if (temp != null)
                                {
                                    CardCombination[] list = GetCombinationCoChua(packNew, temp);
                                    if (list != null && list.Count() > 0) listKQ.AddRange(list);
                                }
                            }
                        }
                    }
                }

            }
            else if (cards.GetType() == typeof(CardCombinationDoi))
            {
                //co the mo rong thanh sam co, tu quy, doi thong

                //thu mo thanh sam co
                foreach (CardLogical card in packNew.ListCards)
                {
                    if (card.Rank == cards[0].Rank)
                    {
                        List<CardLogical> t = new List<CardLogical>();
                        t.AddRange(cards.ToArray());
                        t.Add(card);
                        CardCombination temp = CardCombinationSamCo.Create(t.ToArray());
                        if (temp != null)
                        {
                            CardCombination[] list = GetCombinationCoChua(packNew, temp);
                            if (list != null && list.Count() > 0) listKQ.AddRange(list);
                        }
                    }
                }

                //thu mo thanh tu quy
                // khong mo rong doi thanh tu quy se bi trung khi mo rong sam co thanh tu quy
                //foreach (CardLogical card1 in packNew.ListCards)
                //{
                //    if (card1.Rank == cards[0].Rank)
                //    {
                //        foreach (CardLogical card2 in packNew.ListCards)
                //        {
                //            if (card2!=card1 && card2.Rank == cards[0].Rank)
                //            {
                //                List<CardLogical> t = new List<CardLogical>();
                //                t.AddRange(cards.ToArray());
                //                t.Add(card1);
                //                t.Add(card2);
                //                CardCombination temp = CardCombinationTuQuy.Create(t.ToArray());
                //                if (temp != null)
                //                {
                //                    CardCombination[] list = GetCombinationCoChua(packNew, temp);
                //                    if (list!=null && list.Count()>0) listKQ.AddRange(list);
                //                }
                //            }
                //        }
                //    }
                //}

                //thu mo thanh doi thong
                foreach (CardLogical card1 in packNew.ListCards)
                {
                    if (card1.Rank == cards[0].Rank+1)
                    {
                        foreach (CardLogical card2 in packNew.ListCards)
                        {
                            if (card2 != card1 && card2.Rank == cards[0].Rank+1)
                            {
                                foreach (CardLogical card3 in packNew.ListCards)
                                {
                                    if (card3.Rank == cards[0].Rank+2)
                                    {
                                        foreach (CardLogical card4 in packNew.ListCards)
                                        {
                                            if (card3 != card4 && card4.Rank == cards[0].Rank+2)
                                            {
                                                List<CardLogical> t = new List<CardLogical>();
                                                t.AddRange(cards.ToArray());
                                                t.Add(card1);
                                                t.Add(card2);
                                                t.Add(card3);
                                                t.Add(card4);
                                                CardCombination temp = CardCombinationDoiThong.Create(t.ToArray());
                                                if (temp != null)
                                                {
                                                    CardCombination[] list = GetCombinationCoChua(packNew, temp);
                                                    if (list != null && list.Count() > 0) listKQ.AddRange(list);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (cards.GetType() == typeof(CardCombinationDoiThong))
            {
                //neu 3 doi thong thi thanh 4 doi, 4 thanh 5 doi
                foreach (CardLogical card1 in packNew.ListCards)
                {
                    if (card1.Rank == cards[0].Rank+1)
                    {
                        foreach (CardLogical card2 in packNew.ListCards)
                        {
                            if (card2 != card1 && card2.Rank == cards[0].Rank+1)
                            {
                                List<CardLogical> t = new List<CardLogical>();
                                t.AddRange(cards.ToArray());
                                t.Add(card1);
                                t.Add(card2);
                                CardCombination temp = CardCombinationDoiThong.Create(t.ToArray());
                                if (temp != null)
                                {
                                    CardCombination[] list = GetCombinationCoChua(packNew, temp);
                                    if (list != null && list.Count() > 0) listKQ.AddRange(list);
                                }
                            }
                        }
                    }
                }
            }
            else if (cards.GetType() == typeof(CardCombinationSamCo))
            {
                //mo rong thanh tu quy
                foreach (CardLogical card in packNew.ListCards)
                {
                    if (card.Rank == cards[cards.CardsCount - 1].Rank)
                    {
                        List<CardLogical> t = new List<CardLogical>();
                        t.AddRange(cards.ToArray());
                        t.Add(card);
                        CardCombination temp = CardCombinationTuQuy.Create(t.ToArray());
                        if (temp != null)
                        {
                            CardCombination[] list = GetCombinationCoChua(packNew, temp);
                            if (list != null && list.Count() > 0) listKQ.AddRange(list);
                        }
                        break;
                    }
                }
            }
            else if (cards.GetType() == typeof(CardCombinationSanh))
            {
                //them mot la
                foreach (CardLogical card in packNew.ListCards)
                {
                    if (card.Rank == cards[cards.CardsCount - 1].Rank+1)
                    {
                        List<CardLogical> t = new List<CardLogical>();
                        t.AddRange(cards.ToArray());
                        t.Add(card);
                        CardCombination temp = CardCombinationSanh.Create(t.ToArray());
                        if (temp != null)
                        {
                            CardCombination[] list = GetCombinationCoChua(packNew, temp);
                            if (list != null && list.Count() > 0) listKQ.AddRange(list);
                        }
                    }
                }
            }
            else if (cards.GetType() == typeof(CardCombinationTuQuy))
            {
                //ko mo rong dc
            }
            return listKQ.ToArray();
        }
        //public static CardCombination CreateCombination(params Card[] cards)
        //{
        //    List<CardLogical> list = new List<CardLogical>();
        //    foreach (Card c in cards)
        //    {
        //        list.Add((CardLogical)c);
        //    }
        //    return CreateCombination(list.ToArray());
        //}
        public virtual int CompareTo(CardCombination cards)
        {
            return 0;
        }
        public CardLogical[] ToArray()
        {
            return listCards.ToArray();
        }
        protected virtual bool Check(params CardLogical[] cards)
        {
            return false;
        }
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
