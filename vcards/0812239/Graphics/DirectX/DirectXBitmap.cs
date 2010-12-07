using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

#if DESKTOP
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
#else
using Microsoft.WindowsMobile.DirectX;
using Microsoft.WindowsMobile.DirectX.Direct3D;
#endif

namespace _0812239
{
    ///  
    /// Summary description for Bitmap. 
    ///  
    public class DirectXBitmap : IBitmap
    {

        ///  
        /// True if the image should be drawn with alpha transparency 
        ///  
        public bool Transparent { get { return transparentValue; } }
        bool transparentValue;

        ///  
        /// Get the color of the images source key. 
        ///  
        public Color SourceKey { get { return sourceKey; } }
        Color sourceKey = Color.Empty;

        ///  
        /// The original width of the image 
        ///  
        int widthValue;

        ///  
        /// The original height of the image 
        ///  
        int heightValue;

        ///  
        /// The texture object holding this image 
        ///  
        public Texture Texture { get { return tex; } }
        Texture tex;


        ///  
        /// Get the width of this image. 
        ///  
        public int Width { get { return widthValue; } }

        ///  
        /// Get the height of this image. 
        ///  
        public int Height { get { return heightValue; } }

        ///  
        /// Allocate and load an image from the specified file. 
        ///  
        /// Name of image file 
        /// True if the image should have 
        /// transparency 
        public DirectXBitmap(string fileName, Device dev, bool transparent)
        {
            Bitmap bmp = new Bitmap(fileName);
            widthValue = bmp.Width;
            heightValue = bmp.Height;
            if (transparent)
                sourceKey = bmp.GetPixel(0, 0);
            transparentValue = transparent;
            bmp.Dispose();
            bmp = null;

#if DESKTOP 
            Format format = Format.A8R8G8B8; 
            Pool pool = Pool.Default; 
#else
            Format format = Format.A1R5G5B5;
            Pool pool = Pool.VideoMemory;
#endif
            tex = TextureLoader.FromFile(dev, fileName, Width, Height, 1,
                Usage.None, format, pool, Filter.Linear, Filter.None,
                SourceKey.ToArgb());
        }

        ///  
        /// Free any resources allocated for the image. 
        ///  
        public void Dispose()
        {
            if (tex != null)
            {
                tex.Dispose();
                tex = null;
            }

        }


    }
}
