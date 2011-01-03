using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class PlayerClientAI: PlayerClient
    {
        PackLogical packLogic;
        public PlayerClientAI(PlayerInfo playerinfo)
            : base(playerinfo)
        {

        }
        public override void OnServerPhatBai(PackLogical pack)
        {
            packLogic = pack;
        }
        public override void OnTurnToMe(BuocDi buoc)
        {
            base.OnTurnToMe(buoc);
            SendPlayerSkip();
        }
    }
}
