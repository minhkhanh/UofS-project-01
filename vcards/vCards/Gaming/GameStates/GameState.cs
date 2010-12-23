using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace vCards
{
    public enum GameStateID
    {
        StateUknown,
        StateMenu,
        StateTest,
        StatePlay,
        StateGameCustom
    }

    public abstract class GameState
    {
        GameStateID idState = GameStateID.StateUknown;
        public GameStateID ID
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

        public void DrawBkgr()
        {
            Gpnel.IGameGracphics.DrawBitmap(new Rectangle(0, 0, Gpnel.IGameGracphics.ScreenWidth, Gpnel.IGameGracphics.ScreenHeight), ibmpBack);
        }

        public virtual void EnterState(){}
        public virtual void UpdateState(){}
        public virtual void RenderState(){}
        public virtual void DrawState() { gpnel.IGameGracphics.Flip(); }
        public virtual void ExitState(){}

        public virtual void OnMouseDown(){}
        public virtual void OnMouseUp(){}

        public void HandleMessage(MessageID messID, params object[] paras)
        {
            switch (messID)
            {
                case MessageID.MessageEnter:
                    EnterState();
                    Gpnel.StateReady = true;
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
                    gpnel.StateReady = false;
                    break;
                case MessageID.MouseDown:
                    OnMouseDown();
                    break;
                case MessageID.MouseUp:
                    OnMouseUp();
                    break;
                default:
                    throw new ApplicationException("HandleMessage() : Message ID unknown.");
            }
        }
    }
}
