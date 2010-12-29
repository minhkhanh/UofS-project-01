using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Drawing;

namespace vCards
{
    public class TransAnimation : Animation
    {
        ///  
        /// Transparent image to be used for animating. 
        ///  
        public IImage IImgImage { get { return iimgImage; } }
        IImage iimgImage;

        public TransAnimation(string fileName, IImagingFactory fac, int numberRows,
            int numberColumns, int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond)
            : base(numberRows, numberColumns, startCell, cellWidth, cellHeight, cellsPerSecond)
        {
            // Load and initialize the Bitmap object 
            fac.CreateImageFromFile(fileName, out iimgImage);
            if (iimgImage == null)
            {
                initialized = false;
                return;
            }

            allocated = true;
        }

        public TransAnimation(Stream filestream, IImagingFactory fac, int numberRows,
            int numberColumns, int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond) :
            base(numberRows, numberColumns, startCell, cellWidth, cellHeight, cellsPerSecond)
        {
            // Load and initialize the Bitmap object 
            //fac.CreateImageFromStream(filestream, out iimgImage);
            if (iimgImage == null)
            {
                initialized = false;
                return;
            }

            allocated = true;
        }

        public TransAnimation(IImage iimg, int numberRows,
            int numberColumns, int startCell, int cellWidth, int cellHeight,
            int cellsPerSecond)
            : base(numberRows, numberColumns, startCell, cellWidth, cellHeight, cellsPerSecond)
        {
            // Load and initialize the Bitmap object 
            iimgImage = iimg;
            if (iimgImage == null)
            {
                initialized = false;
                return;
            }

            allocated = true;
        }

        public override void Draw(IGraphics igp, int x, int y, int w, int h)
        {
            //igp.DrawImageAlphaChannel(iimgImage, new RECT(x, y, w, h), new RECT(Region));
        }

        public override void Draw(IGraphics igp, int x, int y, Rectangle rectSrc)
        {
            rectSrc.X += Region.X;
            rectSrc.Y += Region.Y;

            //igp.DrawImageAlphaChannel(iimgImage, new RECT(x, y, rectSrc.Width, rectSrc.Height), new RECT(rectSrc));
        }

        public override void Draw(IGraphics igp, int x, int y)
        {
            //igp.DrawImageAlphaChannel(iimgImage, new RECT(x, y, CellWidth, CellHeight), new RECT(Region));
        }

        public override void Dispose()
        {
            if (!allocated)
                return;

            //if (iimgImage != null)
            //    iimgImage.Dispose();
        }
    }
}
