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
        public static IImage iimgCardCover;

        //public static IGraphics GameGraphics;
        //static Assembly assem = Assembly.GetExecutingAssembly();
        public MyResourceManager(IGraphics igraphics)
        {
            //GameGraphics = igraphics;

            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\spades.png", out iimgSpades);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\clubs.png", out iimgClubs);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\diamonds.png", out iimgDiamonds);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\hearts.png", out iimgHearts);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\cover.png", out iimgCardCover);
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
                default:
                    //throw new ApplicationException("CardShape constructor : CardSuit unknown.");
                    return null;
            }
        }
    }
}
