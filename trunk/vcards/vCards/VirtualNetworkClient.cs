using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class VirtualNetworkClient
    {
        PlayerClient client;
        public static VirtualNetworkClient Create(PlayerInfo info, PlayerClient clientIns)
        {
            VirtualNetworkClient t = new VirtualNetworkClient();
            t.client = clientIns;
            if (!VirtualNetworkServer.ProcThemNguoiChoi(t, info))
            {
                t = null;
            }
            return t;
        }
        protected VirtualNetworkClient()
        {
            
        }
        public bool SendExitBanChoi()
        {
            if (client.Info.IdPlayer==0)
            {
                return false;
            }
            return VirtualNetworkServer.ProcExitBanChoi(client.Info.IdPlayer);
        }
        public void ProcPackLogicalToPlayer(PackLogical cards)
        {
            ////////////////////xu ly phia client
            client.OnServerPhatBai(cards);
        }
        public void ProcTurnToPlayer()
        {
            ///////////////////xu ly den luot di cua client
            client.OnTurnToMe();
        }
        public bool SendPlayerGo(CardCombination cards)
        {
            return VirtualNetworkServer.ProcPlayerGo(client.Info.IdPlayer, cards);
        }
    }
}
