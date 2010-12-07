using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;

namespace vCards
{
    ///  
    /// Draw modes 
    ///  
    [FlagsAttribute]
    public enum FontDrawOptions
    {
        None = 0,
        DrawTextLeft = 0x0001,
        DrawTextCenter = 0x0002,
        DrawTextRight = 0x0004
    }


    public interface IFont
    {
        void Dispose();
    }
}
