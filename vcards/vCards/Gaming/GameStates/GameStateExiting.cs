using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class GameStateExiting: GameState
    {
        #region all controls

        ImageButton btnStatus;

        #endregion
        public GameStateExiting(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateExiting;
        }

        public override void InitControls()
        {
            Rectangle regn = new Rectangle(0, gamePanel.GameGraphics.ScreenHeight - 30, 100, 30);

            btnStatus = new ImageButton(regn
                , Program.AppPath + @"\Resources\Images\Buttons\ExitStatus.png"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\ExitStatus.png"
                );

            ctrlContainer.ManageControl(btnStatus);

            btnStatus.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnStatus_MouseUp);
        }

        public void btnStatus_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            gamePanel.Playing = false;
        }
    }
}
