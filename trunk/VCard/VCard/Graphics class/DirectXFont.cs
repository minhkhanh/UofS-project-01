using System;
//using System.Drawing;
using Microsoft.WindowsMobile.DirectX.Direct3D;
namespace VCard
{
    public class DirectXFont : IFont
    {
        public DirectXFont(string fontName, Device device)
        {
            //!!! CHUA CAI DAT
        }

        private Font fontValue;
        public Font Font
        {
            get { return fontValue; }
            set { fontValue = value; }
        }

        public DirectXFont(Font fontNew)
        {
            fontValue = fontNew;
        }
        #region IFont Members

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}