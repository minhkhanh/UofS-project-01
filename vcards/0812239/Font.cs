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
        DrawTextCenter = 0x0,
        DrawTextRight = 0x1,
        DrawTextLeft = 0x2
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
