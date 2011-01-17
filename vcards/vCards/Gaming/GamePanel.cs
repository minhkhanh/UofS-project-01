using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Drawing;

namespace vCards
{
    public enum MessageID
    {
        MessageUnknown,
        MessageEnter,
        MessageRender,
        MessageDraw,
        MessageExit,

        MouseDown,
        MouseUp
    }

    public class GamePanel
    {
        const int GAME_FPS = 24;
        Control ownerControl;

        public Control OwnerControl
        {
            get { return ownerControl; }
            set { ownerControl = value; }
        }

        IGraphics g;
        public IGraphics GameGraphics
        {
            get { return g; }
            set { g = value; }
        }
        GameOptions option = new GameOptions();
        public vCards.GameOptions Option
        {
            get { return option; }
            set { option = value; }
        }
        List<GameState> listGameStates = new List<GameState>();
        public void InitGameStates()
        {
            listGameStates.Add(new GameStateMenu(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\MenuBkgr.bmp"));
            listGameStates.Add(new GameStatePlaying(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\PlayBkgr.bmp"));
            listGameStates.Add(new GameStateOptions(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\OptMenuBkgr.bmp"));
            listGameStates.Add(new GameStateExiting(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\ExitBkgr.bmp"));
            listGameStates.Add(new GameStateHighScore(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\StateBkgrHighScore.bmp"));
        }

        public void ManageImgControl(MyControl ic)
        {
            ownerControl.MouseDown += new MouseEventHandler(ic.OnMouseDown);
            ownerControl.MouseUp += new MouseEventHandler(ic.OnMouseUp);
            ownerControl.MouseMove += new MouseEventHandler(ic.OnMouseMove);

            //ownerControl.Click += new EventHandler(ic.OnClick);
        }

        public GamePanel(Control frm)
        {
            g = new GdiGraphics(frm);

            ownerControl = frm;

            InitGameStates();
        }

        GameStateID currStateID = GameStateID.StateMenu;
        GameStateID nextStateID = GameStateID.None;

        public void SendMessage(MessageID messID, params object[] paras)
        {
            GameState target = listGameStates.Find(i => i.ID == currStateID);
            if (target != null)
                target.HandleMessage(messID, paras);
        }

        bool playing = true;
        public bool Playing
        {
            //get { return playing; }
            set { playing = value; }
        }

        bool enterState = true;
        bool exitState = false;

        //bool stateReady = false;
        //public void GameLoop2()
        //{
        //    while (playing)
        //    {
        //        if (stateReady)
        //        {
        //            SendMessage(MessageID.MessageRender);
        //            SendMessage(MessageID.MessageDraw);
        //        }
        //    }
        //}

        public void GameLoop()
        {
            int sleeptime = 1;
            while (playing)
            {
                int t1 = Environment.TickCount;
                if (enterState)
                {
                    SendMessage(MessageID.MessageEnter);
                    enterState = false;
                }

                if (sleeptime > 0)
                {
                    SendMessage(MessageID.MessageRender);
                    SendMessage(MessageID.MessageDraw);
                }

                if (exitState)
                {
                    exitState = false;
                    enterState = true;
                    SendMessage(MessageID.MessageExit);
                }

                sleeptime = 1000 / GAME_FPS - (Environment.TickCount - t1);
                //sleeptime = 10;
                if (sleeptime > 0)
                    Thread.Sleep(sleeptime);
            }
        }

        public void SwitchStateDone()
        {
            GameState prev = listGameStates.Find(i => i.ID == nextStateID);
            prev.PreviousStateID = currStateID;

            currStateID = nextStateID;
        }

        public void SwitchState(GameStateID next)
        {
            exitState = true;
            nextStateID = next;
        }
    }
}
