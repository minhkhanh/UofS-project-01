//--------------------------------------------------------------------- 
//  This file is part of the Microsoft .NET Framework SDK Code Samples. 
//  
//  Copyright (C) Microsoft Corporation.  All rights reserved. 
//  
//This source code is intended only as a supplement to Microsoft 
//Development Tools and/or on-line documentation.  See these other 
//materials for detailed information regarding Microsoft code samples. 
//  
//THIS CODE AND INFORMATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY 
//KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
//PARTICULAR PURPOSE. 
//--------------------------------------------------------------------- 

using System;
using System.IO;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

#if !DESKTOP
using Microsoft.WindowsMobile.DirectX;
using Microsoft.WindowsMobile.DirectX.Direct3D;
#else 
using Microsoft.DirectX; 
using Microsoft.DirectX.Direct3D; 
#endif

namespace vCards
{
    ///  
    /// Summary description for Bitmap. 
    ///  
    public class GdiBitmap : IBitmap
    {
        ///  
        /// Access the internal GDI representation of the Bitmap object 
        ///  
        internal Bitmap Image { get { return bmp; } }

        ///  
        /// Get the color of the images source key. 
        ///  
        public Color SourceKey { get { return sourceKeyValue; } }
        Color sourceKeyValue = Color.Empty;

        ///  
        /// True if the image should be drawn with alpha transparency 
        ///  
        public bool Transparent { get { return transparentValue; } }
        bool transparentValue;

        ///  
        /// Internal GDI representation of the image. 
        ///  
        Bitmap bmp = null;

        ///  
        /// Get the width of this image. 
        ///  
        public int Width { get { return bmp.Width; } }

        ///  
        /// Get the height of this image. 
        ///  
        public int Height { get { return bmp.Height; } }

        ///  
        /// Allocate and load an image from the specified file. 
        ///  
        /// Name of image file 
        public GdiBitmap(string fileName, bool transparent)
        {
            bmp = new Bitmap(fileName);
            transparentValue = transparent;
            if (transparent)
                sourceKeyValue = bmp.GetPixel(0, 0);
        }

        ///  
        /// Free any resources allocated for the image. 
        ///  
        public void Dispose()
        {
            bmp.Dispose();
        }
    }
}