using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    public class PlayerServer
    {
        //int iIndex;
        PackLogical packLogic;
        public PackLogical PackLogic
        {
            get { return packLogic; }
            set { packLogic = value; }
        }
        PlayerInfo info;
        public PlayerInfo Info
        {
            get { return info; }
            set { info = value; }
        }
        public PlayerServer(PlayerInfo inf)//, int i)
        {
            info = inf;
            //iIndex = i;
        }
        public void InitCard()//(params CardLogical[] cards)
        {
            //if (cards.Count() < PackLogical.CARD_NUM) return;
            packLogic = new PackLogical();
        }
        public void AddCard(params CardLogical[] cards)
        {
            packLogic.AddCards(cards);
        }
        public void SortCardsByValue()
        {
            packLogic.SortByValue();
        }
        public void OnPhatBaiChoClient()
        {
            VirtualNetworkServer.SendPackLogicalToPlayer(info.IdPlayer, packLogic);
        }
        public void OnYeuCauClientDi(BuocDi buoc)
        {
            VirtualNetworkServer.SendTurnToPlayer(info.IdPlayer, buoc);
        }
        public void OnTurnToOtherPlayer(PlayerInfo player) //id cua nguoi choi dc di
        {
            VirtualNetworkServer.SendTurnToOtherPlayer(info.IdPlayer, player);
        }
        public void SendOnePlayerGo(CardCombination cards)
        {
            VirtualNetworkServer.SendOnePlayerGo(info.IdPlayer, info, cards);
        }
    }
}
