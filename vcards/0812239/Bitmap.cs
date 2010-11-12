using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace _0812239
{
    public interface IBitmap : IDisposable
    {
        int Height { get;}
        Color SourceKey { get; set; }
        bool Transparent { get; set; }
        int Width { get;}
    }

    public class GdiBitmap : IBitmap
    {
        public GdiBitmap(string strFileName, bool bTransparent)
        {
            //!!! CHUA CAI DAT
        }

        private Bitmap bmp;
        public Bitmap Image
        {
            get { return bmp; }
            set { bmp = value; }
        }

        private Color sourceKeyValue;
        private bool transparentValue;

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
