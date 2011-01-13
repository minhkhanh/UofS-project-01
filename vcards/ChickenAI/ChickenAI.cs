using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace ChickenAI
{
    public class ChickenAI: InterfaceAI
    {
        #region InterfaceAI Members

        public string NameAI
        {
            get { return "Chicken AI"; }
        }

        public void OnOtherJoinPlay(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnOtherLeavePlay(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnServerPhatBai(PackLogical pack)
        {
            throw new NotImplementedException();
        }

        public PackLogical OnTurnToMe(BuocDi buoc)
        {
            throw new NotImplementedException();
        }

        public void OnOnePlayerGo(PlayerInfo player, CardCombination cards)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
