using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    public class ResourcesManager
    {
        public static GamePanel gamePanel;
        //public static IImage GetImageResource(string path)
        //{
        //    IImage iimgCover;
        //    gpanel.IGameImgFactory.CreateImageFromFile(gpanel.AppPath + @"Resources\Images\Misc\Untitled-1.png", out iimgCover);
        //    return iimgCover; 
        //}
        public static IImage GetCardImage(int num)
        {
            if (num < 0) return null;
            IImage iimgCover;
            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Cards\" + num.ToString("D2") + ".png", out iimgCover);
            return iimgCover;
        }

        public static IBitmap GetCardBitmap(int num)
        {
            if (num < 0) return null;
            return gamePanel.GameGraphics.CreateBitmap(Program.AppPath + @"\Resources\Images\Cards\" + num.ToString("D2") + ".png", false);
        }
    }
}
