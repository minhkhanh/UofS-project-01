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

        ImageButton okImgBtn;
        CardPack pack01;
        CardPack pack02;
        Deck deck01 = new Deck();

        #endregion

        public GameStateCustom(GamePanel gp, string bkgrPath)
            : base(gp, bkgrPath)
        {
            stateId = GameStateID.StateGameCustom;
        }
        
        public override void InitControls()
        {
            okImgBtn = new ImageButton(new Rectangle(50, 100, 100, 50)
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Bkgr.bmp"                
                , gamePanel.GameGraphics
                , Program.AppPath + @"\Resources\Images\Buttons\OKBtn_Hover.png"
                );
            ctrlContainer.AddControl(okImgBtn);

            pack01 = new CardPack(PlayerSide.Bottom, gamePanel.GameGraphics);           

            deck01.Deal(pack01);

            gamePanel.ManageImgControl(pack01);
            //gamePanel.ManageImgControl(pack02);

            pack01.Rearrange(gamePanel.GameGraphics);
            //pack02.Rearrange(gamePanel.GameGraphics);
        }

        public override void RenderState()
        {
            base.RenderState();

            pack01.Draw(gamePanel.GameGraphics);
        }
    }
}
