using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

#if DESKTOP
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
#else
using Microsoft.WindowsMobile.DirectX;
using Microsoft.WindowsMobile.DirectX.Direct3D;
#endif

namespace vCards
{
    public class DirectXGraphics : IGraphics
    {
        ///  
        /// The rendering device for D3D 
        ///  
        Device device;

        ///  
        /// A buffer of vertex data for colored (non-textured) drawing 
        /// operations 
        ///  
        VertexBuffer vbCol;

        ///  
        /// A buffer of vertex data for textured drawing operations 
        ///  
        VertexBuffer vbTex;

        ///  
        /// The fixed height of our rendering area 
        ///  
        private static int Width = 240;

        ///  
        /// The fixed width of our rendering area 
        ///  
        private static int Height = 320;

        public DirectXGraphics(Control ctrl)
        {
            Pool vertexBufferPool;

            // Setup D3D parameters 
            PresentParameters presentParams = new PresentParameters();
#if !DESKTOP
            presentParams.Windowed = false;
            presentParams.SwapEffect = SwapEffect.Discard;
            presentParams.BackBufferCount = 1;
            presentParams.BackBufferFormat = Format.R5G6B5;
            presentParams.BackBufferWidth = Width;
            presentParams.BackBufferHeight = Height;
            device = new Device(0, DeviceType.Default, ctrl,
                CreateFlags.None, presentParams);
#else 
            presentParams.Windowed = true; 
            presentParams.SwapEffect = SwapEffect.Discard; 
            device = new Device(0, DeviceType.Hardware, ctrl, 
                CreateFlags.SoftwareVertexProcessing, presentParams); 
#endif
            device.RenderState.AlphaTestEnable = true;
            device.RenderState.AlphaFunction = Compare.NotEqual;
            device.RenderState.ReferenceAlpha = 0;

#if !DESKTOP
            // Get the device capabilities 

            Caps caps;
            caps = device.DeviceCaps;

            if (caps.SurfaceCaps.SupportsVidVertexBuffer)
                vertexBufferPool = Pool.VideoMemory;
            else
                vertexBufferPool = Pool.SystemMemory;
#else 
            vertexBufferPool = Pool.SystemMemory; 
#endif

            vbCol = new VertexBuffer(
                typeof(CustomVertex.TransformedColored), 4, device,
                0, CustomVertex.TransformedColored.Format, vertexBufferPool);
            vbTex = new VertexBuffer(
                typeof(CustomVertex.TransformedTextured), 4, device,
                0, CustomVertex.TransformedTextured.Format,
                vertexBufferPool);

            // Clear the backbuffer to a blue color  
            device.Clear(ClearFlags.Target, System.Drawing.Color.Blue,
                1.0f, 0);
            // Begin the scene 
            device.BeginScene();
        }


        #region IGraphics Members

        ///  
        /// Gets the width of the screen. 
        ///  
        public int ScreenWidth
        {
            get
            {
                return Width;
            }
        }

