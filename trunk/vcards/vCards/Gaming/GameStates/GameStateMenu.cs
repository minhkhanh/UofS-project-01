using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Threading;

namespace vCards
{
    public class GameStateMenu : GameState
    {
        #region declare all image controls

        ImageButton btnPlay;
        ImageButton btnGameOpt;
        ImageButton btnExit;
        ImageButton btnHighScore;

        #endregion

        public GameStateMenu(GamePanel gpn, string bkgrPath)
            : base(gpn, bkgrPath)
        {
            stateId = GameStateID.StateMenu;
        }
        
        public override void InitControls()
        {         
            Rectangle origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 100) / 2, 150, 100, 30);

            btnPlay = new ImageButton(
                origin
                , Program.AppPath + @"\Resources\Images\Buttons\BtnBkgrPlay.png"
                , gamePanel.GameGraphics
                );

            origin.Y += origin.Height + 5;
            btnGameOpt = new ImageButton(
                origin
                , Program.AppPath + @"\Resources\Images\Buttons\BtnBkgrGameOpt.png"
                , gamePanel.GameGraphics
                );

            origin.Y += origin.Height + 5;
            btnHighScore = new ImageButton(
                origin
                , Program.AppPath + @"\Resources\Images\Buttons\BtnBkgrHighScore.png"
                , gamePanel.GameGraphics
                );

            origin.Y += origin.Height + 5;
            btnExit = new ImageButton(
                origin
                , Program.AppPath + @"\Resources\Images\Buttons\BtnBkgrExit.png"
                , gamePanel.GameGraphics
                );

            ctrlContainer.ManageControl(btnPlay);
            ctrlContainer.ManageControl(btnGameOpt);
            ctrlContainer.ManageControl(btnExit);
            ctrlContainer.ManageControl(btnHighScore);

            btnPlay.MouseUp += new EventHandler<MouseEventArgs>(newGameImgBtn_MouseUp);
            btnExit.MouseUp += new EventHandler<MouseEventArgs>(btnExit_MouseUp);
            btnGameOpt.MouseUp += new EventHandler<MouseEventArgs>(btnGameOpt_MouseUp);
            btnHighScore.MouseUp += new EventHandler<MouseEventArgs>(btnHighScore_MouseUp);
        }

        public void btnHighScore_MouseUp(object o, EventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateHighScore);
        }

        public void btnGameOpt_MouseUp(object o, EventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateOptions);
        }

        public void btnExit_MouseUp(object o, EventArgs e)
        {
            if (MessageBox.Show("Are you sure?", "vCards", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) == DialogResult.No)
                return;

            gamePanel.SwitchState(GameStateID.StateExiting);
        }

        public void newGameImgBtn_MouseUp(object o, MouseEventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateGameCustom);
        }
    }
}
