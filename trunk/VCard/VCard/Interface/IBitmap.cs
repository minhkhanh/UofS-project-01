using System;
using System.Drawing;
namespace VCard
{
    public enum DrawOptions
    {
        None = 0,
        BlitKeyedTransparency = 0x0001,
        BlitMirrorLeftRight = 0x0010,       // ve chieu nguoc lai trai-phai
        BlitMirrorUpDown = 0x0020           // ve chieu nguoc lai tren-duoi
    }
    public interface IBitmap : IDisposable
    {
        int Height { get; }
        Color SourceKey { get; set; }
        bool Transparent { get; set; }
        int Width { get; }
    }
}