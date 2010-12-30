using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace vCards
{
    public class MyResourceManager
    {
        public static IImage iimgSpades;
        public static IImage iimgClubs;
        public static IImage iimgDiamonds;
        public static IImage iimgHearts;

        public static IImage iimgCardBottomCover;
        public static IImage iimgCardTopCover;
        public static IImage iimgCardLeftCover;
        public static IImage iimgCardRightCover;

        //public static IGraphics GameGraphics;
        //static Assembly assem = Assembly.GetExecutingAssembly();
        public MyResourceManager(IGraphics igraphics)
        {
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\spades.png", out iimgSpades);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\clubs.png", out iimgClubs);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\diamonds.png", out iimgDiamonds);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\hearts.png", out iimgHearts);

            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\cover.png", out iimgCardBottomCover);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\top_cover.png", out iimgCardTopCover);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\leftside_cover.png", out iimgCardLeftCover);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\rightside_cover.png", out iimgCardRightCover);
        }

        public static IImage GetCoverImage(PlayerSide side)
        {
            switch (side)
            {
            case PlayerSide.Bottom:
                return iimgCardBottomCover;
            case PlayerSide.Top:
                return iimgCardTopCover;
            case PlayerSide.Left:
                return iimgCardLeftCover;
            case PlayerSide.Right:
                return iimgCardRightCover;
             default:
                return null;
            }
        }

        public static IImage GetCardImage(CardSuit suit)
        {
            switch (suit)
            {
                case CardSuit.Spades:
                    return iimgSpades;
                case CardSuit.Clubs:
                    return iimgClubs;
                case CardSuit.Diamonds:
                    return iimgDiamonds;
                case CardSuit.Hearts:
                    return iimgHearts;
                case CardSuit.None:
                    return iimgCardBottomCover;
                default:
                    //throw new ApplicationException("CardShape constructor : CardSuit unknown.");
                    return null;
            }
        }
    }
}
