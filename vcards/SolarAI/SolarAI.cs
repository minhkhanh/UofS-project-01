using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace SolarAI
{
    public class SolarAI: InterfaceAI
    {
        private PackLogical myPack;
        #region InterfaceAI Members

        public string NameAI
        {
            get { return "Solar AI"; }
        }

        public void OnOtherJoinPlay(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnOtherLeavePlay(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnTurnToOtherPlayer(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnServerPhatBai(PackLogical pack)
        {
            myPack = pack;
            myPack.SortByValue();
        }

        public CardCombination OnTurnToMe(BuocDi buoc)
        {
            System.Threading.Thread.Sleep(2000);
            CardCombination cards = null;
            if (buoc.LoaiBuocDi == LoaiBuocDi.BuocDau || buoc.LoaiBuocDi == LoaiBuocDi.BuocMoi)
            {
                CardCombination racMin = CardCombination.CreateCombination(myPack[0]);
                CardCombination[] listCC = CardCombination.GetCombinationCoChua(myPack, racMin);
                if (listCC != null)
                {
                    cards = listCC[0];
                    foreach (CardCombination cc in listCC)
                    {
                        if (cards.CardsCount < cc.CardsCount)
                        {
                            cards = cc;
                        }
                    }
                }
            }
            else
            {
                List<CardCombination> listCC = new List<CardCombination>();
                foreach (CardLogical card in myPack.ListCards)
                {
                    CardCombination racMin = CardCombination.CreateCombination(card);
                    CardCombination[] listTemp = CardCombination.GetCombinationCoChua(myPack, racMin);
                    if (listTemp != null)
                    {
                        listCC.AddRange(listTemp);
                    }
                }
                if (listCC.Count > 0)
                {
                    List<CardCombination> listTmp = new List<CardCombination>();
                    foreach (CardCombination cc in listCC)
                    {
                        if (cc.CompareTo(buoc.Cards) > 0)
                        {
                            listTmp.Add(cc);
                        }
                    }
                    if (listTmp.Count>0)
                    {
                        for (int i = 0; i < listTmp.Count - 1; ++i)
                        {
                            for (int j = i + 1; j < listTmp.Count; ++j)
                            {
                                if (listTmp[i].CompareTo(listTmp[j]) > 0)
                                {
                                    CardCombination tmp = listTmp[i];
                                    listTmp[i] = listTmp[j];
                                    listTmp[j] = tmp;
                                }
                            }
                        }
                        cards = listTmp[0];
                    }
                }
            }
            return cards;
        }

        public void OnOtherPlayerGo(PlayerInfo player, CardCombination cards)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
