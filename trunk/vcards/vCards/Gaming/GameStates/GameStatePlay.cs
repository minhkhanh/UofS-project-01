using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    public class GameStatePlay: GameState
    {
        public GameStatePlay(GamePanel gp)
        {
            Gpnel = gp;
            ID = GameStateID.StatePlay;
        }

        public override void EnterState()
        {
            BackIBmp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\PlayBkgr.bmp", false);
        }

        public override void RenderState()
        {
            DrawBkgr();
        }

        public override void DrawState()
        {
            Gpnel.IGameGracphics.Flip();
        }
    }
}
