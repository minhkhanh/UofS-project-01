using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace vCards
{
    public class GameStateCustom: GameState
    {
        #region  declare all image controls

        Pack pack01;
        Pack pack02;
        Deck deck01 = new Deck();
        //ImageButton

        #endregion

        public GameStateCustom(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateGameCustom;
        }
        
        public override void InitControls()
        {
            pack01 = new Pack(PlayerSide.Bottom, gamePanel.GameGraphics);
            pack02 = new Pack(PlayerSide.Left, gamePanel.GameGraphics);

            pack01.Enabled = true;
            pack02.Enabled = false;

            //deck01.Deal(pack01, pack02);

            ctrlContainer.AddControl(pack01);
            ctrlContainer.AddControl(pack02);

            pack01.SortByValue();

            pack01.Rearrange(gamePanel.GameGraphics);
            pack02.Rearrange(gamePanel.GameGraphics);
        }

        public override void RenderState()
        {
            base.RenderState();
        }
    }
}
