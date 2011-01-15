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

        #endregion

        public GameStateMenu(GamePanel gpn, string bkgrPath)
            : base(gpn, bkgrPath)
        {
            stateId = GameStateID.StateMenu;
        }
        
        public override void InitControls()
        {         
            Rectangle origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 100) / 2, 100, 100, 30);

            btnPlay = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\PlayBtn_Bkgr.png"                
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\PlayBtn_Hover.png");

            origin.Y += origin.Height + 10;
            btnGameOpt = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\OptBtn_Bkgr.png"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\OptBtn_Hover.png");

            origin.Y += origin.Height + 10;
            btnExit = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\ExitBtn_Bkgr.png"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\ExitBtn_Hover.png");

            ctrlContainer.ManageControl(btnPlay);
            ctrlContainer.ManageControl(btnGameOpt);
            ctrlContainer.ManageControl(btnExit);

            btnPlay.MouseUp += new EventHandler<MouseEventArgs>(newGameImgBtn_MouseUp);
            btnExit.MouseUp += new EventHandler<MouseEventArgs>(btnExit_MouseUp);
            btnGameOpt.MouseUp += new EventHandler<MouseEventArgs>(btnGameOpt_MouseUp);
        }

        public void btnGameOpt_MouseUp(object o, EventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateOptions);
        }

        public void btnExit_MouseUp(object o, EventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateExiting);
        }

        public void newGameImgBtn_MouseUp(object o, MouseEventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateGameCustom);
        }
    }
}
