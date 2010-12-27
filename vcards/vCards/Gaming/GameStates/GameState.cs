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
        StateGameCustom
    }

    public abstract class GameState
    {
        #region all data members

        protected GameStateID stateId = GameStateID.None;
        public GameStateID ID
        {
            get { return stateId; }
        }

        protected GamePanel gamePanel;

        List<ImageControl> listImgControls = new List<ImageControl>();

        protected IBitmap ibmpBack;

        //protected List<Rectangle> listDirtyRect = new List<Rectangle>();

        #endregion       

        public GameState(GamePanel gp, string bmpPath)
        {
            gamePanel = gp;
            ibmpBack = gamePanel.GameGraphics.CreateBitmap(bmpPath, false);

            InitControls();
        }

        public void ManageImgControl(ImageControl ic)
        {
            listImgControls.Add(ic);
            gamePanel.ManageImgControl(ic);
        }

        public void DrawStateBkgr()
        {
            gamePanel.GameGraphics.DrawBitmap(0, 0, ibmpBack);
            //listDirtyRect.Add(new Rectangle(0, 0, gamePanel.GameGraphics.ScreenWidth, gamePanel.GameGraphics.ScreenHeight));
        }

        public virtual void EnterState()
        {
            // - enable tat ca cac control co trong state
            EnableControls();
        }

        public virtual void RenderState() 
        {
            // - ve anh nen cua state
            DrawStateBkgr();

            // - ve ra tat ca cac control
            DrawControls(gamePanel.GameGraphics);
        }

        public virtual void DrawState()
        {
            // flip buffer
            gamePanel.GameGraphics.Flip();
        }

        public virtual void ExitState() 
        {
            gamePanel.SwitchStateDone(); 
        }

        /// <summary>
        /// Khoi tao gia tri, thong so cho cac control
        /// </summary>
        public abstract void InitControls();

        /// <summary>
        /// Kich hoat tat ca cac control thuoc state
        /// </summary>
        public virtual void EnableControls()
        {
            foreach (ImageControl i in listImgControls)
            {
                i.Enable();
            }
        }

        /// <summary>
        /// Vo hieu hoa tat ca cac control thuoc state
        /// </summary>
        public virtual void DisableControls()
        {
            foreach (ImageControl i in listImgControls)
            {
                i.Disable();
            }
        }

        /// <summary>
        /// Hien thi tat ca cac control thuoc state
        /// </summary>
        public virtual void DrawControls(IGraphics igp)
        {
            foreach (ImageControl i in listImgControls)
            {
                i.Draw(igp);
                //listDirtyRect.Add(i.Region);
            }
        }

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
