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
        None,
        StateMenu,
        StateTest,
        StatePlay,
        StateGameCustom,
        StateOptions,
        StateExiting
    }

    public abstract class GameState
    {
        #region data members

        protected GameStateID stateId = GameStateID.None;
        protected GamePanel gamePanel;
        protected ImgCtrlContainer ctrlContainer;
        protected IBitmap ibmpBack;

        #endregion

        #region properties

        public GameStateID ID
        {
            get { return stateId; }
        }

        #endregion

        public GameState(GamePanel gp, string bmpPath)
        {
            gamePanel = gp;
            ibmpBack = gamePanel.GameGraphics.CreateBitmap(bmpPath, false);

            ctrlContainer = new ImgCtrlContainer(gamePanel.GameGraphics);
            gamePanel.ManageImgControl(ctrlContainer);

            //InitControls();
        }

        public void DrawStateBkgr()
        {
            gamePanel.GameGraphics.DrawBitmap(0, 0, ibmpBack);
        }

        public virtual void EnterState()
        {
            InitControls();

            // - enable tat ca cac control co trong state
            //ctrlContainer.Enabled = true;
        }

        public virtual void RenderState() 
        {
            // - ve anh nen cua state
            DrawStateBkgr();

            // - ve ra tat ca cac control
            ctrlContainer.Draw(gamePanel.GameGraphics);
        }

        public virtual void DrawState()
        {
            // flip buffer
            gamePanel.GameGraphics.Flip();
        }

        public virtual void ExitState() 
        {
            ctrlContainer.Dispose();

            gamePanel.SwitchStateDone(); 
        }

        /// <summary>
        /// Khoi tao gia tri, thong so cho cac control
        /// </summary>
        public virtual void InitControls(){}

        public void HandleMessage(MessageID messID, params object[] paras)
        {
            switch (messID)
            {
                case MessageID.MessageEnter:
                    EnterState();
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
