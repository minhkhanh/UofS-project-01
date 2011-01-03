using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace vCards
{
    class PlayerClient
    {
        
        //PlayerSide mySide;

        public PlayerClient(PlayerInfo playerinfo)
        {
            info = playerinfo;
        }
        protected BuocDi buocDiTruoc;
        public vCards.BuocDi BuocDiTruoc
        {
            get { return buocDiTruoc; }
            //set { buocDiTruoc = value; }
        }
        protected VirtualNetworkClient client;
        protected PlayerInfo info;
        public vCards.PlayerInfo Info
        {
            get { return info; }
            set { info = value; }
        }
        public bool JoinPlay()
        {
            client = VirtualNetworkClient.Create(info, this);
            if (client != null) return true;
            return false;
        }
        public virtual void OnServerPhatBai(PackLogical packLogic)
        {

        }
        public virtual void OnTurnToMe(BuocDi buoc)
        {
            Trace.WriteLine("Den luot cua: " + info.Name);
            buocDiTruoc = buoc;
        }
        public bool SendBaiPlayerDanh(CardCombination cards)
        {
            return client.SendPlayerGo(cards);
        }
        public bool SendPlayerSkip()
        {
            return client.SendPlayerSkip();
        }
    }
}
