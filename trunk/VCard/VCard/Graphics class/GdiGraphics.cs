using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Drawing.Imaging;
namespace VCard
{
    /// <summary>
    /// A GDI implementation of the IGraphics
    /// </summary>
    public class GdiGraphics : IGraphics
    {
        /// <summary>
        /// Gets the width of the screen.
        /// </summary>
        public int ScreenWidth
        {
            get { return back.Width; }
        }

        /// <summary>
        /// Gets the height of the screen.
        /// </summary>
        public int ScreenHeight
        {
            get { return back.Height; }
        }

        /// <summary>
        /// Represents the back buffer.
        /// </summary>
        Bitmap back = null;

        /// <summary>
        /// Graphics object associated with the back buffer.
        /// </summary>
        Graphics gBack = null;

        /// <summary>
        /// Graphics object associated with the screen / owner control.
        /// </summary>
        Graphics screen = null;

        /// <summary>
        /// Initialize the graphics engine.
        /// </summary>
        /// <param name="owner">Owner control (Form)</param>
        public GdiGraphics(Control owner)
        {
            back = new Bitmap(owner.Width, owner.Height);
            gBack = Graphics.FromImage(back);
            screen = owner.CreateGraphics();
        }

        /// <summary>
        /// Disposes allocated resources
        /// </summary>
        public void Dispose()
        {
            screen.Dispose();
            gBack.Dispose();
        }

        /// <summary>
        /// Draw the current cell of the animation to the back buffer.
        /// </summary>
        /// <param name="x">X destination of the draw</param>
        /// <param name="y">Y destination of the draw</param>
        /// <param name="animation">Animation to be drawn</param>
        public void DrawAnimation(int x, int y, Animation animation)
        {
            DrawBitmap(x, y, animation.Region, animation.Image);
        }

        /// <summary>
        /// Ve anh len mot vung nao do. Anh se tu dong bien doi cho phu hop voi vung can ve
        /// </summary>
        /// <param name="image"></param>
        /// <param name="destRect"></param>
        public void DrawImageTransparent(IBitmap image, Rectangle destRect)
        {
            GdiBitmap gdiBitmap = null;
            try
            {
                gdiBitmap = (GdiBitmap)image;
            }
            catch (InvalidCastException e)
            {
                throw new ApplicationException(
                    "The bitmap given was not created by" +
                    "this class' CreateBitmap() method.", e);
            }

            // Clip the regions to the screen
            int x = destRect.X;      // temp variable for function param, not used
            int y = destRect.Y;      // temp variable for function param, not used
            if (!ValidateRegions(ref x, ref y, ref destRect))
                return;

            if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
            {
                //Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                //    sourceRegion.Height);

                ImageAttributes attr = new ImageAttributes();
                attr.SetColorKey(gdiBitmap.SourceKey, gdiBitmap.SourceKey);
                gBack.DrawImage(gdiBitmap.Image, destRect,
                    gdiBitmap.Width, 0,
                    -gdiBitmap.Width, gdiBitmap.Height,
                    GraphicsUnit.Pixel, attr);
            }
            else
            {
                //Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                //    sourceRegion.Height);

                ImageAttributes attr = new ImageAttributes();
                attr.SetColorKey(gdiBitmap.SourceKey, gdiBitmap.SourceKey);
                gBack.DrawImage(gdiBitmap.Image, destRect,
                    0, 0,
                    gdiBitmap.Width, gdiBitmap.Height,
                    GraphicsUnit.Pixel, attr);
            }
        }

        public void DrawImageTransparent(IBitmap image, Rectangle srcRect, int x, int y)
        {
            GdiBitmap gdiBitmap = null;
            try
            {
                gdiBitmap = (GdiBitmap)image;
            }
            catch (InvalidCastException e)
            {
                throw new ApplicationException(
                    "The bitmap given was not created by" +
                    "this class' CreateBitmap() method.", e);
            }

            // Clip the regions to the screen
            if (!ValidateRegions(ref x, ref y, ref srcRect))
                return;

            if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
            {
                Rectangle dest = new Rectangle(x, y, srcRect.Width, srcRect.Height);

                ImageAttributes attr = new ImageAttributes();
                attr.SetColorKey(gdiBitmap.SourceKey, gdiBitmap.SourceKey);
                gBack.DrawImage(gdiBitmap.Image, dest,
                    srcRect.X + srcRect.Width, srcRect.Y,
                    -srcRect.Width, srcRect.Height,
                    GraphicsUnit.Pixel, attr);
            }
            else
            {
                Rectangle dest = new Rectangle(x, y, srcRect.Width, srcRect.Height);

                ImageAttributes attr = new ImageAttributes();
                attr.SetColorKey(gdiBitmap.SourceKey, gdiBitmap.SourceKey);
                gBack.DrawImage(gdiBitmap.Image, dest,
                    srcRect.X, srcRect.Y,
                    srcRect.Width, srcRect.Height,
                    GraphicsUnit.Pixel, attr);
            }
        }

