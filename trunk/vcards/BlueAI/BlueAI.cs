using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace BlueAI
{
    public class BlueAI: InterfaceAI
    {
        private PackLogical myPack;
        #region InterfaceAI Members

        public string NameAI
        {
            get { return "Blue AI"; }
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
                foreach (CardCombination cc in listCC)
                {
                    if (cc.CompareTo(buoc.Cards) > 0)
                    {
                        cards = cc;
                        break;
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
