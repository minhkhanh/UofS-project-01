using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using ShareLibrary;

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
        public PackLogical PackLogic
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

        protected PlayerClient(PlayerInfo playerinfo)
        {
            info = playerinfo;
            mutexProtectVar = new Mutex();
        }
        ~PlayerClient()
        {
            mutexProtectVar.Close();
        }
        protected BuocDi buocDiTruoc;
        public BuocDi BuocDiTruoc
        {
            get { return buocDiTruoc; }
        }
        protected VirtualNetworkClient client;
        protected PlayerInfo info;
        public PlayerInfo Info
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
        public virtual void OnOtherJoinPlay(PlayerInfo pInfo) //bao voi client la da co 1 nguoi vao ban choi
        {

        }
        public virtual void OnOtherLeavePlay(PlayerInfo pInfo) //bao voi client la da co 1 nguoi roi ban choi
        {

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
        public virtual void OnOnePlayerGo(PlayerInfo player, CardCombination cards) //co nguoi danh bai ra co the la minh
        {
            Trace.WriteLine("Co nguoi di " + cards.CardsCount + " la bai, lo ma chan di!");
        }
    }
}
