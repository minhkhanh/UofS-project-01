﻿using System;
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
        public GameStateMenu(GamePanel gpn)
        {
            Gpnel = gpn;
            ID = GameStateID.StateMenu;
        }

        IImage iimgCover;
        List<MyBmpButton> buttons = new List<MyBmpButton>();
        public void InitButtons()
        {
            IBitmap ibmpBtnUp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\btnUp.bmp", true);
            IBitmap ibmpBtnDown = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\btnDown.bmp", true);

            Gpnel.IGameImgFactory.CreateImageFromFile(Gpnel.AppPath + @"Resources\Images\Misc\Untitled-1.png", out iimgCover);

            Rectangle origin = new Rectangle((Gpnel.IGameGracphics.ScreenWidth - 100)/2, 50, 100, 30);

            buttons.Add(new MyBmpButton("New Game", origin, MyButtonID.MainMenuNewGame, ibmpBtnUp, ibmpBtnDown, Gpnel.AppPath + @"Resources\Images\Misc\btnCover.png", Gpnel.IGameImgFactory));

            origin.Y += 10 + origin.Height;
            buttons.Add(new MyBmpButton("Options", origin, MyButtonID.MainMenuOption, ibmpBtnUp, ibmpBtnDown, Gpnel.AppPath + @"Resources\Images\Misc\btnCover.png", Gpnel.IGameImgFactory));

            origin.Y += 10 + origin.Height;
            buttons.Add(new MyBmpButton("Quit", origin, MyButtonID.MainMenuQuit, ibmpBtnUp, ibmpBtnDown, Gpnel.AppPath + @"Resources\Images\Misc\btnCover.png", Gpnel.IGameImgFactory));
        }
        
        public override void EnterState()
        {
            BackIBmp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\MenuBkgr.bmp", true);

            InitButtons();
        }

        public override void UpdateState()
        {
            
        }

        public override void RenderState()
        {
            //Gpnel.IGameGracphics.DrawBitmap(new Rectangle(0, 0, Gpnel.IGameGracphics.ScreenWidth, Gpnel.IGameGracphics.ScreenHeight), BackIBmp);
            DrawBkgr();

            foreach (MyBmpButton i in buttons)
            {
                i.Draw(Gpnel.IGameGracphics);
            }

            Gpnel.IGameGracphics.DrawImageAlphaChannel(iimgCover, new Rectangle(0, 0, 100, 100), new Rectangle(0, 0, 100, 100));
        }

        //public override void DrawState()
        //{
        //    Gpnel.IGameGracphics.Flip();
        //}

        public override void ExitState()
        {
        }

        MyBmpButton btnClicked = null;
        public override void OnMouseDown()
        {                        
            foreach (MyBmpButton i in buttons)
            {
                if (i.ValidateClick(Gpnel.Click))
                    btnClicked = i;
            }
        }

        public override void OnMouseUp()
        {
            foreach (MyBmpButton i in buttons)
            {
                if (i.State == MyButtonState.Down)
                {
                    i.State = MyButtonState.Up;
                }
            }

            if (btnClicked != null)
            {
                switch (btnClicked.ID)
                {
                    case MyButtonID.MainMenuNewGame:
                        Gpnel.ChangeState(GameStateID.StateGameCustom);
                        break;

                    case MyButtonID.MainMenuOption:
                        ExitState();
                        break;

                    case MyButtonID.MainMenuQuit:
                        ExitState();
                        break;
                }
            }
        }
    }
}
