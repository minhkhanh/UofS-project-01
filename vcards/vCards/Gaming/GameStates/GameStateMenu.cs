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

        ImageButton newGameImgBtn;

        #endregion

        public GameStateMenu(GamePanel gpn, string bkgrPath)
            : base(gpn, bkgrPath)
        {
            stateId = GameStateID.StateMenu;
        }
        
        public override void InitControls()
        {         
            Rectangle origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 100) / 2, 50, 100, 30);

            newGameImgBtn = new ImageButton(origin, true
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Bkgr.bmp"                
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Hover.png");

            ManageImgControl(newGameImgBtn);

            newGameImgBtn.MouseDown += new EventHandler<MouseEventArgs>(newGameImgBtn_MouseDown);
            newGameImgBtn.MouseUp += new EventHandler<MouseEventArgs>(newGameImgBtn_MouseUp);
            newGameImgBtn.Click += new EventHandler<EventArgs>(newGameImgBtn_Click);
        }

        public void newGameImgBtn_Click(object o, EventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateGameCustom);
        }

        public void newGameImgBtn_MouseUp(object o, MouseEventArgs e)
        {
            
        }

        public void newGameImgBtn_MouseDown(object o, MouseEventArgs e)
        {

        }
    }
}
