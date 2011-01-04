using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class PlayerClientUser: PlayerClient
    {
        Pack myPack = null;
        public vCards.Pack MyPack
        {
            get { return myPack; }
            //set { myPack = value; }
        }
        IGraphics gp;
        ImgCtrlContainer ctrlList;
        GameState gameState;
        public PlayerClientUser(PlayerInfo playerinfo, IGraphics g, ImgCtrlContainer controls, GameState state)
            : base(playerinfo)
        {
            gp = g;
            ctrlList = controls;
            gameState = state;
        }
        public void Rearrange(IGraphics g)
        {
            if (myPack != null) myPack.Rearrange(g);
        }
        public override void OnServerPhatBai(PackLogical packLogic)
        {
            base.OnServerPhatBai(packLogic);
            myPack = new Pack(PlayerSide.Bottom, gp);
            myPack.Enabled = true;
            foreach (CardLogical card in packLogic.ListCards)
            {
                myPack.AddControl(new Card(card, PlayerSide.Bottom));
            }            
            ctrlList.AddControl(myPack);            
        }
        public override void OnTurnToMe(BuocDi buoc)
        {
            base.OnTurnToMe(buoc);
            ((GameStateCustom)gameState).PaintTurnToPlayer();            
        }
    }
}
