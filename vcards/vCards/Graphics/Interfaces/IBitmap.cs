using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public interface IBitmap : IDisposable
    {
        ///  
        /// Get the color of the image which will be transparent 
        ///  
        Color SourceKey { get; }

        ///  
        /// Gets the width of the image 
        ///  
        int Width { get; }

        ///  
        /// Gets the height of the image 
        ///  
        int Height { get; }

        ///  
        /// True if the object should be drawn with alpha transparency 
        ///  
        bool Transparent { get; }
    }
}
