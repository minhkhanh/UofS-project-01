using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace vCards
{
    class BanChoi
    {
        public const int NUM_PLAYER = 4;
        List<PlayerServer> player = new List<PlayerServer>(NUM_PLAYER);
        Deck deck = null;
        List<int> turnQueye = null;
        //CardCombination buff = null;
        VongDi turnList = null;
        //int iPlayerCanGoIndex = -1;
        bool bDaYeuCauPlayerDi;
        bool bClientDaDi;
        protected BanChoi()
        {

        }
        public static BanChoi Create()
        {
            BanChoi t = new BanChoi();
            VirtualNetworkServer.banChoi = t;
            return t;
        }
        public bool AddPlayer(PlayerInfo info)
        {
            if (player.Count>=NUM_PLAYER)
            {
                return false;
            }
            player.Add(new PlayerServer(info));//, player.Count));
            info.IdPlayer = player.Count - 1;
            return true;
        }
        public bool RemovePlayer(int clientIDBanChoi)
        {
            if (clientIDBanChoi == 0)//key thi ko dc roi khoi
            {
                return false; 
            }
            player.RemoveAt(clientIDBanChoi);
            //////////////////////////////////////////////////////////////////////////
            // xu ly logic lien quan den bai, cai dat sau
            return true;
        }
        public bool NewGame()
        {
            if (player.Count < 2)
            {
                return false;
            }
            deck = new Deck();
            deck.DealAndSort(player.ToArray());
            InitTurn();
            PhatBaiChoCacClient();
            //iPlayerCanGoIndex = turnQueye.Peek();
            return true;
        }
        private void PhatBaiChoCacClient()
        {
            foreach (PlayerServer p in player)
            {
                p.OnPhatBaiChoClient();
            }
        }
        private void InitTurn()
        {
            turnQueye = new List<int>(NUM_PLAYER);
            int iMin = 0;
            for (int i=1; i < player.Count; ++i )
            {
                if (player[i].PackLogic[0].CompareValue(player[iMin].PackLogic[0])<0)
                {
                    iMin = i;
                }
            }
            turnQueye.Add(iMin++);
            //for (int i = 0; i < player.Count; ++i)
            //{
            //    turnQueye.Enqueue(iMin++);
            //    if (iMin==player.Count)
            //    {
            //        iMin = 0;
            //    }
            //}
        }
        public bool PlayerGo(int iIndex, CardCombination cards)
        {
            if (iIndex != turnQueye[0] || !player[iIndex].PackLogic.IsChua(cards))
            {
                return false;
            }
            if (turnList.GetLastBuocDi().Cards.CompareTo(cards) <= 0)
            {
                return false;
            }
            bClientDaDi = true;
            BuocDi buoc = new BuocDi();
            buoc.Player = player[iIndex];
            buoc.Cards = cards;
            turnList.ThemBuoiDi(buoc);
            iIndex = PlayerNext(iIndex);
            turnQueye.Add(turnQueye[0]);
            turnQueye[0] = iIndex;
            return true;
        }
        private int PlayerNext(int iIndex)
        {
            iIndex++;
            if (iIndex == player.Count)
            {
                iIndex = 0;
            }
            return iIndex;
        }
        private bool PlayerCantGo(int iIndex, CardCombination cards)
        {
            if (iIndex != turnQueye[0] || !player[iIndex].PackLogic.IsChua(cards))
            {
                return false;
            }
            if (turnList.GetLastBuocDi().Cards.CompareTo(cards)>0)
            {
                return true;
            }
            return false;
        }
        private void PlayerDontWantGo(int iIndex)
        {
            if (iIndex != turnQueye[0])
            {
                return;
            }
            iIndex = PlayerNext(iIndex);
            turnQueye[0] = iIndex;
        }
        private void YeuCauPlayerDi()
        {
            bClientDaDi = false;
            bDaYeuCauPlayerDi = true;
            player[turnQueye[0]].OnYeuCauClientDi(turnList.GetLastBuocDi());
        }
        public static void StartThread(BanChoi banChoi)
        {
            Thread gameThread = new Thread(new ThreadStart(banChoi.ThreadLoop));
            gameThread.Start();
        }
        private void ThreadLoop()
        {
            bDaYeuCauPlayerDi = false;
            while (!IsTheEnd())
            {
                if (!bDaYeuCauPlayerDi)
                {
                    YeuCauPlayerDi();
                }
                Thread.Sleep(200);
                if (!bClientDaDi)
                {
                    continue;
                }
                
            }
        } 
        private bool IsTheEnd()
        {
            int iSoNguoiHetBai = 0;
            for (int i = 0; i < player.Count; ++i )
            {
                if (player[i].PackLogic.ListCards.Count==0)
                {
                    ++iSoNguoiHetBai;
                }
            }
            if (iSoNguoiHetBai==(player.Count-1))
            {
                return true;
            }
            return false;
        }
    }
}
