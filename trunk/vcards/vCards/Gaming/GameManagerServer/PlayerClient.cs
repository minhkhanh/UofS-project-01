using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;

namespace vCards
{
    enum StatusPlayer
    {
        None,   //ko cap nhat gi ca
        ServerPhatBai, //ve pack
        DenLuotToiDi
    }
    class PlayerClient
    {
        protected PackLogical packLogic;
        public vCards.PackLogical PackLogic
        {
            get 
            {
                mutexProtectVar.WaitOne();
                PackLogical temp = new PackLogical(packLogic);
                mutexProtectVar.ReleaseMutex();
                return temp; 
            }
        }
        protected Mutex mutexProtectVar;
        //PlayerSide mySide;

        public PlayerClient(PlayerInfo playerinfo)
        {
            info = playerinfo;
            mutexProtectVar = new Mutex();
        }
        ~PlayerClient()
        {
            mutexProtectVar.Close();
        }
        protected BuocDi buocDiTruoc;
        public vCards.BuocDi BuocDiTruoc
        {
            get { return buocDiTruoc; }
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
        public virtual void OnServerPhatBai(PackLogical pack)
        {
            mutexProtectVar.WaitOne();            
            packLogic = pack;
            mutexProtectVar.ReleaseMutex();
        }
        public virtual void OnTurnToMe(BuocDi buoc)
        {
            Trace.WriteLine("Den luot cua: " + info.Name);
            mutexProtectVar.WaitOne();            
            buocDiTruoc = buoc;
            mutexProtectVar.ReleaseMutex();
        }
        public virtual void OnTurnToOtherPlayer(PlayerInfo player) //id cua nguoi choi dc di
        {
            Trace.WriteLine("Den luot cua: " + player.Name + " phai doi thoi!");
        }
        public virtual bool SendBaiPlayerDanh(CardCombination cards)
        {
            if (client.SendPlayerGo(cards))
            {
                packLogic.PhepHieu(cards);                
                return true;
            }
            return false;
        }
        public virtual bool SendPlayerSkip()
        {
            if (client.SendPlayerSkip())
            {
                Trace.WriteLine("Toi: " + info.Name + " nhuong mot nuoc do!");
                return true;
            }
            return false;
        }
        public virtual void OnOnePlayerGo(CardCombination cards)
        {
            Trace.WriteLine("Co nguoi di " + cards.CardsCount + " la bai, lo ma chan di!");
        }
    }
}
