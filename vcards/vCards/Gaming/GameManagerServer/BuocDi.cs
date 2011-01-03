using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    enum LoaiBuocDi
    {
        BuocDau,
        BuocMoi,
        BinhThuong
    }
    class BuocDi
    {
        private PlayerServer player;
        public vCards.PlayerServer Player
        {
            get { return player; }
            set { player = value; }
        }
        private CardCombination cards;
        public vCards.CardCombination Cards
        {
            get { return cards; }
            set { cards = value; }
        }
        LoaiBuocDi loaiBuocDi = LoaiBuocDi.BinhThuong;
        public vCards.LoaiBuocDi LoaiBuocDi
        {
            get { return loaiBuocDi; }
            set { loaiBuocDi = value; }
        }
    }
}
