using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace vCards
{
    public class GameStateHighScore: GameState
    {
        ImageButton btnBack;

        public GameStateHighScore(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateHighScore;
        }

        public override void InitControls()
        {
            btnBack = new ImageButton(
                new System.Drawing.Rectangle(0, gamePanel.GameGraphics.ScreenHeight - 30, 100, 30)
                , MyResourceManager.iimgBtnBack
                );

            ctrlContainer.ManageControl(btnBack);
            btnBack.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnBack_MouseUp);
        }

        public void btnBack_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            GoBackState();
        }
    }
}
