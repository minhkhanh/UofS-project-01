using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ChickenAI
{
    public class ChickenAI: InterfaceAI
    {
        private PackLogical myPack;
        #region InterfaceAI Members

        public string NameAI
        {
            get { return "Chicken AI"; }
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
        }
        //List<CardCombination> listNhomBai;
        //private void 
        public CardCombination OnTurnToMe(BuocDi buoc)
        {
            CardCombination cards = null;
            if (buoc.LoaiBuocDi == LoaiBuocDi.BuocDau)
            {
            }
            else if (buoc.LoaiBuocDi == LoaiBuocDi.BuocMoi)
            {
            }
            else
            {

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
