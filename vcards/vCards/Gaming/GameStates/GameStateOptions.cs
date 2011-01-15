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

        ToggleImgBtn btnGameSound;
        ImageButton btnBack;

        ImageButton btnAIDecrease;
        ImageButton btnAIIncrease;
        //ImageButton btnPlayerNumDecrease;
        //ImageButton btnPlayerNumIncrease;

        ImgCtrlScrollList imglistPlayerNum;
        ImgCtrlScrollList imglistGameSound;

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
            btnBack = new ImageButton(rect
                , Program.AppPath + @"\Resources\Images\Buttons\BackBtn_Bgkr.png"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\BackBtn_Bgkr.png"
                );

            ctrlContainer.ManageControl(btnBack);

            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textGameSound.png", out iimgtextGameSound);
            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textAILevel.png", out iimgtextAILevel);
            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textPlayerNum.png", out iimgtextPlayerNum);

            Rectangle origin = new Rectangle(130, 150, 110, 30);
            //btnGameSound = new ToggleImgBtn(origin
            //    , Program.AppPath + @"\Resources\Images\Buttons\VolBtn_Bkgr.png"
            //    , gamePanel.GameGraphics
            //    , Program.AppPath + @"\Resources\Images\Buttons\VolBtn_Hover.png"
            //    , options.Sound
            //    );
            imglistGameSound = new ImgCtrlScrollList(origin);
            imglistGameSound.AddItem(0, "OFF");
            imglistGameSound.AddItem(1, "Song 1");
            imglistGameSound.AddItem(2, "Song 2");
            imglistGameSound.AddItem(3, "Song 3");

            ctrlContainer.ManageControl(imglistGameSound);

            //origin.X = 0;
            origin.Y += origin.Height + 10;
            origin.Width = 30;
            btnAIDecrease = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\LeftArrow_Bkgr.png"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\LeftArrow_Hover.png"
                );

            ctrlContainer.ManageControl(btnAIDecrease);

            origin.X += 80;
            btnAIIncrease = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\RightArrow_Bkgr.png"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\RightArrow_Hover.png"
                );

            //SoundEff

            ctrlContainer.ManageControl(btnAIIncrease);

            //origin.X -= 80;
            //origin.Y += origin.Height + 10;
            //btnPlayerNumDecrease = new ImageButton(origin
            //    , Program.AppPath + @"\Resources\Images\Buttons\LeftArrow_Bkgr.png"
            //    , gamePanel.GameGraphics
            //    , Program.AppPath + @"\Resources\Images\Buttons\LeftArrow_Hover.png"
            //    );

            //ctrlContainer.ManageControl(btnPlayerNumDecrease);

            //origin.X += 50;
            //btnPlayerNumIncrease = new ImageButton(origin
            //    , Program.AppPath + @"\Resources\Images\Buttons\RightArrow_Bkgr.png"
            //    , gamePanel.GameGraphics
            //    , Program.AppPath + @"\Resources\Images\Buttons\RightArrow_Hover.png"
            //    );

            //ctrlContainer.ManageControl(btnPlayerNumIncrease); 

            origin.X -= 80;
            origin.Y += origin.Height + 10;
            origin.Width = 110;
            origin.Height = 30;
            imglistPlayerNum = new ImgCtrlScrollList(origin);
            imglistPlayerNum.AddItem(1, "1");
            imglistPlayerNum.AddItem(2, "2");
            imglistPlayerNum.AddItem(3, "3");
            imglistPlayerNum.AddItem(4, "4");

            ctrlContainer.ManageControl(imglistPlayerNum);

            //btnGameSound.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnGameSound_MouseUp);
            btnBack.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnBack_MouseUp);
            btnAIDecrease.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnAIDecrease_MouseUp);
            btnAIIncrease.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnAIIncrease_MouseUp);
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

            gamePanel.GameGraphics.DrawImageAlphaChannel(iimgtextGameSound, 0, 150);
            gamePanel.GameGraphics.DrawImageAlphaChannel(iimgtextAILevel, 0, 190);
            gamePanel.GameGraphics.DrawImageAlphaChannel(iimgtextPlayerNum, 0, 230);

            gamePanel.GameGraphics.DrawText(
                new Rectangle(btnAIDecrease.Width + btnAIDecrease.X, btnAIDecrease.Y, btnAIIncrease.X - btnAIDecrease.Width - btnAIDecrease.X, btnAIIncrease.Height)
                , options.AILevelName()
                , Color.GreenYellow
                , MyResourceManager.fontH1
                , FontDrawOptions.DrawTextCenter | FontDrawOptions.DrawTextMiddle
                );

            //gamePanel.GameGraphics.DrawText(
            //    new Rectangle(btnPlayerNumDecrease.Width + btnPlayerNumDecrease.X, btnPlayerNumDecrease.Y, btnPlayerNumIncrease.X - btnPlayerNumDecrease.Width - btnPlayerNumDecrease.X, btnPlayerNumIncrease.Height)
            //    , options.PlayerNumber.ToString()
            //    , Color.GreenYellow
            //    , MyResourceManager.fontH1
            //    , FontDrawOptions.DrawTextCenter | FontDrawOptions.DrawTextMiddle
            //    );
        }

    }
}
