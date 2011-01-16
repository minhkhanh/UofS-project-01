using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using ShareLibrary;
using System.Media;

namespace vCards
{
    public class MyResourceManager
    {
        #region card images

        public static IImage iimgSpades;
        public static IImage iimgClubs;
        public static IImage iimgDiamonds;
        public static IImage iimgHearts;

        public static IImage iimgCardBottomCover;
        public static IImage iimgCardTopCover;
        public static IImage iimgCardLeftCover;
        public static IImage iimgCardRightCover;

        #endregion        

        #region button images

        public static IImage iimgLeftArrow;
        public static IImage iimgRightArrow;

        public static IImage iimgBtnDownCover;

        #endregion

        #region sounds

        public static int iMaxSong = 4;
        public static SoundPlayer[] bkgrSongs = new SoundPlayer[iMaxSong];
        public static int iCurrSong = 0;

        #endregion

        #region fonts

        public static IFont fontH1;

        #endregion


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

            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Buttons\SquareBtnBkgrLeftArrow.png", out iimgLeftArrow);
            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Buttons\SquareBtnBkgrRightArrow.png", out iimgRightArrow);

            igraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Buttons\BtnCoverDownState.png", out iimgBtnDownCover);

            fontH1 = igraphics.CreateFont("tahoma", 10, System.Drawing.FontStyle.Bold);

            bkgrSongs[0] = new SoundPlayer(Program.AppPath + @"\Resources\Sounds\Shorts\dee.wav");
            bkgrSongs[1] = new SoundPlayer(Program.AppPath + @"\Resources\Sounds\BkgrSongs\song01.wav");
            bkgrSongs[2] = new SoundPlayer(Program.AppPath + @"\Resources\Sounds\BkgrSongs\song02.wav");
            bkgrSongs[3] = new SoundPlayer(Program.AppPath + @"\Resources\Sounds\BkgrSongs\song03.wav");
            bkgrSongs[0].LoadAsync();
            bkgrSongs[1].LoadAsync();
            bkgrSongs[2].LoadAsync();
            bkgrSongs[3].LoadAsync();
        }

        public static void NextSong(int iSong)
        {
            if (iSong < 0 || iSong >= iMaxSong)
                return;

            bkgrSongs[iCurrSong].Stop();

            if (iSong != 0)
            {
                iCurrSong = iSong;
                bkgrSongs[iCurrSong].PlayLooping();
            }
        }

        public static void StopSounds()
        {
            foreach (SoundPlayer i in bkgrSongs)
            {
                i.Stop();
            }
        }

        public static IImage GetCardCoverImage(PlayerSide side)
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
