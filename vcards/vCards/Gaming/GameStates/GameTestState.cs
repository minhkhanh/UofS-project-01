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
            StateID = GameStateID.StateMenu;
        }
        TapCacLaBai list;
        public override void EnterState()
        {
            BackIBmp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\MenuBkgr.bmp", true);
            list = new TapCacLaBai(new Rectangle(0, 0, Gpnel.IGameGracphics.ScreenWidth, Gpnel.IGameGracphics.ScreenHeight));
            LaBai.iBaseHeight = 83;
            LaBai.iBaseWidth = 66;
            LaBai.iMaxWidth = 22;
            LaBai lb = new LaBai(4);
            list.Add(lb);
            lb = new LaBai(7);
            list.Add(lb);
            lb = new LaBai(11);
            list.Add(lb);
            lb = new LaBai(27);
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
