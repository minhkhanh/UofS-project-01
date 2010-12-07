using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace _0812239
{
    public interface IBitmap : IDisposable
    {
        int Height { get; }
        Color KeyColor { get; set; }
        bool Transparent { get; set; }
        int Width { get; }
    }
}
