using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace vCards
{
    public class GameStateCustom: GameState
    {
        #region  declare all image controls

        //Pack pack01;
        //Pack pack02;
        //Deck deck01 = new Deck();
        BanChoi banChoi;
        PlayerClient player1;
        PlayerClient player2;
        ImageButton imgBtnEnter;
        ImageButton imgBtnSkip;

        int iIndexCardDanhRa = -1;

        Pack myPack;
        //ImageButton

        #endregion

        public GameStateCustom(GamePanel gp, string bkgrPath)
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
            player1 = new PlayerClientUser(new PlayerInfo("Khanh"));
            player1.JoinPlay();
            player2 = new PlayerClientAI(new PlayerInfo("MinhAI"));
            player2.JoinPlay();
            banChoi.NewGame(); // tao game moi phat bai cho client de hien thi len
            //((PlayerClientUser)player1).Rearrange(gamePanel.GameGraphics);            


            Rectangle origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 20) / 3, 230, 35, 12);
            imgBtnEnter = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Bkgr.bmp"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Hover.png");
            ctrlContainer.AddControl(imgBtnEnter);
            imgBtnEnter.MouseUp += new EventHandler<MouseEventArgs>(imgBtnEnter_MouseUp);

            origin = new Rectangle((gamePanel.GameGraphics.ScreenWidth - 20)*2 / 3, 230, 35, 12);
            imgBtnSkip = new ImageButton(origin
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Bkgr.bmp"
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Hover.png");
            ctrlContainer.AddControl(imgBtnSkip);
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
            if (player1.BuocDiTruoc.LoaiBuocDi == LoaiBuocDi.BinhThuong && cards.CompareTo(player1.BuocDiTruoc.Cards) <= 0)
            {
                return;
            }
            if (player1.BuocDiTruoc.LoaiBuocDi == LoaiBuocDi.BuocDau && !cards.IsHave(myPack.GetMinCardLogical()))
            {
                return;
            }
            if (player1.SendBaiPlayerDanh(cards))
            {
                myPack.RemoveSelectedCard();
                myPack.Rearrange(gamePanel.GameGraphics);
                //player1.Status = StatusPlayer.None;
            }
        }

        public void imgBtnSkip_MouseUp(object o, MouseEventArgs e)
        {
            player1.SendPlayerSkip();
            //player1.Status = StatusPlayer.None;
            //PaintNotTurnToPlayer();
        }

        public override void RenderState()
        {            
            if (((PlayerClientUser)player1).Status == StatusPlayer.ServerPhatBai)
            {
                myPack = new Pack(PlayerSide.Bottom, gamePanel.GameGraphics, player1.PackLogic);
                myPack.Rearrange(gamePanel.GameGraphics);
                ctrlContainer.AddControl(myPack);
                ((PlayerClientUser)player1).Status = StatusPlayer.None;
            }
            else if (((PlayerClientUser)player1).Status == StatusPlayer.DenLuotToiDi)
            {
                PaintTurnToPlayer();
            }
            else
            {
                PaintNotTurnToPlayer();
            }
            CardCombination cards = ((PlayerClientUser)player1).CardsOnePlayerGo;
            if (cards!=null)
            {
                NhomBaiDanhRa nhomBai = new NhomBaiDanhRa(gamePanel.GameGraphics, cards);
                if (iIndexCardDanhRa!=-1)
                {
                    ctrlContainer.RemoveAt(iIndexCardDanhRa);
                }
                iIndexCardDanhRa = ctrlContainer.AddControl(nhomBai);
                nhomBai.Rearrange(gamePanel.GameGraphics);
            }
            base.RenderState();
        }
    }
}
