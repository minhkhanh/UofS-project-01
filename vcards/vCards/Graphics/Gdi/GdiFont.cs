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
using System.Runtime.InteropServices;
using System.Drawing;

#if DESKTOP 
using Microsoft.DirectX.Direct3D; 
#else
using Microsoft.WindowsMobile.DirectX;
using Microsoft.WindowsMobile.DirectX.Direct3D;
#endif

namespace vCards
{
    ///  
    /// Summary description for Font. 
    ///  
    public class GdiFont : IFont
    {
        System.Drawing.Font fontValue = null;

        ///  
        /// Gets the GDI font associated with this font data. 
        ///  
        public System.Drawing.Font Font { get { return fontValue; } }

        public GdiFont(string fontName, float fontSize, FontStyle fontStyle)
        {
            fontValue = new System.Drawing.Font(fontName, fontSize,
                fontStyle);
        }

        ///  
        /// Allocate and load a font. 
        ///  
        /// Name of font family 
        public GdiFont(string fontName)
        {
            fontValue = new System.Drawing.Font(fontName, 12,
                System.Drawing.FontStyle.Regular);
        }

        public void Dispose()
        {
            if (fontValue != null)
                fontValue.Dispose();
        }
    }
}
