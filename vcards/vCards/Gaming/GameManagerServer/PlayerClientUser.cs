using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    class PlayerClientUser: PlayerClient
    {
        public PlayerClientUser(PlayerInfo playerinfo)
            : base(playerinfo)
        {

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
        public override void OnServerPhatBai(PackLogical packLogic)
        {
            base.OnServerPhatBai(packLogic);
            status = StatusPlayer.ServerPhatBai;          
        }
        public override void OnTurnToMe(BuocDi buoc)
        {
            base.OnTurnToMe(buoc);
            status = StatusPlayer.DenLuotToiDi;
            strStatus = "Den luot cua toi danh bai!";
        }
        public override bool SendBaiPlayerDanh(CardCombination cards)
        {
            if (base.SendBaiPlayerDanh(cards))
            {
                status = StatusPlayer.None;
                return true;
            }
            return false;
        }
        public override bool SendPlayerSkip()
        {
            if (base.SendPlayerSkip())
            {
                status = StatusPlayer.None;
                return true;
            }
            return false;
        }
        private bool bDaVeCardDanhRa = false;
        private CardCombination cardsOnePlayerGo = null;
        public CardCombination CardsOnePlayerGo
        {
            get 
            {
                if (cardsOnePlayerGo==null || bDaVeCardDanhRa)
                {
                    return null;
                }
                mutexProtectVar.WaitOne();
                CardCombination cards = cardsOnePlayerGo;
                bDaVeCardDanhRa = true;
                mutexProtectVar.ReleaseMutex();
                return cards; 
            }
        }
        private string strStatus = "";
        public string StatusString
        {
            get { return strStatus; }
            //set { strStatus = value; }
        }
        public override void OnOnePlayerGo(PlayerInfo player, CardCombination cards)
        {
            base.OnOnePlayerGo(player, cards);
            mutexProtectVar.WaitOne();            
            bDaVeCardDanhRa = false;
            cardsOnePlayerGo = cards;
            mutexProtectVar.ReleaseMutex();
        }
        public override void OnTurnToOtherPlayer(PlayerInfo player)
        {
            base.OnTurnToOtherPlayer(player);
            strStatus = "Den luot cua " + player.Name + " danh bai!";
        }
        private bool bEndGame = false;
        public bool IsEndGame
        {
            get { return bEndGame; }
            set { bEndGame = value; }
        }
        public override void OnEndGame()
        {
            base.OnEndGame();
            bEndGame = true;
        }
    }
}
