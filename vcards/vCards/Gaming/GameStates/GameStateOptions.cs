using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class GameStateOptions: GameState
    {
        #region controls

        ImageButton btnBack;

        ImgCtrlScrollList imglistPlayerNum;
        ImgCtrlScrollList imglistGameSound;
        ImgCtrlScrollList imglistAILevel;

        #endregion

        #region images

        IImage iimgtextGameSound;
        IImage iimgtextAILevel;
        IImage iimgtextPlayerNum;

        #endregion

        #region default options

        GameOptions options = new GameOptions();

        #endregion

        public GameStateOptions(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateOptions;
        }

        public override void InitControls()
        {
            Rectangle rect;

            rect = new Rectangle(0, gamePanel.GameGraphics.ScreenHeight - 30, 100, 30);
            btnBack = new ImageButton(
                rect
                , Program.AppPath + @"\Resources\Images\Buttons\BtnBkgrBack.png"
                , gamePanel.GameGraphics
                );

            ctrlContainer.ManageControl(btnBack);

            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textGameSound.png", out iimgtextGameSound);
            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textAILevel.png", out iimgtextAILevel);
            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textPlayerNum.png", out iimgtextPlayerNum);

            Rectangle origin = new Rectangle(130, 150, 110, 30);
            imglistGameSound = new ImgCtrlScrollList(origin, MyResourceManager.fontH1);
            imglistGameSound.AddItem(0, "OFF");
            imglistGameSound.AddItem(1, "Song 1");
            imglistGameSound.AddItem(2, "Song 2");
            imglistGameSound.AddItem(3, "Song 3");

            ctrlContainer.ManageControl(imglistGameSound);

            origin.Y += origin.Height + 10;

            imglistAILevel = new ImgCtrlScrollList(origin, MyResourceManager.fontH1);
            //string[] listAIName = QuanLyAI.GetAINameList();
            //for (int i = 0; i < listAIName.Count(); ++i )
            //{
            //    imglistAILevel.AddItem(i, listAIName[i]);
            //}
            imglistAILevel.AddItem(1, "Easy");
            imglistAILevel.AddItem(2, "Hard");

            ctrlContainer.ManageControl(imglistAILevel);

            origin.Y += origin.Height + 10;
            imglistPlayerNum = new ImgCtrlScrollList(origin, MyResourceManager.fontH1);
            imglistPlayerNum.AddItem(1, "1");
            imglistPlayerNum.AddItem(2, "2");
            imglistPlayerNum.AddItem(3, "3");
            imglistPlayerNum.AddItem(4, "4");

            ctrlContainer.ManageControl(imglistPlayerNum);

            btnBack.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnBack_MouseUp);
            imglistGameSound.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(imglistGameSound_MouseUp);
        }

        public void imglistGameSound_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            int currSong = (int)imglistGameSound.GetCurrValue();
            if (currSong != MyResourceManager.iCurrSong)
                MyResourceManager.NextSong(currSong);
        }

        public void btnPlayerNumIncrease_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            options.IncreasePlayerNum();
        }

        public void btnPlayerNumDecrease_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            options.DecreasePlayerNum();
        }

        public void btnAIIncrease_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            options.IncreaseAILevel();
        }

        public void btnAIDecrease_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            options.DecreaseAILevel();
        }

        public void btnGameSound_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            options.Sound = !options.Sound;
        }

        public void btnBack_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            gamePanel.SwitchState(GameStateID.StateMenu);
        }

        public override void RenderState()
        {
            base.RenderState();

            ctrlContainer.Draw(gamePanel.GameGraphics);

            gamePanel.GameGraphics.DrawImageAlphaChannel(iimgtextGameSound, 0, 150);
            gamePanel.GameGraphics.DrawImageAlphaChannel(iimgtextAILevel, 0, 190);
            gamePanel.GameGraphics.DrawImageAlphaChannel(iimgtextPlayerNum, 0, 230);
        }

    }
}
