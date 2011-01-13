using System;
using System.Collections.Generic;
using System.Text;

namespace ShareLibrary
{
    public interface InterfaceAI
    {
        string NameAI { get; }
        void OnOtherJoinPlay(PlayerInfo pInfo);// ham nay chua can dung, thuat toan cao moi can dung
        void OnOtherLeavePlay(PlayerInfo pInfo);// ham nay chua can dung, thuat toan cao moi can dung
        void OnTurnToOtherPlayer(PlayerInfo player);// ham nay chua can dung, thuat toan cao moi can dung
        void OnServerPhatBai(PackLogical pack);
        CardCombination OnTurnToMe(BuocDi buoc); // tra ve null neu ko di ma bo luot
        void OnOtherPlayerGo(PlayerInfo player, CardCombination cards);
    }
}
