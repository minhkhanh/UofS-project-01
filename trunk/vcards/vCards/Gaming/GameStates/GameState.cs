using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace vCards
{
    public enum GameStateID
    {
        StateUknown,
        StateMenu
    }

    public abstract class GameState
    {
        GameStateID idState = GameStateID.StateUknown;
        public GameStateID StateID
        {
            get { return idState; }
            set { idState = value; }
        }

        Control owner;
        public Control Owner
        {
            get { return owner; }
            set { owner = value; }
        }

        GamePanel gpnel;
        public GamePanel Gpnel
        {
            get { return gpnel; }
            set { gpnel = value; }
        }

        IBitmap ibmpBack;
        public IBitmap BackIBmp
        {
            get { return ibmpBack; }
            set { ibmpBack = value; }
        }

        public abstract void EnterState();
        public abstract void UpdateState();
        public abstract void RenderState();
        public abstract void DrawState();
        public abstract void ExitState();

        public void HandleMessage(MessageID messID)
        {
            switch (messID)
            {
                case MessageID.MessageEnter:
                    EnterState();
                    break;
                case MessageID.MessageUpdate:
                    UpdateState();
                    break;
                case MessageID.MessageRender:
                    RenderState();
                    break;
                case MessageID.MessageDraw:
                    DrawState();
                    break;
                case MessageID.MessageExit:
                    ExitState();
                    break;
                default:
                    throw new ApplicationException("HandleMessage() : Message ID unknown.");
            }
        }
    }
}
