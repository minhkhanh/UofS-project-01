using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace ShareLibrary
{
    public enum LoaiBuocDi
    {
        BuocDau,
        BuocMoi,
        BinhThuong
    }
    public class BuocDi
    {
        private PlayerInfo player;
        public PlayerInfo Player
        {
            get { return player; }
            set { player = value; }
        }
        private CardCombination cards;
        public CardCombination Cards
        {
            get { return cards; }
            set { cards = value; }
        }
        LoaiBuocDi loaiBuocDi = LoaiBuocDi.BinhThuong;
        public LoaiBuocDi LoaiBuocDi
        {
            get { return loaiBuocDi; }
            set { loaiBuocDi = value; }
        }
    }
}
