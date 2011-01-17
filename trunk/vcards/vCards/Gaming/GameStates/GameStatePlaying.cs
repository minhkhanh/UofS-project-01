using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using ShareLibrary;

namespace vCards
{
    public class GameStatePlaying: GameState
    {
        #region  declare all image controls

        //Pack pack01;
        //Pack pack02;
        //Deck deck01 = new Deck();
        BanChoi banChoi;
        PlayerClient myPlayer;
        //PlayerClient player2;
        List<PlayerClient> playerAI = new List<PlayerClient>(3);
        ImageButton imgBtnEnter;
        ImageButton imgBtnSkip;

        int iIndexCardDanhRa = -1;

        Pack myPack;
        //ImageButton

        #endregion

        public GameStatePlaying(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateGameCustom;
        }
        
        public override void InitControls()
        {
            //pack01 = new Pack(PlayerSide.Bottom, gamePanel.GameGraphics);
            //pack02 = new Pack(PlayerSide.Left, gamePanel.GameGraphics);

            //pack01.Enabled = true;
            //pack02.Enabled = false;

            ////deck01.Deal(pack01, pack02);

            //ctrlContainer.AddControl(pack01);
            //ctrlContainer.AddControl(pack02);

            //pack01.SortByValue();

            //pack01.Rearrange(gamePanel.GameGraphics);
            //pack02.Rearrange(gamePanel.GameGraphics);
            banChoi = BanChoi.Create();
            myPlayer = new PlayerClientUser(new PlayerInfo("Khanh"));
            myPlayer.JoinPlay();
            int iCountAI = 0;
            foreach (string str in gamePanel.Option.ArrNameAI)
            {
                PlayerClient p = new PlayerClientAI(new PlayerInfo("AI " + iCountAI.ToString()), str);
                iCountAI++;
                playerAI.Add(p);
            }
            foreach (PlayerClient p in playerAI)
            {
                p.JoinPlay();
            }
            banChoi.NewGame(); // tao game moi phat bai cho client de hien thi len
            //((PlayerClientUser)player1).Rearrange(gamePanel.GameGraphics);            


            Rectangle origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 20) / 3, 230, 35, 12);
            imgBtnEnter = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\SquareBtnBkgrLeftArrow.png"
                , gamePanel.GameGraphics
                );
            ctrlContainer.ManageControl(imgBtnEnter);
            imgBtnEnter.MouseUp += new EventHandler<MouseEventArgs>(imgBtnEnter_MouseUp);

            origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 20)*2 / 3, 230, 35, 12);
            imgBtnSkip = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\SquareBtnBkgrLeftArrow.png"
                , gamePanel.GameGraphics
                );
            ctrlContainer.ManageControl(imgBtnSkip);
            imgBtnSkip.MouseUp += new EventHandler<MouseEventArgs>(imgBtnSkip_MouseUp);
            imgBtnEnter.Visible = false;
            imgBtnSkip.Visible = false;
            imgBtnEnter.Enabled = false;
            imgBtnSkip.Enabled = false;


            BanChoi.StartThread(banChoi);
        }

        private void PaintServerChiaBai()
        {

        }

        private void PaintTurnToPlayer()
        {
            imgBtnEnter.Visible = true;
            imgBtnSkip.Visible = true;
            imgBtnEnter.Enabled = true;
            imgBtnSkip.Enabled = true;
        }

        private void PaintNotTurnToPlayer()
        {
            imgBtnEnter.Visible = false;
            imgBtnSkip.Visible = false;
            imgBtnEnter.Enabled = false;
            imgBtnSkip.Enabled = false;
        }

        public void imgBtnEnter_MouseUp(object o, MouseEventArgs e)
        {
            PackLogical pack = myPack.GetSelectedCard();
            CardCombination cards = CardCombination.CreateCombination(pack.ListCards.ToArray());
            if (cards==null)
            {
                return;
            }
            if (myPlayer.BuocDiTruoc.LoaiBuocDi == LoaiBuocDi.BinhThuong && cards.CompareTo(myPlayer.BuocDiTruoc.Cards) <= 0)
            {
                return;
            }
            if (myPlayer.BuocDiTruoc.LoaiBuocDi == LoaiBuocDi.BuocDau && !cards.IsHave(myPack.GetMinCardLogical()))
            {
                return;
            }
            if (myPlayer.SendBaiPlayerDanh(cards))
            {
                myPack.RemoveSelectedCard();
                myPack.Rearrange(gamePanel.GameGraphics);
                //player1.Status = StatusPlayer.None;
            }
        }

        public void imgBtnSkip_MouseUp(object o, MouseEventArgs e)
        {
            myPlayer.SendPlayerSkip();
            //player1.Status = StatusPlayer.None;
            //PaintNotTurnToPlayer();
        }

        public override void RenderState()
        {
            if (((PlayerClientUser)myPlayer).IsEndGame)
            {
                GoBackState();
            }
            if (((PlayerClientUser)myPlayer).Status == StatusPlayer.ServerPhatBai)
            {
                myPack = new Pack(PlayerSide.Bottom, gamePanel.GameGraphics, myPlayer.PackLogic);
                myPack.Rearrange(gamePanel.GameGraphics);
                ctrlContainer.ManageControl(myPack);
                ((PlayerClientUser)myPlayer).Status = StatusPlayer.None;
            }
            else if (((PlayerClientUser)myPlayer).Status == StatusPlayer.DenLuotToiDi)
            {
                PaintTurnToPlayer();
                if (myPlayer.BuocDiTruoc.LoaiBuocDi == LoaiBuocDi.BuocMoi && iIndexCardDanhRa != -1)
                {
                    ctrlContainer.RemoveAt(iIndexCardDanhRa);
                    iIndexCardDanhRa = -1;
                }
            }
            else
            {
                PaintNotTurnToPlayer();
            }
            CardCombination cards = ((PlayerClientUser)myPlayer).CardsOnePlayerGo;
            if (cards!=null)
            {
                NhomBaiDanhRa nhomBai = new NhomBaiDanhRa(gamePanel.GameGraphics, cards);
                if (iIndexCardDanhRa!=-1)
                {
                    ctrlContainer.RemoveAt(iIndexCardDanhRa);
                }
                iIndexCardDanhRa = ctrlContainer.ManageControl(nhomBai);
                nhomBai.Rearrange(gamePanel.GameGraphics);
            }
            base.RenderState();
            gamePanel.GameGraphics.DrawText(
                new Rectangle(10, 15, 200, 20)
                , ((PlayerClientUser)myPlayer).StatusString
                , MyResourceManager.colorT1
                , MyResourceManager.fontH1
                , FontDrawOptions.DrawTextMiddle | FontDrawOptions.DrawTextLeft
                );
        }
    }
}
