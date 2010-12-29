using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Drawing;

namespace vCards
{
    public class BmpAnimation : Animation
    {
        ///  
        /// Bitmap to be used for animating. 
        ///  
        public IBitmap IBmpImage { get { return ibmpImage; } }
        IBitmap ibmpImage;

        public BmpAnimation(string fileName, IGraphics graphics, int numberRows,
            int numberColumns, int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond)
            : base(numberRows, numberColumns, startCell, cellWidth, cellHeight, cellsPerSecond)
        {
            // Load and initialize the Bitmap object 
            ibmpImage = graphics.CreateBitmap(fileName, true);
            if (ibmpImage == null)
            {
                initialized = false;
                return;
            }

            allocated = true;
        }

        public BmpAnimation(Stream filestream, IGraphics graphics, int numberRows,
            int numberColumns, int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond)
            : base(numberRows, numberColumns, startCell, cellWidth, cellHeight, cellsPerSecond)
        {
            // Load and initialize the Bitmap object 
            ibmpImage = graphics.CreateBitmap(filestream, true);
            if (ibmpImage == null)
            {
                initialized = false;
                return;
            }

            allocated = true;
        }

        public BmpAnimation(IBitmap ibmp, int numberRows,
            int numberColumns, int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond)
            : base(numberRows, numberColumns, startCell, cellWidth, cellHeight, cellsPerSecond)
        {
            // Load and initialize the Bitmap object 
            ibmpImage = ibmp;
            if (ibmpImage == null)
            {
                initialized = false;
                return;
            }

            allocated = true;
        }

        public override void Draw(IGraphics igp, int x, int y, int w, int h)
        {
            igp.DrawBitmap(Region, new Rectangle(x, y, w, h), ibmpImage);
        }

        public override void Draw(IGraphics igp, int x, int y, Rectangle rectSrc)
        {
            rectSrc.X += Region.X;
            rectSrc.Y += Region.Y;

            igp.DrawBitmap(x, y, rectSrc, ibmpImage);
        }

        public override void Draw(IGraphics igp, int x, int y)
        {
            igp.DrawBitmap(x, y, Region, ibmpImage);
        }

        public override void Dispose()
        {
            if (!allocated)
                return;

            if (ibmpImage != null)
                ibmpImage.Dispose();
        }
    }
}
