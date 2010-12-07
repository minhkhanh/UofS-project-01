using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace _0812239
{
    ///  
    /// Draw options used for drawing bitmaps. 
    ///  
    [FlagsAttribute]
    public enum DrawOptions
    {
        None = 0,
        BlitKeyedTransparency = 0x0001,
        BlitMirrorLeftRight = 0x0010,
        BlitMirrorUpDown = 0x0020
    }

    public interface IGraphics : IDisposable
    {
        ///  
        /// Gets the height of the screen. 
        ///  
        int ScreenWidth { get; }

        ///  
        /// Gets the width of the screen. 
        ///  
        int ScreenHeight { get; }

        ///  
        /// Draw the current cell of the animation to the back buffer. 
        ///  
        /// X destination of the draw 
        /// Y destination of the draw 
        /// Animation to be drawn 
        void DrawAnimation(int x, int y, Animation animation);

        ///  
        /// Draw the bitmap to the back buffer. 
        ///  
        /// X destination of the draw 
        /// Y destination of the draw 
        /// Source region of the draw 
        /// Bitmap to be drawn 
        void DrawBitmap(int x, int y, Rectangle sourceRegion, IBitmap bmp);

        ///  
        /// Draw a filled rectangle to the back buffer. 
        ///  
        /// Rectangle to be filled 
        /// Color of rectangle 
        void DrawFilledRect(Rectangle r, Color c);

        ///  
        /// Flip the back buffer to the display. 
        ///  
        void Flip();

        ///  
        /// Draw the string to the back buffer. 
        ///  
        /// X destination of text 
        /// Y destination of text 
        /// Text to be displayed 
        /// Color of text 
        /// Font to be used 
        /// Font draw options 
        void DrawText(int x, int y, string text, Color color, IFont font,
            FontDrawOptions options);

        ///  
        /// Set the current draw mode. 
        ///  
        /// options to be set 
        void SetDrawOptions(DrawOptions options);

        ///  
        /// Clear the current draw mode of the specified options. 
        ///  
        /// options to be cleared 
        void ClearDrawOptions(DrawOptions options);

        ///  
        /// Creates a bitmap compatible with this graphics device 
        ///  
        /// The file to load the image from 
        /// True if the image should be drawn with 
        /// alpha transparency 
        /// A bitmap compatible with this graphics device 
        IBitmap CreateBitmap(string fileName, bool transparent);

        ///  
        /// Creates a font object compatible with this graphics device 
        ///  
        ///  
        /// A font object compatible with this graphics device 
        ///  
        IFont CreateFont(string fontName);
    }
}
