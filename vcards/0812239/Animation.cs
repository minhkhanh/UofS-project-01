using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace _0812239
{
    public class Animation
    {
        IBitmap _ibitmImage;
        public IBitmap Image { get; set; }

        Rectangle _rectRegion;
        public Rectangle Region { get; set; }

        int _iCellNumber;
        public int NumberCells { get; set; }

        int _iCellWidth;
        public int CellWidth { get; set; }

        int _iCellHeight;
        public int CellHeight { get; set; }

        int _iCurCell;
        public int CurCell { get; set; }

        public void Dispose()
        {
            _ibitmImage.Dispose();
        }
    }
}