        /// <summary>
        /// Draw the bitmap to the back buffer.
        /// </summary>
        /// <param name="x">X destination of the draw</param>
        /// <param name="y">Y destination of the draw</param>
        /// <param name="sourceRegion">Source region of the draw</param>
        /// <param name="bmp">Bitmap to be drawn</param>
        public void DrawBitmap(int x, int y, Rectangle sourceRegion,
            IBitmap bmp)
        {
            // make sure the function is passed an appropriate implementation
            GdiBitmap gdiBitmap = null;
            try
            {
                gdiBitmap = (GdiBitmap)bmp;
            }
            catch (InvalidCastException e)
            {
                throw new ApplicationException(
                    "The bitmap given was not created by" +
                    "this class' CreateBitmap() method.", e);
            }

            // Clip the regions to the screen
            if (!ValidateRegions(ref x, ref y, ref sourceRegion))
                return;

            // Draw the bitmap
            if (gdiBitmap.Transparent)
            {
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
                {
                    Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                        sourceRegion.Height);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetColorKey(gdiBitmap.SourceKey, gdiBitmap.SourceKey);
                    gBack.DrawImage(gdiBitmap.Image, dest,
                        sourceRegion.X + sourceRegion.Width, sourceRegion.Y,
                        -sourceRegion.Width, sourceRegion.Height,
                        GraphicsUnit.Pixel, attr);
                }
                else
                {
                    Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                        sourceRegion.Height);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetColorKey(gdiBitmap.SourceKey, gdiBitmap.SourceKey);
                    gBack.DrawImage(gdiBitmap.Image, dest, sourceRegion.X,
                        sourceRegion.Y,
                        sourceRegion.Width, sourceRegion.Height,
                        GraphicsUnit.Pixel, attr);
                }
            }
            else
            {
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
                {
                    Rectangle dest = new Rectangle(x + sourceRegion.Width - 1,
                        y, 1, sourceRegion.Height);
                    Rectangle src = new Rectangle(sourceRegion.X, sourceRegion.Y,
                        1, sourceRegion.Height);
                    for (int i = 0; i < sourceRegion.Width; i++)
                    {
                        gBack.DrawImage(gdiBitmap.Image, dest.X, dest.Y, src,
                            GraphicsUnit.Pixel);
                        dest.X--;
                        src.X++;
                    }
                }
                else
                {
#if !DESKTOP
                    gBack.DrawImage(gdiBitmap.Image, x, y, sourceRegion,
                        GraphicsUnit.Pixel);
#else 
                    gBack.DrawImage(gdiBitmap.Image, x, y,
                        sourceRegion.Width, sourceRegion.Height);
#endif
                }
            }
        }

        /// <summary>
        /// Draw a filled rectangle to the back buffer.
        /// </summary>
        /// <param name="r">Rectangle to be filled</param>
        /// <param name="c">Color of rectangle</param>
        public void DrawFilledRect(Rectangle r, Color c)
        {
            gBack.FillRectangle(new SolidBrush(c), r);
        }

        /// <summary>
        /// Flip the back buffer to the display.
        /// </summary>
        public void Flip()
        {
            screen.DrawImage(back, 0, 0);
        }

        public void Flip(Rectangle rect)
        {
            screen.DrawImage(back, rect, rect, GraphicsUnit.Pixel);
        }

        public void Flip(List<Rectangle> listRect)
        {
            foreach (Rectangle i in listRect)
                screen.DrawImage(back, i, i, GraphicsUnit.Pixel);
        }

        /// <summary>
        /// Draw the string to the back buffer.
        /// </summary>
        /// <param name="x">X destination of text</param>
        /// <param name="y">Y destination of text</param>
        /// <param name="text">Text to be displayed</param>
        /// <param name="color">Color of text</param>
        /// <param name="font">Font to be used</param>
        /// <param name="options">Font draw options</param>
        public void DrawText(int x, int y, string text,
            Color color, IFont font, FontDrawOptions options)
        {
            // make sure the function is passed an appropriate implementation
            GdiFont gdiFont = null;
            try
            {
                gdiFont = (GdiFont)font;
            }
            catch (InvalidCastException e)
            {
                throw new ApplicationException(
                    "The font given was not created by" +
                    "this class' CreateFont() method.", e);
            }

            float drawX = (float)x;
            float drawY = (float)y;

            if ((options & FontDrawOptions.DrawTextCenter) != 0)
            {
                SizeF sSize = gBack.MeasureString(text, gdiFont.Font);
                drawX -= sSize.Width / 2.0F;
            }
            else if ((options & FontDrawOptions.DrawTextRight) != 0)
            {
                SizeF sSize = gBack.MeasureString(text, gdiFont.Font);
                drawX -= sSize.Width;
            }

            Brush brush = new SolidBrush(color);
            gBack.DrawString(text, gdiFont.Font, brush, drawX, drawY);

        }

        /// <summary>
        /// Draw options used for drawing bitmaps.
        /// </summary>
        DrawOptions drawOptions = 0;
        /// <summary>
        /// Set the current draw mode.
        /// </summary>
        /// <param name="options">options to be set</param>
        public void SetDrawOptions(DrawOptions options)
        {
            drawOptions |= options;
        }

        /// <summary>
        /// Clear the current draw mode of the specified options.
        /// </summary>
        /// <param name="options">options to be cleared</param>
        public void ClearDrawOptions(DrawOptions options)
        {
            drawOptions &= ~options;
        }

        /// <summary>
        /// Validate draw regions be clipping them to the screen.
        /// </summary>
        /// <param name="x">X destination</param>
        /// <param name="y">Y destination</param>
        /// <param name="sourceRegion">Source region</param>
        /// <returns>true if any part of the destination is drawable
        /// (on-screen), false otherwise</returns>
        public bool ValidateRegions(ref int x, ref int y, ref Rectangle sourceRegion)
        {
            if (x < 0)
            {
                sourceRegion.Width += x;
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) == 0)
                {
                    sourceRegion.X -= x;
                }

                x = 0;
            }
            else if (x >= ScreenWidth)
            {
                return false;
            }

            if (y < 0)
            {
                sourceRegion.Height += y;
                if ((drawOptions & DrawOptions.BlitMirrorUpDown) == 0)
                {
                    sourceRegion.Y -= y;
                }

                y = 0;
            }
            else if (y >= ScreenHeight)
            {
                return false;
            }

            if (x + sourceRegion.Width > ScreenWidth)
            {
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
                    sourceRegion.X += (sourceRegion.Width + x) - ScreenWidth;

                sourceRegion.Width -= (sourceRegion.Width + x) - ScreenWidth;
            }

            if (y + sourceRegion.Height > ScreenHeight)
            {
                if ((drawOptions & DrawOptions.BlitMirrorUpDown) != 0)
                    sourceRegion.Y += (sourceRegion.Height + y) - ScreenHeight;

                sourceRegion.Height -= (sourceRegion.Height + y) - ScreenHeight;
            }

            return true;
        }

        /// <summary>
        /// Creates a bitmap compatible with this graphics device
        /// </summary>
        /// <param name="fileName">The file to load the image from</param>
        /// <param name="transparent">True if the image should be drawn with
        /// alpha transparency</param>
        /// <returns>A bitmap compatible with this graphics device</returns>
        public IBitmap CreateBitmap(string fileName, bool transparent)
        {
            return new GdiBitmap(fileName, transparent);
        }

        public IBitmap CreateBitmap(System.IO.Stream stream, bool transparent)
        {
            return new GdiBitmap(stream, transparent);
        }

        public IBitmap CreateBitmap(Bitmap bmp, bool transparent)
        {
            return new GdiBitmap(bmp, transparent);
        }


        /// <summary>
        /// Creates a font object compatible with this graphics device
        /// </summary>
        /// <param name="fontName"></param>
        /// <returns>A font object compatible with this graphics device
        /// </returns>
        public IFont CreateFont(string fontName)
        {
            return new GdiFont(fontName);
        }
    }
}