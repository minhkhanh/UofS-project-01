﻿using System;
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
        LoaiBuocDi loaiBuocDi = LoaiBuocDi.BinhThuong; // cac thong tin tren la cua buoc truoc, thong tin nay la cua buoc hien tai
        public LoaiBuocDi LoaiBuocDi
        {
            get { return loaiBuocDi; }
            set { loaiBuocDi = value; }
        }
    }
}
