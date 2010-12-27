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

        ImageButton okImgBtn;

        CardShape card01;

        #endregion

        public GameStateCustom(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateGameCustom;

            InitControls();
        }
        
        public override void InitControls()
        {
            okImgBtn = new ImageButton(new Rectangle(50, 100, 100, 50), true
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Bkgr.bmp"                
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Hover.png"
                );
            ManageImgControl(okImgBtn);
            okImgBtn.MouseDown += new EventHandler<MouseEventArgs>(okImgBtn_MouseDown);
            okImgBtn.MouseUp += new EventHandler<MouseEventArgs>(okImgBtn_MouseUp);
            okImgBtn.Click += new EventHandler<EventArgs>(okImgBtn_Click);


            card01 = new CardShape(new Rectangle(50, 200, 52, 66), true
                , Program.AppPath + @"\Resources\Images\Cards\00_75.png"
                , gamePanel.GameGraphics
                , new CardValue(CardRank.Ace, CardSuit.Spades)
                );
            ManageImgControl(card01);
            card01.MouseMove += new EventHandler<MouseEventArgs>(card01_MouseMove);
        }

        public void card01_MouseMove(object o, MouseEventArgs e)
        {
            card01.MoveTo(new Point(e.X, e.Y));
        }

        public void okImgBtn_Click(object o, EventArgs e)
        {

        }

        public void okImgBtn_MouseDown(object o, MouseEventArgs e)
        {
        }

        public void okImgBtn_MouseUp(object o, MouseEventArgs e)
        {         
        }
    }
}
