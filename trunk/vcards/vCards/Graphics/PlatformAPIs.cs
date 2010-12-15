using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace vCards
{
    public struct BlendFunction
    {
        public byte BlendOp;
        public byte BlendFlags;
        public byte SourceConstantAlpha;
        public byte AlphaFormat;
    }

    public enum BlendOperation : byte
    {
        AC_SRC_OVER = 0x00
    }

    public enum BlendFlags : byte
    {
        Zero = 0x00
    }

    public enum SourceConstantAlpha : byte
    {
        Transparent = 0x00,
        Opaque = 0xFF
    }

    public enum AlphaFormat : byte
    {
        AC_SRC_ALPHA = 0x01
    }

    public class PlatformAPIs
    {
        [DllImport("coredll.dll")]
        extern public static Int32 AlphaBlend(IntPtr hdcDest,
                                              Int32 xDest,
                                              Int32 yDest,
                                              Int32 cxDest,
                                              Int32 cyDest,
                                              IntPtr hdcSrc,
                                              Int32 xSrc,
                                              Int32 ySrc,
                                              Int32 cxSrc,
                                              Int32 cySrc,
                                              BlendFunction blendFunction);
    }
}
