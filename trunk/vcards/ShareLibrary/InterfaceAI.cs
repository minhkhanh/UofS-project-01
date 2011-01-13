using System;
using System.Collections.Generic;
using System.Text;

namespace ShareLibrary
{
    public interface InterfaceAI
    {
        string Description { get; set; }
        void OnOtherJoinPlay(PlayerInfo pInfo);
        void OnOtherLeavePlay(PlayerInfo pInfo);
        void OnServerPhatBai(PackLogical pack);
        PackLogical OnTurnToMe(BuocDi buoc); // tra ve null neu ko di ma bo luot
    }
}
