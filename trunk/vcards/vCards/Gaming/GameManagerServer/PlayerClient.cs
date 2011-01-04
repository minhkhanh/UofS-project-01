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
        protected StatusPlayer status = StatusPlayer.None;
        public vCards.StatusPlayer Status
        {
            get 
            {
                mutexProtectVar.WaitOne();
                mutexProtectVar.ReleaseMutex();
                return status; 
            }
            set 
            {
                mutexProtectVar.WaitOne();                
                status = value;
                mutexProtectVar.ReleaseMutex();
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
