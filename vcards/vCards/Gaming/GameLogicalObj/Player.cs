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
        PlayerSide side = PlayerSide.None;
    }
}
