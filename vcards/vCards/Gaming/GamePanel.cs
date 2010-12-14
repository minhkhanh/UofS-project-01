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
        MessageExit
    }

    public class GamePanel
    {
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
            listGameStates.Add(new GameStateMenu(this));
        }

        public GamePanel(Control frm)
        {
            g = new GdiGraphics(frm);

            InitGameStates();
        }

        GameStateID currStateID = GameStateID.StateMenu;

        public void SendMessage(MessageID messID)
        {
            GameState target = listGameStates.Find(i => i.StateID == currStateID);
            if (target != null)
                target.HandleMessage(messID);
        }

        bool playing = true;

        bool enterState = true;
        bool exitState = false;

        public void GameLoop()
        {
            while (playing)
            {
                if (enterState)
                {
                    enterState = false;
                    SendMessage(MessageID.MessageEnter);
                }

                SendMessage(MessageID.MessageUpdate);

                if (exitState)
                {
                    SendMessage(MessageID.MessageExit);

                    exitState = false;
                    enterState = true;
                }
                else
                {
                    SendMessage(MessageID.MessageRender);
                    SendMessage(MessageID.MessageDraw);
                }

                Thread.Sleep(10);
            }
        }

        Point click = Point.Empty;
        public Point Click
        {
            get { return click; }
            set { click = value; }
        }
    }
}
