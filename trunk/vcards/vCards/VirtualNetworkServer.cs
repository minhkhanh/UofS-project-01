using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class VirtualNetworkServer
    {
        static List<VirtualNetworkClient> listClient = new List<VirtualNetworkClient>();
        public static BanChoi banChoi;
        public static bool ProcThemNguoiChoi(VirtualNetworkClient clientID, PlayerInfo info)
        {
            info.IdPlayer = listClient.Count;
            if (!banChoi.AddPlayer(info))
            {
                return false;
            }            
            listClient.Add(clientID);
            return true;
        }
        public static bool ProcExitBanChoi(int clientIDBanChoi)
        {
            if (banChoi.RemovePlayer(clientIDBanChoi))
            {
                listClient.RemoveAt(clientIDBanChoi);
                return true;
            }
            return false;
        }
        public static void SendPackLogicalToPlayer(int clientId, PackLogical cards)
        {
            listClient[clientId].ProcPackLogicalToPlayer(cards);
        }
        public static void SendTurnToPlayer(int clientID, BuocDi buoc)
        {
            listClient[clientID].ProcTurnToPlayer(buoc);
        }
        public static bool ProcPlayerGo(int clientID, CardCombination cards)
        {
            return banChoi.OnPlayerGo(clientID, cards);
        }
        public static void SendHavePlayerGo()
        {

        }
        public static bool ProcPlayerSkip(int clientID)
        {
            return banChoi.OnPlayerSkip(clientID);
        }
    }
}
