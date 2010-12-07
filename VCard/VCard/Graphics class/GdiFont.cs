using System;
using System.Drawing;
namespace VCard
{
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