        ///  
        /// Gets the height of the screen. 
        ///  
        public int ScreenHeight
        {
            get
            {
                return Height;
            }
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

        public void DrawBitmap(int x, int y, IBitmap bmp)
        {
            Rectangle rectSrc = new Rectangle(0, 0, bmp.Width, bmp.Height);

            DrawBitmap(x, y, rectSrc, bmp);
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
            DirectXBitmap dx_bmp = null;
            try
            {
                dx_bmp = (DirectXBitmap)bmp;
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

            // determine texture coordinates so that 
            // the there is a 1-1 mapping between texels and screen pixels 
            Rectangle dest = new Rectangle(x, y, sourceRegion.Width,
                sourceRegion.Height);
            RectangleF tex_rect = new RectangleF(
                ((float)sourceRegion.X + 0.5F) / dx_bmp.Width,
                ((float)sourceRegion.Y + 0.5F) / dx_bmp.Height,
                ((float)sourceRegion.Width + 0.5F) / dx_bmp.Width,
                ((float)sourceRegion.Height + 0.5F) / dx_bmp.Height);


            // load the vertex buffer with data for the two triangles 
            // in the rectangle 
            GraphicsStream stm = vbTex.Lock(0, 0, 0);
            CustomVertex.TransformedTextured[] verts =
                new CustomVertex.TransformedTextured[4];

            if ((drawOptions & DrawOptions.BlitMirrorLeftRight) == 0)
            {
                verts[0].X = dest.Right;
                verts[0].Y = dest.Top;
                verts[0].Z = 0.5f;
                verts[0].Rhw = 1;
                verts[0].Tu = tex_rect.Right;
                verts[0].Tv = tex_rect.Top;
                verts[1].X = dest.Right;
                verts[1].Y = dest.Bottom;
                verts[1].Z = 0.5f;
                verts[1].Rhw = 1;
                verts[1].Tu = tex_rect.Right;
                verts[1].Tv = tex_rect.Bottom;
                verts[2].X = dest.Left;
                verts[2].Y = dest.Top;
                verts[2].Z = 0.5f;
                verts[2].Rhw = 1;
                verts[2].Tu = tex_rect.Left;
                verts[2].Tv = tex_rect.Top;
                verts[3].X = dest.Left;
                verts[3].Y = dest.Bottom;
                verts[3].Z = 0.5f;
                verts[3].Rhw = 1;
                verts[3].Tu = tex_rect.Left;
                verts[3].Tv = tex_rect.Bottom;
            }
            else
            {
                verts[0].X = dest.Right;
                verts[0].Y = dest.Top;
                verts[0].Z = 0.5f;
                verts[0].Rhw = 1;
                verts[0].Tu = tex_rect.Left;
                verts[0].Tv = tex_rect.Top;
                verts[1].X = dest.Right;
                verts[1].Y = dest.Bottom;
                verts[1].Z = 0.5f;
                verts[1].Rhw = 1;
                verts[1].Tu = tex_rect.Left;
                verts[1].Tv = tex_rect.Bottom;
                verts[2].X = dest.Left;
                verts[2].Y = dest.Top;
                verts[2].Z = 0.5f;
                verts[2].Rhw = 1;
                verts[2].Tu = tex_rect.Right;
                verts[2].Tv = tex_rect.Top;
                verts[3].X = dest.Left;
                verts[3].Y = dest.Bottom;
                verts[3].Z = 0.5f;
                verts[3].Rhw = 1;
                verts[3].Tu = tex_rect.Right;
                verts[3].Tv = tex_rect.Bottom;
            }

            stm.Write(verts);
            vbTex.Unlock();

            // bind the texture to next drawing operation 
            device.SetTexture(0, dx_bmp.Texture);

            // bind the vertex data to the next drawing operation 
            device.SetStreamSource(0, vbTex, 0);
#if DESKTOP 
                device.VertexFormat = 
                    CustomVertex.TransformedTextured.Format; 
#endif
            // perform the draw 
            device.DrawPrimitives(PrimitiveType.TriangleStrip, 0, 2);
        }

        ///  
        /// Draw a filled rectangle to the back buffer. 
        ///  
        /// Rectangle to be filled 
        /// Color of rectangle 
        public void DrawFilledRect(Rectangle r, Color c)
        {
            // fill the vertex buffer with the correct vertices 
            GraphicsStream stm = vbCol.Lock(0, 0, 0);
            CustomVertex.TransformedColored[] verts =
                new CustomVertex.TransformedColored[4];

            verts[0].X = r.Left;
            verts[0].Y = r.Bottom;
            verts[0].Z = 0.5f;
            verts[0].Rhw = 1;
            verts[0].Color = c.ToArgb();
            verts[1].X = r.Left;
            verts[1].Y = r.Top;
            verts[1].Z = 0.5f;
            verts[1].Rhw = 1;
            verts[1].Color = c.ToArgb();
            verts[2].X = r.Right;
            verts[2].Y = r.Top;
            verts[2].Z = 0.5f;
            verts[2].Rhw = 1;
            verts[2].Color = c.ToArgb();
            verts[3].X = r.Right;
            verts[3].Y = r.Bottom;
            verts[3].Z = 0.5f;
            verts[3].Rhw = 1;
            verts[3].Color = c.ToArgb();
            stm.Write(verts);
            vbCol.Unlock();

            // bind the vertex data to the next drawing operation 
            device.SetStreamSource(0, vbCol, 0);
#if DESKTOP 
            device.VertexFormat = CustomVertex.TransformedColored.Format; 
#endif
            // draw the triangles 
            device.DrawPrimitives(PrimitiveType.TriangleFan, 0, 2);
        }


        ///  
        /// Flip the back buffer to the display. 
        ///  
        public void Flip()
        {
            if (device == null)
                return;

            // End the current rendering 
            device.EndScene();
            device.Present();

            // Start a new rendering... 
            // Clear the backbuffer to a blue color  
            device.Clear(ClearFlags.Target, System.Drawing.Color.Blue,
                1.0f, 0);
            // Begin the scene 
            device.BeginScene();
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
        public void DrawText(int x, int y, string text, Color color,
            IFont font, FontDrawOptions options)
        {
            // make sure the function is passed an appropriate implementation 
            DirectXFont dx_font = null;
            try
            {
                dx_font = (DirectXFont)font;
            }
            catch (InvalidCastException e)
            {
                throw new ApplicationException(
                    "The font given was not created by" +
                    "this class' CreateFont() method.", e);
            }

            // determine the rectangle to draw in 
            Rectangle rect = new Rectangle();
#if DESKTOP 
            dx_font.Font.DrawText(null, text, ref rect, 
                DrawTextFormat.CalculateRect, color); 
#else
            dx_font.Font.MeasureString(null, text, ref rect, 0);
#endif
            rect.Y = y;
            rect.X = 0;
            rect.Width = ScreenWidth;

            // set options for the DrawText call 
            DrawTextFormat drawOptions;
            if (options == FontDrawOptions.DrawTextCenter)
                drawOptions = DrawTextFormat.Center;
            else if (options == FontDrawOptions.DrawTextLeft)
                drawOptions = DrawTextFormat.Left;
            else
                drawOptions = DrawTextFormat.Right;

            dx_font.Font.DrawText(null, text, rect, drawOptions, color);
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
            Rectangle clipped_src = new Rectangle(sourceRegion.X, sourceRegion.Y,
                sourceRegion.Width, sourceRegion.Height);
            if (x < 0)
            {
                if (x + sourceRegion.Width < 0) return false;
                clipped_src.Width += x;
                clipped_src.X -= x;
                x = 0;
            }
            else if (x >= ScreenWidth)
            {
                return false;
            }

            if (y < 0)
            {
                if (y + sourceRegion.Height < 0) return false;
                clipped_src.Height += y;
                clipped_src.Y -= y;
                y = 0;
            }
            else if (y >= ScreenHeight)
            {
                return false;
            }

            if (x + sourceRegion.Width > ScreenWidth)
            {
                clipped_src.Width -= (x + sourceRegion.Width) - ScreenWidth;
            }

            if (y + sourceRegion.Height > ScreenHeight)
            {
                clipped_src.Height -= (y + sourceRegion.Height) - ScreenHeight;
            }

            if ((drawOptions & DrawOptions.BlitMirrorLeftRight) != 0)
            {
                sourceRegion.X = sourceRegion.X + sourceRegion.Width -
                    (clipped_src.X - sourceRegion.X) - clipped_src.Width;
            }
            else
            {
                sourceRegion.X = clipped_src.X;
            }

            sourceRegion.Width = clipped_src.Width;
            sourceRegion.Y = clipped_src.Y;
            sourceRegion.Height = clipped_src.Height;

            return true;
        }

        ///  
        /// Creates a bitmap compatible with this graphics device 
        ///  
        /// The file to load the image from 
        /// True if the image should be drawn 
        /// with alpha transparency 
        /// A bitmap compatible with this graphics device 
        public IBitmap CreateBitmap(string fileName, bool transparent)
        {
            return new DirectXBitmap(fileName, device, transparent);
        }


        ///  
        /// Creates a font object compatible with this graphics device 
        ///  
        ///  
        /// A font object compatible with this graphics device 
        ///  
        public IFont CreateFont(string fontName)
        {
            return new DirectXFont(fontName, device);
        }

        #endregion

        #region IDisposable Members

        public void Dispose()
        {
            device.Dispose();
        }

        #endregion

    }
}
