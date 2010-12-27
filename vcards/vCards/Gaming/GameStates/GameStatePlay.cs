using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    public class GameStatePlay: GameState
    {
        public GameStatePlay(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StatePlay;

            InitControls();
        }

        public override void InitControls()
        {
            
        }
    }
}
