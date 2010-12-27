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

        IGraphics g;
        public IGraphics GameGraphics
        {
            get { return g; }
            set { g = value; }
        }

        List<GameState> listGameStates = new List<GameState>();
        public void InitGameStates()
        {
            listGameStates.Add(new GameStateMenu(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\MenuBkgr.bmp"));
            listGameStates.Add(new GameStateCustom(this, Program.AppPath + @"\Resources\Images\StateBackgrounds\PlayBkgr.bmp"));
        }

        public void ManageImgControl(ImageControl ic)
        {
            ownerControl.MouseDown += new MouseEventHandler(ic.OnMouseDown);
            ownerControl.MouseUp += new MouseEventHandler(ic.OnMouseUp);
            ownerControl.MouseMove += new MouseEventHandler(ic.OnMouseMove);

            ownerControl.Click += new EventHandler(ic.OnClick);
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

        bool enterState = true;
        bool exitState = false;

        bool stateReady = false;
        public bool StateReady
        {
            get { return stateReady; }
            set { stateReady = value; }
        }

        public void GameLoop2()
        {
            while (playing)
            {
                if (stateReady)
                {
                    SendMessage(MessageID.MessageRender);
                    SendMessage(MessageID.MessageDraw);
                }
            }
        }

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
            currStateID = nextStateID;
        }

        public void SwitchState(GameStateID next)
        {
            exitState = true;
            nextStateID = next;
        }
    }
}
