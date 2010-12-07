using System;
using System.Drawing;
namespace VCard
{
    [FlagsAttribute]
    public enum FontDrawOptions
    {
        DrawTextCenter = 0x0,
        DrawTextRight = 0x1,
        DrawTextLeft = 0x2
    }
    public interface IFont
    {
        void Dispose();
    }
}