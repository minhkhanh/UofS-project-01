using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    class GameTestState: GameState
    {
        public GameTestState(GamePanel gpn)
        {
            Gpnel = gpn;
            StateID = GameStateID.StateTest;
        }

        Deck list;
        public override void EnterState()
        {
            BackIBmp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\MenuBkgr.bmp", true);
            list = new Deck(new Rectangle(0, 0, Gpnel.IGameGracphics.ScreenWidth, Gpnel.IGameGracphics.ScreenHeight));
            Card.iBaseHeight = 83;
            Card.iBaseWidth = 66;
            Card.iMaxWidth = 22;
            Card lb = new Card(4);
            list.Add(lb);
            lb = new Card(7);
            list.Add(lb);
            lb = new Card(11);
            list.Add(lb);
            lb = new Card(27);
            list.Add(lb);
        }

        public override void UpdateState()
        {
            //throw new NotImplementedException();
        }

        public override void RenderState()
        {
            //Gpnel.IGameGracphics.DrawBitmap(new Rectangle(0, 0, Gpnel.IGameGracphics.ScreenWidth, Gpnel.IGameGracphics.ScreenHeight), BackIBmp);
            list.UpdatePos();
            list.Draw(Gpnel.IGameGracphics);

            //Gpnel.IGameGracphics.DrawImageAlphaChannel(iimgCover, new Rectangle(0, 0, 100, 100), new Rectangle(0, 0, 100, 100));
        }

        public override void DrawState()
        {
            Gpnel.IGameGracphics.Flip();
        }

        public override void ExitState()
        {
            throw new NotImplementedException();
        }

    }
}
