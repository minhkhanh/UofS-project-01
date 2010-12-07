using System.Drawing;
using Microsoft.WindowsMobile.DirectX.Direct3D;
namespace VCard
{
    public class DirectXBitmap : IBitmap
    {
        public DirectXBitmap(string fileName, Device device, bool transparent)
        {

        }
        private Bitmap bmp;
        private Color sourceKeyValue;
        private bool transparentValue;  // true: xoa nen khi ve bitmap
        private Texture texture;
        public Microsoft.WindowsMobile.DirectX.Direct3D.Texture Texture
        {
            get { return texture; }
            set { texture = value; }
        }
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
            throw new System.NotImplementedException();
        }

        #endregion
    }

}