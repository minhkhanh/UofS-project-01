using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace _0812239
{
    public class GdiBitmap : IBitmap
    {
        public GdiBitmap(string strFileName, bool bTransparent)
        {
            bmp = new Bitmap(strFileName);
            transparent = bTransparent;
        }

        public GdiBitmap(Bitmap bmpImage, bool bTransparent)
        {
            bmp = new Bitmap(bmpImage);
            transparent = bTransparent;
        }

        public GdiBitmap(System.IO.Stream strm, bool bTransparent)
        {
            bmp = new Bitmap(strm);
            transparent = bTransparent;
        }

        private Bitmap bmp;
        public Bitmap Image
        {
            get { return bmp; }
            set { bmp = value; }
        }

        private Color keycolor;
        private bool transparent;  // true: xoa nen khi ve bitmap

        #region IBitmap Members

        public int Height
        {
            get { return bmp.Height; }
        }

        public int Width
        {
            get { return bmp.Width; }
        }

        public Color KeyColor
        {
            get { return keycolor; }
            set { keycolor = value; }
        }

        public bool Transparent
        {
            get { return transparent; }
            set { transparent = value; }
        }

        #endregion

        #region IDisposable Members

        public void Dispose()
        {
            bmp.Dispose();
        }

        #endregion
    }
}
