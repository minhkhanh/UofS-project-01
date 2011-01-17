using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

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
        public void ProcTurnToPlayer(BuocDi buoc)
        {
            ///////////////////xu ly den luot di cua client
            client.OnTurnToMe(buoc);
        }
        public void ProcTurnToOtherPlayer(PlayerInfo player) //id cua nguoi choi dc di
        {
            client.OnTurnToOtherPlayer(player);
        }
        public bool SendPlayerGo(CardCombination cards)
        {
            return VirtualNetworkServer.ProcPlayerGo(client.Info.IdPlayer, cards);
        }
        public bool SendPlayerSkip()
        {
            return VirtualNetworkServer.ProcPlayerSkip(client.Info.IdPlayer);
        }
        public void ProcOnePlayerGo(PlayerInfo player, CardCombination cards)
        {
            client.OnOnePlayerGo(player, cards);
        }

        public void ProcMessEndGame()
        {
            client.OnEndGame();
        }
    }
}
