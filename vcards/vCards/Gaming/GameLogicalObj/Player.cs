using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    public enum PlayerSide
    {
        None,
        Left,
        Top,
        Right,
        Bottom
    }

    public class Player
    {
        //PlayerSide side = PlayerSide.None;
        int iIndex;
        //PackLogical packLogic;
        Pack pack;
        public vCards.Pack Pack
        {
            get { return pack; }
            //set { pack = value; }
        }
        public Player(int i)
        {
            iIndex = i;
        }
        public void CreatePack(IGraphics ig)
        {
            pack = new Pack(PlayerSide.Bottom, ig);
        }
        public void RearrangePack(IGraphics ig)
        {
            pack.Rearrange(ig);
        }
        public void ReciveCard(params CardLogical[] cards)
        {
            if (cards.Count() < PackLogical.CARD_NUM) return;
            //packLogic = new PackLogical(cards);
            foreach (CardLogical c in cards)
            {
                pack.AddControl(new Card(c, PlayerSide.Bottom));
            }            
        }
    }
}
