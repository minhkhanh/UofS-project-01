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

        ImageButton btnCancel;
        ImageButton btnOK;

        ImgCtrlScrollList scrllistGameSound;
        ImgCtrlScrollList scrllistAILevel01;
        ImgCtrlScrollList scrllistAILevel02;
        ImgCtrlScrollList scrllistAILevel03;

        #endregion

        #region images

        //IImage iimgtextGameSound;
        //IImage iimgtextAILevel;
        //IImage iimgtextPlayerNum;

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
            //gamePanel
            Rectangle rect;

            rect = new Rectangle(0, gamePanel.GameGraphics.ScreenHeight - 30, 100, 30);
            btnCancel = new ImageButton(
                rect
                , MyResourceManager.iimgBtnCancel
                );            

            rect.X = gamePanel.GameGraphics.ScreenWidth - 100;
            btnOK = new ImageButton(
                rect
                , MyResourceManager.iimgBtnOK
                );

            //gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textGameSound.png", out iimgtextGameSound);
            //gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textAILevel.png", out iimgtextAILevel);
            //gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\TextImages\textPlayerNum.png", out iimgtextPlayerNum);

            Rectangle origin = new Rectangle(10, 150, 110, 30);
            origin.X += 120;
            scrllistGameSound = new ImgCtrlScrollList(origin);
            scrllistGameSound.AddItem(0, "OFF");
            scrllistGameSound.AddItem(1, "Song 1");
            scrllistGameSound.AddItem(2, "Song 2");
            scrllistGameSound.AddItem(3, "Song 3");

            origin.Y += origin.Height + 5;
            origin.X = 10;
            origin.X += 120;
            scrllistAILevel01 = new ImgCtrlScrollList(origin);
            string[] listAIName = QuanLyAI.GetAINameList();
            scrllistAILevel01.AddItem(-1, "N/A");
            for (int i = 0; i < listAIName.Count(); ++i)
            {
                scrllistAILevel01.AddItem(i, listAIName[i]);
            }
            if (listAIName.Count()>0) scrllistAILevel01.CurrentIndex = 1;

            origin.Y += origin.Height + 5;
            origin.X = 10;
            origin.X += 120;
            scrllistAILevel02 = new ImgCtrlScrollList(origin);
            scrllistAILevel02.AddItem(-1, "N/A");
            for (int i = 0; i < listAIName.Count(); ++i)
            {
                scrllistAILevel02.AddItem(i, listAIName[i]);
            }

            origin.Y += origin.Height + 5;
            origin.X = 10;
            origin.X += 120;
            scrllistAILevel03 = new ImgCtrlScrollList(origin);
            scrllistAILevel03.AddItem(-1, "N/A");
            for (int i = 0; i < listAIName.Count(); ++i)
            {
                scrllistAILevel03.AddItem(i, listAIName[i]);
            }

            btnCancel.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnCancel_MouseUp);
            btnOK.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnOK_MouseUp);
            scrllistGameSound.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(imglistGameSound_MouseUp);

            ctrlContainer.ManageControl(btnOK);
            ctrlContainer.ManageControl(scrllistGameSound);
            ctrlContainer.ManageControl(scrllistAILevel01);
            ctrlContainer.ManageControl(scrllistAILevel02);
            ctrlContainer.ManageControl(scrllistAILevel03);
            ctrlContainer.ManageControl(btnCancel);
        }

        public void btnOK_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            // do changes here
            options.ArrNameAI.Clear();
            if (scrllistAILevel01.CurrentIndex > 0)
            {
                options.ArrNameAI.Add(scrllistAILevel01.CurrentItemText);
            }
            if (scrllistAILevel02.CurrentIndex > 0)
            {
                options.ArrNameAI.Add(scrllistAILevel02.CurrentItemText);
            }
            if (scrllistAILevel03.CurrentIndex > 0)
            {
                options.ArrNameAI.Add(scrllistAILevel03.CurrentItemText);
            }

            gamePanel.Option = options;

            GoBackState();
        }

        public void imglistGameSound_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            int currSong = (int)scrllistGameSound.CurrentItemValue;
            if (currSong != MyResourceManager.iCurrSong)
                MyResourceManager.NextSong(currSong);
        }

        public void btnCancel_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            GoBackState();
        }

        public override void RenderState()
        {
            base.RenderState();

            ctrlContainer.Draw(gamePanel.GameGraphics);

            Rectangle origin = new Rectangle(10, 150, 110, 30);
            gamePanel.GameGraphics.DrawText(origin, "Background songs: ", MyResourceManager.colorT1, MyResourceManager.fontH1, FontDrawOptions.DrawTextLeft | FontDrawOptions.DrawTextMiddle);
            origin.Y += origin.Height + 5;
            gamePanel.GameGraphics.DrawText(origin, "AI 1 level: ", MyResourceManager.colorT1, MyResourceManager.fontH1, FontDrawOptions.DrawTextLeft | FontDrawOptions.DrawTextMiddle);
            origin.Y += origin.Height + 5;
            gamePanel.GameGraphics.DrawText(origin, "AI 2 level: ", MyResourceManager.colorT1, MyResourceManager.fontH1, FontDrawOptions.DrawTextLeft | FontDrawOptions.DrawTextMiddle);
            origin.Y += origin.Height + 5;
            gamePanel.GameGraphics.DrawText(origin, "AI 3 level: ", MyResourceManager.colorT1, MyResourceManager.fontH1, FontDrawOptions.DrawTextLeft | FontDrawOptions.DrawTextMiddle);
        }

    }
}
