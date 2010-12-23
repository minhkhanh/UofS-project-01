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
        MessageUpdate,
        MessageRender,
        MessageDraw,
        MessageExit,

        MouseDown,
        MouseUp
    }

    public class GamePanel
    {
        Control ownerForm;
        public Control OwnerForm
        {
            get { return ownerForm; }
            set { ownerForm = value; }
        }

        IImagingFactory factory = (IImagingFactory)Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid("327ABDA8-072B-11D3-9D7B-0000F81EF32E")));
        public IImagingFactory IGameImgFactory
        {
            get { return factory; }
            set { factory = value; }
        }

        IGraphics g;
        public IGraphics IGameGracphics
        {
            get { return g; }
            set { g = value; }
        }

        string pathApp = System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName.Replace(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].Name, "");
        public string AppPath
        {
            get { return pathApp; }
            set { pathApp = value; }
        }

        List<GameState> listGameStates = new List<GameState>();
        public void InitGameStates()
        {
            listGameStates.Add(new GameTestState(this));
            listGameStates.Add(new GameStateMenu(this));
            listGameStates.Add(new GameStatePlay(this));
            listGameStates.Add(new GameStateCustom(this));
        }

        public GamePanel(Control frm)
        {
            g = new GdiGraphics(frm);

            ownerForm = frm;

            InitGameStates();
        }

        GameStateID currStateID = GameStateID.StateMenu;
        public GameStateID CurrentState
        {
            get { return currStateID; }
            set { currStateID = value; }
        }

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

        public void GameLoop()
        {
            while (playing)
            {
                int tickPrev = Environment.TickCount;

                //if (enterState)
                //{
                //    enterState = false;
                //    SendMessage(MessageID.MessageEnter);
                //}

                //SendMessage(MessageID.MessageUpdate);

                //if (exitState)
                //{
                //    SendMessage(MessageID.MessageExit);

                //    exitState = false;
                //    enterState = true;
                //}
                //else
                //{
                //    SendMessage(MessageID.MessageRender);
                //    SendMessage(MessageID.MessageDraw);
                //}

                if (stateReady)
                {
                    SendMessage(MessageID.MessageRender);
                    SendMessage(MessageID.MessageDraw);
                }

                int tickSleep = tickPrev + 100 - Environment.TickCount;
                Thread.Sleep(Math.Abs(tickSleep));

                //tickPrev = Environment.TickCount;
            }
        }

        public void GameLoop2()
        {
            while (playing)
            {
                SendMessage(MessageID.MessageRender);
                SendMessage(MessageID.MessageDraw);
             
                Thread.Sleep(10);
            }
        }

        public void ChangeState(GameStateID id)
        {
            SendMessage(MessageID.MessageExit);

            currStateID = id;
            SendMessage(MessageID.MessageEnter);            
        }

        //MyButtonState clickState = MyButtonState.Up;
        //public MyButtonState ClickState
        //{
        //    get { return clickState; }
        //    set { clickState = value; }
        //}

        Point click = Point.Empty;
        public Point Click
        {
            get { return click; }
            set { click = value; }
        }
    }
}
