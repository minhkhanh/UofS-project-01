﻿using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using ShareLibrary;

namespace SolarAI
{
    public class SolarAI: InterfaceAI
    {
        #region InterfaceAI Members

        public string NameAI
        {
            get { return "Solar AI"; }
        }

        public void OnOtherJoinPlay(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnOtherLeavePlay(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnTurnToOtherPlayer(PlayerInfo pInfo)
        {
            throw new NotImplementedException();
        }

        public void OnServerPhatBai(PackLogical pack)
        {
            throw new NotImplementedException();
        }

        public CardCombination OnTurnToMe(BuocDi buoc)
        {
            throw new NotImplementedException();
        }

        public void OnOtherPlayerGo(PlayerInfo player, CardCombination cards)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}