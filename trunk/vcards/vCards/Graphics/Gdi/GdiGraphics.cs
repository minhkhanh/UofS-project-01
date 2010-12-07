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
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

//#if DESKTOP 
//using Microsoft.DirectX; 
//using Microsoft.DirectX.Direct3D; 
//#else
//using Microsoft.WindowsMobile.DirectX;
//using Microsoft.WindowsMobile.DirectX.Direct3D;
//#endif

namespace vCards
{
    ///  
    /// A GDI implementation of the IGraphics 
    ///  
    public class GdiGraphics : IGraphics
    {

        ///  
        /// Gets the width of the screen. 
        ///  
        public int ScreenWidth
        {
            get { return back.Width; }
        }

        ///  
        /// Gets the height of the screen. 
        ///  
        public int ScreenHeight
        {
            get { return back.Height; }
        }

        ///  
        /// Represents the back buffer. 
        ///  
        Bitmap back = null;

        ///  
        /// Graphics object associated with the back buffer. 
        ///  
        Graphics gBack = null;

        ///  
        /// Graphics object associated with the screen / owner control. 
        ///  
        Graphics screen = null;

        ///  
        /// Initialize the graphics engine. 
        ///  
        /// Owner control (Form) 
        public GdiGraphics(Control owner)
        {
            back = new Bitmap(owner.ClientSize.Width, owner.ClientSize.Height); // ? back = new Bitmap(240, 320);
            gBack = Graphics.FromImage(back);
            screen = owner.CreateGraphics();
        }

        ///  
        /// Empty.  Provided for compatibility. 
        ///  
        public void Dispose()
        {
            screen.Dispose();
        }

        ///  
        /// Draw the current cell of the animation to the back buffer. 
        ///  
        /// X destination of the draw 
        /// Y destination of the draw 
        /// Animation to be drawn 
        public void DrawAnimation(int x, int y, Animation animation)
        {
            DrawBitmap(x, y, animation.Region, animation.Image);
        }

        ///  
        /// Draw the bitmap to the back buffer. 
        ///  
        /// X destination of the draw 
        /// Y destination of the draw 
        /// Source region of the draw 
        /// Bitmap to be drawn 
        public void DrawBitmap(int x, int y, Rectangle sourceRegion,
            IBitmap bmp)
        {
            // make sure the function is passed an appropriate implementation 
            GdiBitmap gdi_bmp = null;
            try
            {
                gdi_bmp = (GdiBitmap)bmp;
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
            if (gdi_bmp.Transparent)
            {
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
                {
                    Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                        sourceRegion.Height);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetColorKey(gdi_bmp.SourceKey, gdi_bmp.SourceKey);
                    gBack.DrawImage(gdi_bmp.Image, dest, sourceRegion.X +
                        sourceRegion.Width,
                        sourceRegion.Y, -sourceRegion.Width, sourceRegion.Height,
                        GraphicsUnit.Pixel, attr);
                }
                else
                {
                    Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                        sourceRegion.Height);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetColorKey(gdi_bmp.SourceKey, gdi_bmp.SourceKey);
                    gBack.DrawImage(gdi_bmp.Image, dest, sourceRegion.X,
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
                        gBack.DrawImage(gdi_bmp.Image, dest.X, dest.Y, src,
                            GraphicsUnit.Pixel);
                        dest.X--;
                        src.X++;
                    }
                }
                else
                {
#if !DESKTOP
                    gBack.DrawImage(gdi_bmp.Image, x, y, sourceRegion,
                        GraphicsUnit.Pixel);
#else  
                    gBack.DrawImage(gdi_bmp.Image, x, y, 
                        sourceRegion.Width, sourceRegion.Height); 
#endif
                }
            }
        }

        ///  
        /// Draw a filled rectangle to the back buffer. 
        ///  
        /// Rectangle to be filled 
        /// Color of rectangle 
        public void DrawFilledRect(Rectangle r, Color c)
        {
            gBack.FillRectangle(new SolidBrush(c), r);
        }

        ///  
        /// Flip the back buffer to the display. 
        ///  
        public void Flip()
        {
            screen.DrawImage(back, 0, 0);
        }

        ///  
        /// Draw the string to the back buffer. 
        ///  
        /// X destination of text 
        /// Y destination of text 
        /// Text to be displayed 
        /// Color of text 
        /// Font to be used 
        /// Font draw options 
        public void DrawText(int x, int y, string text,
            Color color, IFont font, FontDrawOptions options)
        {
            // make sure the function is passed an appropriate implementation 
            GdiFont gdi_font = null;
            try
            {
                gdi_font = (GdiFont)font;
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
                SizeF sSize = gBack.MeasureString(text, gdi_font.Font);
                drawX -= sSize.Width / 2.0F;
            }
            else if ((options & FontDrawOptions.DrawTextRight) != 0)
            {
                SizeF sSize = gBack.MeasureString(text, gdi_font.Font);
                drawX -= sSize.Width;
            }

            Brush brush = new SolidBrush(color);
            gBack.DrawString(text, gdi_font.Font, brush, drawX, drawY);

        }

        ///  
        /// Draw options used for drawing bitmaps. 
        ///  
        DrawOptions drawOptions = 0;
        ///  
        /// Set the current draw mode. 
        ///  
        /// options to be set 
        public void SetDrawOptions(DrawOptions options)
        {
            drawOptions |= options;
        }

        ///  
        /// Clear the current draw mode of the specified options. 
        ///  
        /// options to be cleared 
        public void ClearDrawOptions(DrawOptions options)
        {
            drawOptions &= ~options;
        }

        ///  
        /// Validate draw regions be clipping them to the screen. 
        ///  
        /// X destination 
        /// Y destination 
        /// Source region 
        /// true if any part of the destination is drawable 
        /// (on-screen), false otherwise 
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

        ///  
        /// Creates a bitmap compatible with this graphics device 
        ///  
        /// The file to load the image from 
        /// True if the image should be drawn with 
        /// alpha transparency 
        /// A bitmap compatible with this graphics device 
        public IBitmap CreateBitmap(string fileName, bool transparent)
        {
            return new GdiBitmap(fileName, transparent);
        }


        ///  
        /// Creates a font object compatible with this graphics device 
        ///  
        ///  
        /// A font object compatible with this graphics device 
        ///  
        public IFont CreateFont(string fontName)
        {
            return new GdiFont(fontName);
        }
    }
}
