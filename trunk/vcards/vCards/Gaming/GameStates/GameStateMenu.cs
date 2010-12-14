using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace vCards
{
    public class GameStateMenu : GameState
    {
        public GameStateMenu(GamePanel gpn)
        {
            Gpnel = gpn;
            StateID = GameStateID.StateMenu;
        }

        IImage iimgCover;
        //int nButtons = 3;
        List<MyBmpButton> buttons = new List<MyBmpButton>();
        public void InitButtons()
        {
            IBitmap ibmpBtnUp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\btnUp.bmp", true);
            IBitmap ibmpBtnDown = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\btnDown.bmp", true);

            Gpnel.IGameImgFactory.CreateImageFromFile(Gpnel.AppPath + @"Resources\Images\Misc\Untitled-1.png", out iimgCover);

            Rectangle origin = new Rectangle((Gpnel.IGameGracphics.ScreenWidth - 100)/2, 50, 100, 30);

            buttons.Add(new MyBmpButton("New Game", origin, ibmpBtnUp, ibmpBtnDown, Gpnel.AppPath + @"Resources\Images\Misc\Untitled-1.png", Gpnel.IGameImgFactory));

            origin.Y += 10 + origin.Height;
            buttons.Add(new MyBmpButton("Options", origin, ibmpBtnUp, ibmpBtnDown, Gpnel.AppPath + @"Resources\Images\Misc\Untitled-1.png", Gpnel.IGameImgFactory));

            origin.Y += 10 + origin.Height;
            buttons.Add(new MyBmpButton("Quit", origin, ibmpBtnUp, ibmpBtnDown, Gpnel.AppPath + @"Resources\Images\Misc\Untitled-1.png", Gpnel.IGameImgFactory));
        }
        
        public override void EnterState()
        {
            BackIBmp = Gpnel.IGameGracphics.CreateBitmap(Gpnel.AppPath + @"Resources\Images\Misc\MenuBkgr.bmp", true);

            InitButtons();
        }

        public override void UpdateState()
        {
            if (Gpnel.Click.IsEmpty == false)
                foreach (MyBmpButton i in buttons)
                {
                    if (i.IsIn(Gpnel.Click))
                    {
                        i.OnMouseDown();
                        //break;
                    }
                    else
                        i.OnMouseUp();
                }
            else
                foreach (MyBmpButton i in buttons)
                {
                    i.OnMouseUp();
                }
        }

        public override void RenderState()
        {
            Gpnel.IGameGracphics.DrawBitmap(new Rectangle(0, 0, Gpnel.IGameGracphics.ScreenWidth, Gpnel.IGameGracphics.ScreenHeight), BackIBmp);

            foreach (MyBmpButton i in buttons)
            {
                i.Draw(Gpnel.IGameGracphics);
            }

            Gpnel.IGameGracphics.DrawImageAlphaChannel(iimgCover, 0, 0);
        }

        public override void DrawState()
        {
            Gpnel.IGameGracphics.Flip();
        }

        public override void ExitState()
        {
        }
    }
}
