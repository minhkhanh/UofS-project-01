using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    class BanChoi
    {
        public const int NUM_PLAYER = 4;
        List<PlayerServer> player = new List<PlayerServer>(NUM_PLAYER);
        Deck deck = null;
        Queue<PlayerServer> turn = null;
        public bool AddPlayer(PlayerInfo info)
        {
            if (player.Count>=NUM_PLAYER)
            {
                return false;
            }
            player.Add(new PlayerServer(info, player.Count));
            return true;
        }
        public bool NewGame()
        {
            if (player.Count < 2)
            {
                return false;
            }
            deck = new Deck();
            deck.DealAndSort(player.ToArray());
            return true;
        }
        private void InitTurn()
        {
            turn = new Queue<PlayerServer>(NUM_PLAYER);
        }
    }
}
