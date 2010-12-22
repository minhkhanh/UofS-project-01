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
        StateMenu,
        StateTest
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

        public virtual void EnterState(){}
        public virtual void UpdateState(){}
        public virtual void RenderState(){}
        public virtual void DrawState(){}
        public virtual void ExitState(){}

        public virtual void OnMouseDown(params object[] paras){}
        public virtual void OnMouseUp(params object[] paras){}

        public void HandleMessage(MessageID messID, params object[] paras)
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
                case MessageID.MouseDown:
                    OnMouseDown(paras);
                    break;
                case MessageID.MouseUp:
                    OnMouseUp(paras);
                    break;
                default:
                    throw new ApplicationException("HandleMessage() : Message ID unknown.");
            }
        }
    }
}
