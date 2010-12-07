using System;
using System.Drawing;
namespace VCard
{
    public class GdiBitmap : IBitmap
    {
        public GdiBitmap(string strFileName, bool bTransparent)
        {
            bmp = new Bitmap(strFileName);
            transparentValue = bTransparent;
        }

        public GdiBitmap(Bitmap bmpImage, bool bTransparent)
        {
            bmp = new Bitmap(bmpImage);
            transparentValue = bTransparent;
        }

        public GdiBitmap(System.IO.Stream strm, bool bTransparent)
        {
            bmp = new Bitmap(strm);
            transparentValue = bTransparent;
        }

        private Bitmap bmp;

        public Bitmap Image
        {
            get { return bmp; }
            set { bmp = value; }
        }
        private Color sourceKeyValue;
        private bool transparentValue;  // true: xoa nen khi ve bitmap

        #region IBitmap Members

        public int Height
        {
            get { return bmp.Height; }
        }

        public int Width
        {
            get { return bmp.Width; }
        }

        public Color SourceKey
        {
            get { return sourceKeyValue; }
            set { sourceKeyValue = value; }
        }

        public bool Transparent
        {
            get { return transparentValue; }
            set { transparentValue = value; }
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