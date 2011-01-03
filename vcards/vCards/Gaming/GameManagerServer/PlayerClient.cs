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
        public virtual void OnTurnToMe()
        {
            Trace.WriteLine("Den luot cua: " + info.Name);
        }
    }
}
