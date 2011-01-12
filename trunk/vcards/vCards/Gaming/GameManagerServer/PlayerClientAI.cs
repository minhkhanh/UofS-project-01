using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace vCards
{
    class PlayerClientAI: PlayerClient
    {                
        public PlayerClientAI(PlayerInfo playerinfo)
            : base(playerinfo)
        {

        }
        public override void OnServerPhatBai(PackLogical pack)
        {
            base.OnServerPhatBai(pack);
        }
        public override void OnTurnToMe(BuocDi buoc)
        {
            base.OnTurnToMe(buoc);
            if (buoc.Cards==null)
            {
                CardCombination card = CardCombination.CreateCombination(packLogic.ListCards[0]);
                base.SendBaiPlayerDanh(card);
            }
            else SendPlayerSkip();
        }
    }
}
