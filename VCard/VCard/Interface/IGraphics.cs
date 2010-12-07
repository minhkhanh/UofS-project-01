using System;
using System.Drawing;
namespace VCard
{
    public interface IGraphics : IDisposable
    {
        /// <summary>
        /// Gets the height of the screen.
        /// </summary>
        int ScreenWidth { get; }

        /// <summary>
        /// Gets the width of the screen.
        /// </summary>
        int ScreenHeight { get; }

        /// <summary>
        /// Draw the current cell of the animation to the back buffer.
        /// </summary>
        /// <param name="x">X destination of the draw</param>
        /// <param name="y">Y destination of the draw</param>
        /// <param name="animation">Animation to be drawn</param>
        void DrawAnimation(int x, int y, Animation animation);

        /// <summary>
        /// Ve anh trong suot
        /// </summary>
        /// <param name="image"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        //void DrawImageAlphaChannel(IImage image, int x, int y);
        //void DrawImageAlphaChannel(IImage image, Rectangle dest);
        //void DrawImageAlphaChannel(IImage image, Rectangle dest, Rectangle src);

        /// <summary>
        /// Ve toan bo anh len mot vung cua thiet bi do hoa
        /// </summary>
        /// <param name="image"></param>
        /// <param name="destRect"></param>
        void DrawImageTransparent(IBitmap image, Rectangle destRect);

        /// <summary>
        /// Ve mot vung cua anh len mot vi tri tren thiet bi do hoa
        /// </summary>
        /// <param name="image"></param>
        /// <param name="srcRect"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        void DrawImageTransparent(IBitmap image, Rectangle srcRect, int x, int y);

        /// <summary>
        /// Draw the bitmap to the back buffer.
        /// </summary>
        /// <param name="x">X destination of the draw</param>
        /// <param name="y">Y destination of the draw</param>
        /// <param name="sourceRegion">Source region of the draw</param>
        /// <param name="bmp">Bitmap to be drawn</param>
        void DrawBitmap(int x, int y, Rectangle sourceRegion, IBitmap bmp);

        /// <summary>
        /// Draw a filled rectangle to the back buffer.
        /// </summary>
        /// <param name="r">Rectangle to be filled</param>
        /// <param name="c">Color of rectangle</param>
        void DrawFilledRect(Rectangle r, Color c);

        /// <summary>
        /// Flip the back buffer to the display.
        /// </summary>
        void Flip();

        /// <summary>
        /// Draw the string to the back buffer.
        /// </summary>
        /// <param name="x">X destination of text</param>
        /// <param name="y">Y destination of text</param>
        /// <param name="text">Text to be displayed</param>
        /// <param name="color">Color of text</param>
        /// <param name="font">Font to be used</param>
        /// <param name="options">Font draw options</param>
        void DrawText(int x, int y, string text, Color color, IFont font,
            FontDrawOptions options);

        /// <summary>
        /// Set the current draw mode.
        /// </summary>
        /// <param name="options">options to be set</param>
        void SetDrawOptions(DrawOptions options);

        /// <summary>
        /// Clear the current draw mode of the specified options.
        /// </summary>
        /// <param name="options">options to be cleared</param>
        void ClearDrawOptions(DrawOptions options);

        /// <summary>
        /// Creates a bitmap compatible with this graphics device
        /// </summary>
        /// <param name="fileName">The file to load the image from</param>
        /// <param name="transparent">True if the image should be drawn with
        /// alpha transparency</param>
        /// <returns>A bitmap compatible with this graphics device</returns>
        IBitmap CreateBitmap(string fileName, bool transparent);

        /// <summary>
        /// Creates a font object compatible with this graphics device
        /// </summary>
        /// <param name="fontName"></param>
        /// <returns>A font object compatible with this graphics device
        /// </returns>
        IFont CreateFont(string fontName);
    }
}