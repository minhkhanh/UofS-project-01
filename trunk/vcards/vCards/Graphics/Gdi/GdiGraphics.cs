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
using System.IO;
using System.Collections.Generic;

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
        IImagingFactory imagingFactory = (IImagingFactory)Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid("327ABDA8-072B-11D3-9D7B-0000F81EF32E")));
        public IImage CreateIImage(string filename)
        {
            IImage iimg;
            imagingFactory.CreateImageFromFile(filename, out iimg);

            return iimg;
        }

        public IImage CreateIImage(Stream strm)
        {
            IImage iimg;
            imagingFactory.CreateImageFromStream(strm, out iimg);

            return iimg;
        }

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

        public void DrawImageTransparent(IBitmap ibmp, Rectangle srcRect, int x, int y)
        {
            GdiBitmap gdiBitmap = null;
            try
            {
                gdiBitmap = (GdiBitmap)ibmp;
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
        /// Ve anh len mot vung nao do voi mau nen trong suot. Anh se tu dong bien doi cho phu hop voi vung can ve
        /// </summary>
        /// <param name="image"></param>
        /// <param name="destRect"></param>
        public void DrawImageTransparent(IBitmap ibmp, Rectangle destRect)
        {
            GdiBitmap gdiBitmap = null;
            try
            {
                gdiBitmap = (GdiBitmap)ibmp;
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

        public void DrawImageAlphaChannel(IImage image, int x, int y)
        {
            ImageInfo imgInfo;
            image.GetImageInfo(out imgInfo);
            Rectangle desRect = new Rectangle(x, y, (int)imgInfo.Width+x, (int)imgInfo.Height+y);
            Rectangle rectSrc = new Rectangle(0, 0, (int)imgInfo.Width, (int)imgInfo.Height);

            IntPtr hdc = gBack.GetHdc();
            image.Draw(hdc, ref desRect, ref rectSrc);
            gBack.ReleaseHdc(hdc);  // !!! phai thuc hien thao tac Release nay!
        }

        public void DrawImageAlphaChannel(IImage image, Rectangle dest)
        {
            IntPtr hdc = gBack.GetHdc();
            
            ImageInfo imgInfo;
            image.GetImageInfo(out imgInfo);
            Rectangle rectSrc = new Rectangle(0, 0, (int)imgInfo.Width, (int)imgInfo.Height);

            image.Draw(hdc, ref dest, ref rectSrc);

            gBack.ReleaseHdc(hdc);  // !!! phai thuc hien thao tac Release nay!
        }

        public void DrawImageAlphaChannel(IImage image, Rectangle dest, Rectangle src)
        {
            ImageInfo imgInfo;
            image.GetImageInfo(out imgInfo);

            IntPtr hdc = gBack.GetHdc();

            src.X = src.X * (2540 / (int)imgInfo.Xdpi);
            src.Y = src.Y * (2540 / (int)imgInfo.Ydpi);
            src.Width = src.Width * (2540 / (int)imgInfo.Xdpi);
            src.Height = src.Height * (2540 / (int)imgInfo.Ydpi);

            image.Draw(hdc, ref dest, ref src); // !!! xem lai src (tinh bang don vi DPI)

            gBack.ReleaseHdc(hdc);  // !!! phai thuc hien thao tac Release nay!
        }

        public void AlphaBlend(byte alpha, IBitmap ibmp, int x, int y)
        {
            Graphics gSrc = Graphics.FromImage(((GdiBitmap)ibmp).Image);

            IntPtr hdcSrc = gSrc.GetHdc();
            IntPtr hdcDes = gBack.GetHdc();

            BlendFunction blendFunction = new BlendFunction();
            blendFunction.BlendOp = (byte)BlendOperation.AC_SRC_OVER;   // Only supported blend operation
            blendFunction.BlendFlags = (byte)BlendFlags.Zero;           // Documentation says put 0 here
            blendFunction.SourceConstantAlpha = (byte)alpha;            // Constant alpha factor
            blendFunction.AlphaFormat = (byte)0;                        // Don't look for per pixel alpha

            PlatformAPIs.AlphaBlend(hdcDes, x, y, ibmp.Width, ibmp.Height, hdcSrc, 0, 0, ibmp.Width, ibmp.Height, blendFunction);

            gSrc.ReleaseHdc(hdcSrc);
            gBack.ReleaseHdc(hdcDes);
        }

        public void AlphaBlend(byte alpha, IBitmap ibmp, Rectangle dest)
        {
            Graphics gSrc = Graphics.FromImage(((GdiBitmap)ibmp).Image);

            IntPtr hdcSrc = gSrc.GetHdc();
            IntPtr hdcDes = gBack.GetHdc();

            BlendFunction blendFunction = new BlendFunction();
            blendFunction.BlendOp = (byte)BlendOperation.AC_SRC_OVER;   // Only supported blend operation
            blendFunction.BlendFlags = (byte)BlendFlags.Zero;           // Documentation says put 0 here
            blendFunction.SourceConstantAlpha = (byte)alpha;            // Constant alpha factor
            blendFunction.AlphaFormat = (byte)0;                        // Don't look for per pixel alpha

            PlatformAPIs.AlphaBlend(hdcDes, dest.X, dest.Y, dest.Width, dest.Height, hdcSrc, 0, 0, ibmp.Width, ibmp.Height, blendFunction);

            gSrc.ReleaseHdc(hdcSrc);
            gBack.ReleaseHdc(hdcDes);
        }

        public void AlphaBlend(byte alpha, IBitmap ibmp, Rectangle dest, Rectangle src)
        {
            Graphics gSrc = Graphics.FromImage(((GdiBitmap)ibmp).Image);

            IntPtr hdcSrc = gSrc.GetHdc();
            IntPtr hdcDes = gBack.GetHdc();

            BlendFunction blendFunction = new BlendFunction();
            blendFunction.BlendOp = (byte)BlendOperation.AC_SRC_OVER;   // Only supported blend operation
            blendFunction.BlendFlags = (byte)BlendFlags.Zero;           // Documentation says put 0 here
            blendFunction.SourceConstantAlpha = (byte)alpha;            // Constant alpha factor
            blendFunction.AlphaFormat = (byte)0;                        // Don't look for per pixel alpha

            PlatformAPIs.AlphaBlend(hdcDes, dest.X, dest.Y, dest.Width, dest.Height, hdcSrc, src.X, src.Y, src.Width, src.Height, blendFunction);

            gSrc.ReleaseHdc(hdcSrc);
            gBack.ReleaseHdc(hdcDes);
        }

        public void DrawAnimation(int x, int y, Rectangle rectSrc, Animation animation)
        {
            animation.Draw(this, x, y, rectSrc);
        }

        public void DrawAnimationScale(int x, int y, int w, int h, Animation animation)
        {
            animation.Draw(this, x, y, w, h);
        }


        ///  
        /// Draw the current cell of the animation to the back buffer. 
        ///  
        /// X destination of the draw 
        /// Y destination of the draw 
        /// Animation to be drawn 
        public void DrawAnimation(int x, int y, Animation animation)
        {
            animation.Draw(this, x, y);
        }

        public void DrawBitmap(Rectangle rectDest, IBitmap ibmp)
        {
            DrawBitmap(new Rectangle(0, 0, ibmp.Width, ibmp.Height), rectDest, ibmp);
        }

        public void DrawBitmap(int x, int y, IBitmap bmp)
        {
            DrawBitmap(x, y, new Rectangle(0, 0, bmp.Width, bmp.Height), bmp);
        }

        public void DrawBitmap(Rectangle sourceRegion, Rectangle destRect, 
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
            int x = destRect.X;      // temp variable for function param, not used
            int y = destRect.Y;      // temp variable for function param, not used

            if (!ValidateRegions(ref x, ref y, ref destRect))
                return;

            //if (!ValidateRegions(ref x, ref y, ref sourceRegion))
            //    return;

            // Draw the bitmap 
            if (gdi_bmp.Transparent)
            {
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
                {
                    //Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                    //    sourceRegion.Height);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetColorKey(gdi_bmp.SourceKey, gdi_bmp.SourceKey);
                    gBack.DrawImage(gdi_bmp.Image, destRect, sourceRegion.X +
                        sourceRegion.Width,
                        sourceRegion.Y, -sourceRegion.Width, sourceRegion.Height,
                        GraphicsUnit.Pixel, attr);
                }
                else
                {
                    //Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                    //    sourceRegion.Height);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetColorKey(gdi_bmp.SourceKey, gdi_bmp.SourceKey);
                    gBack.DrawImage(gdi_bmp.Image, destRect, sourceRegion.X,
                        sourceRegion.Y,
                        sourceRegion.Width, sourceRegion.Height,
                        GraphicsUnit.Pixel, attr);
                }
            }
            else
            {
                if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
                {
                    //Rectangle dest = new Rectangle(x + sourceRegion.Width - 1,
                    //    y, 1, sourceRegion.Height);
                    //Rectangle src = new Rectangle(sourceRegion.X, sourceRegion.Y,
                    //    1, sourceRegion.Height);
                    //for (int i = 0; i < sourceRegion.Width; i++)
                    //{
                    //    gBack.DrawImage(gdi_bmp.Image, dest.X, dest.Y, src,
                    //        GraphicsUnit.Pixel);
                    //    dest.X--;
                    //    src.X++;
                    //}

                    ImageAttributes attr = new ImageAttributes();
                    attr.ClearColorKey();
                    //attr.SetColorKey(gdi_bmp.SourceKey, gdi_bmp.SourceKey);
                    gBack.DrawImage(gdi_bmp.Image, destRect,
                        sourceRegion.X + sourceRegion.Width,
                        sourceRegion.Y, -sourceRegion.Width, sourceRegion.Height,
                        GraphicsUnit.Pixel, attr);
                }
                else
                {
#if !DESKTOP
                    gBack.DrawImage(gdi_bmp.Image, destRect, sourceRegion,
                        GraphicsUnit.Pixel);
#else  
                    gBack.DrawImage(gdi_bmp.Image, destRect, 
                        sourceRegion.Width, sourceRegion.Height); 
#endif
                }
            }
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

        public void Flip(Rectangle rect)
        {
            screen.DrawImage(back, rect, new Rectangle(0,0,back.Width, back.Height), GraphicsUnit.Pixel);
        }

        public void Flip(List<Rectangle> listRect)
        {
            foreach (Rectangle i in listRect)
            {
                screen.DrawImage(back, i, new Rectangle(0, 0, back.Width, back.Height), GraphicsUnit.Pixel);
            }
        }

        ///  
        /// Flip the back buffer to the display. 
        ///  
        public void Flip()
        {
            screen.DrawImage(back, 0, 0);
        }

        public void DrawString(string text, IFont font, Brush brush, Rectangle textRect)
        {
            gBack.DrawString(text, ((GdiFont)font).Font, brush, textRect);
        }

        public void DrawText(Rectangle rectText, string text, Color color, IFont font, FontDrawOptions options)
        {
            StringFormat stringFormat = new StringFormat();

            if ((options & FontDrawOptions.DrawTextCenter) != 0)
                stringFormat.Alignment = StringAlignment.Center;
            else if ((options & FontDrawOptions.DrawTextLeft) != 0)
                stringFormat.Alignment = StringAlignment.Near;
            else if ((options & FontDrawOptions.DrawTextRight) != 0)
                stringFormat.Alignment = StringAlignment.Far;

            if ((options & FontDrawOptions.DrawTextTop) != 0)
                stringFormat.LineAlignment = StringAlignment.Near;
            else if ((options & FontDrawOptions.DrawTextBottom) != 0)
                stringFormat.LineAlignment = StringAlignment.Far;
            else if ((options & FontDrawOptions.DrawTextMiddle) != 0)
                stringFormat.LineAlignment = StringAlignment.Center;

            gBack.DrawString(text, ((GdiFont)font).Font, new SolidBrush(color), rectText, stringFormat);
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

        public IBitmap CreateBitmap(Stream stream, bool transparent)
        {
            return new GdiBitmap(stream, transparent);
        }

        public IBitmap CreateBitmap(System.Drawing.Bitmap bmp, bool transparent)
        {
            return new GdiBitmap(bmp, transparent);
        }

        public IBitmap CreateBitmap(IBitmap ibmp)
        {
            GdiBitmap gdiBmp = (GdiBitmap)ibmp;
            return new GdiBitmap(gdiBmp);
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

        public IFont CreateFont(string fontName, float fontSize, FontStyle fontStyle)
        {
            return new GdiFont(fontName, fontSize, fontStyle);
        }
    }
}
