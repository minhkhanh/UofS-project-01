using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace _0812239
{
    [FlagsAttribute]
    public enum FontDrawOptions
    {
        DrawTextCenter = 0,
        DrawTextRight = 1,
        DrawTextLeft = 2,
        DrawTextTop = 4,
        DrawTextBottom = 8
    }

    public interface IFont
    {
        void Dispose();
    }

    public class GdiFont : IFont
    {
        public GdiFont(string strFontName)
        {
            //!!! CHUA CAI DAT
        }

        public GdiFont(string strFontName, float fontSize, FontStyle fontStye)
        {
            fontValue = new Font(strFontName, fontSize, fontStye);
        }

        private Font fontValue;
        public Font Font
        {
            get { return fontValue; }
            set { fontValue = value; }
        }

        public GdiFont(Font fontNew)
        {
            fontValue = fontNew;
        }

        #region IFont Members

        public void Dispose()
        {
            fontValue.Dispose();
        }

        #endregion
    }
}
