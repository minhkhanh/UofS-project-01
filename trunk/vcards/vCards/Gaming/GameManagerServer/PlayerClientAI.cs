using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    class PlayerClientAI: PlayerClient
    {
        InterfaceAI objAI = null;
        public PlayerClientAI(PlayerInfo playerinfo, string strNameAI)
            : base(playerinfo)
        {
            objAI = QuanLyAI.CreateObjAIByName(strNameAI);
            if (objAI==null) // ten dua vao ko co thi dung cai dau tien
            {
                objAI = QuanLyAI.CreateObjAIByIndex(0);
            }
        }
        public override void OnServerPhatBai(PackLogical pack)
        {
            base.OnServerPhatBai(pack);
            objAI.OnServerPhatBai(pack);
        }
        public override void OnTurnToMe(BuocDi buoc)
        {
            base.OnTurnToMe(buoc);
            //if (buoc.Cards==null)//code dung test den luot cua minh ma la luot moi thi di con rac
            //{
            //    CardCombination card = CardCombination.CreateCombination(packLogic.ListCards[0]);
            //    base.SendBaiPlayerDanh(card);
            //}
            //else SendPlayerSkip();
            CardCombination cards = objAI.OnTurnToMe(buoc);
            if (cards == null)
            {
                SendPlayerSkip();
            } 
            else
            {
                SendBaiPlayerDanh(cards);
            }
        }
        public override void OnOnePlayerGo(PlayerInfo player, CardCombination cards)
        {
            base.OnOnePlayerGo(player, cards);
            if (player.IdPlayer!=info.IdPlayer)
            {
                objAI.OnOtherPlayerGo(player, cards);
            }
        }
    }
}
