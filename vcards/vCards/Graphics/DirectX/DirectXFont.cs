using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

#if DESKTOP
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
#else
using Microsoft.WindowsMobile.DirectX;
using Microsoft.WindowsMobile.DirectX.Direct3D;
#endif

namespace vCards
{
    public class DirectXFont : IFont
    {
        ///  
        /// Gets the Direct3D font associated with this font data. 
        ///  
        Font fontValue = null;
        public Font Font { get { return fontValue; } }

        ///  
        /// Allocate and load a font. 
        ///  
        /// Name of font family 
        public DirectXFont(string fontName, Device device)
        {
            System.Drawing.Font gdi_font = new System.Drawing.Font(
                fontName, 12, System.Drawing.FontStyle.Regular);
            fontValue = new Font(device, gdi_font);
        }

        public void Dispose()
        {
            if (fontValue != null)
                fontValue.Dispose();
        }
    }
}
