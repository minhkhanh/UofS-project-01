using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    class GameTestState: GameState
    {
        public GameTestState(GamePanel gpn, string bkgrPath)
            : base(gpn, bkgrPath)
        {
            gamePanel = gpn;
            stateId = GameStateID.StateTest;
        }

        public override void InitControls()
        {
            throw new NotImplementedException();
        }

        //Deck list;
        public override void EnterState()
        {
        //    BackIBmp = gamePanel.IGameGracphics.CreateBitmap(Program.AppPath + @"\Resources\Images\Misc\MenuBkgr.bmp", true);
        //    list = new Deck(new Rectangle(0, 0, gamePanel.IGameGracphics.ScreenWidth, gamePanel.IGameGracphics.ScreenHeight));
        //    Card.iBaseHeight = 83;
        //    Card.iBaseWidth = 66;
        //    Card.iMaxWidth = 22;
        //    Card lb = new Card(4);
        //    list.Add(lb);
        //    lb = new Card(7);
        //    list.Add(lb);
        //    lb = new Card(11);
        //    list.Add(lb);
        //    lb = new Card(27);
        //    list.Add(lb);
        }
    }
}
