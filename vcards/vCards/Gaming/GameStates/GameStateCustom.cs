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
        List<ImageButton> listButton = new List<ImageButton>();
        //List<MyBmpTextControl> listTextbox = new List<MyBmpTextControl>();

        public GameStateCustom(GamePanel gp)
        {
            Gpnel = gp;
            ID = GameStateID.StateGameCustom;
        }

        public void InitButtons()
        {
            IBitmap ibmpBtnUp = Gpnel.IGameGracphics.CreateBitmap(Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Bkgr.bmp", true);

            imgBtnOK = new ImageButton(new Rectangle(50, 100, ibmpBtnUp.Width, ibmpBtnUp.Height), true, null
                , ibmpBtnUp, Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Hover.png", Gpnel.IGameGracphics);

            Gpnel.OwnerForm.MouseDown += new System.Windows.Forms.MouseEventHandler(imgBtnOK.OnMouseDown);
            Gpnel.OwnerForm.MouseUp += new System.Windows.Forms.MouseEventHandler(imgBtnOK.OnMouseUp);

            imgBtnOK.MouseDown += new EventHandler<System.Windows.Forms.MouseEventArgs>(OnBtnOK_Click);
        }

        ImageButton imgBtnOK;
        public override void EnterState()
        {
            BackIBmp = Gpnel.IGameGracphics.CreateBitmap(Program.AppPath + @"\Resources\Images\Misc\PlayBkgr.bmp", false);

            InitButtons();
        }

        public void OnBtnOK_Click(object o, MouseEventArgs e)
        {
            MessageBox.Show("Button OK in Custom state clicked!\n Event them thanh cong!");
            ((Form)Gpnel.OwnerForm).Close();
        }

        public override void RenderState()
        {
            Gpnel.IGameGracphics.DrawBitmap(0, 0, BackIBmp);
            imgBtnOK.DrawBackground(Gpnel.IGameGracphics);
        }
    }
}
