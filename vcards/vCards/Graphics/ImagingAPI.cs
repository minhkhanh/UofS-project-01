﻿using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;
using System.IO;

namespace vCards
{
    // Pulled from gdipluspixelformats.h in the Windows Mobile 5.0 Pocket PC SDK
    public enum PixelFormatID : int
    {
        PixelFormatIndexed = 0x00010000,  // Indexes into a palette
        PixelFormatGDI = 0x00020000,      // Is a GDI-supported format
        PixelFormatAlpha = 0x00040000,    // Has an alpha component
        PixelFormatPAlpha = 0x00080000,   // Pre-multiplied alpha
        PixelFormatExtended = 0x00100000, // Extended color 16 bits/channel
        PixelFormatCanonical = 0x00200000,
        PixelFormatUndefined = 0,
        PixelFormatDontCare = 0,
        PixelFormat1bppIndexed = (1 | (1 << 8) | PixelFormatIndexed | PixelFormatGDI),
        PixelFormat4bppIndexed = (2 | (4 << 8) | PixelFormatIndexed | PixelFormatGDI),
        PixelFormat8bppIndexed = (3 | (8 << 8) | PixelFormatIndexed | PixelFormatGDI),
        PixelFormat16bppRGB555 = (5 | (16 << 8) | PixelFormatGDI),
        PixelFormat16bppRGB565 = (6 | (16 << 8) | PixelFormatGDI),
        PixelFormat16bppARGB1555 = (7 | (16 << 8) | PixelFormatAlpha | PixelFormatGDI),
        PixelFormat24bppRGB = (8 | (24 << 8) | PixelFormatGDI),
        PixelFormat32bppRGB = (9 | (32 << 8) | PixelFormatGDI),
        PixelFormat32bppARGB = (10 | (32 << 8) | PixelFormatAlpha | PixelFormatGDI | PixelFormatCanonical),
        PixelFormat32bppPARGB = (11 | (32 << 8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatGDI),
        PixelFormat48bppRGB = (12 | (48 << 8) | PixelFormatExtended),
        PixelFormat64bppARGB = (13 | (64 << 8) | PixelFormatAlpha | PixelFormatCanonical | PixelFormatExtended),
        PixelFormat64bppPARGB = (14 | (64 << 8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatExtended),
        PixelFormatMax = 15
    }

    // Pulled from imaging.h in the Windows Mobile 5.0 Pocket PC SDK
    public enum BufferDisposalFlag : int
    {
        BufferDisposalFlagNone,
        BufferDisposalFlagGlobalFree,
        BufferDisposalFlagCoTaskMemFree,
        BufferDisposalFlagUnmapView
    }

    // Pulled from imaging.h in the Windows Mobile 5.0 Pocket PC SDK
    public enum InterpolationHint : int
    {
        InterpolationHintDefault,
        InterpolationHintNearestNeighbor,
        InterpolationHintBilinear,
        InterpolationHintAveraging,
        InterpolationHintBicubic
    }

    // Pulled from gdiplusimaging.h in the Windows Mobile 5.0 Pocket PC SDK
    public struct BitmapData
    {
        public uint Width;
        public uint Height;
        public int Stride;
        public PixelFormatID PixelFormat;
        public IntPtr Scan0;
        public IntPtr Reserved;
    }

    // Pulled from imaging.h in the Windows Mobile 5.0 Pocket PC SDK
    public struct ImageInfo
    {
        // I am being lazy here, I don't care at this point about the RawDataFormat GUID
        public uint GuidPart1;
        public uint GuidPart2;
        public uint GuidPart3;
        public uint GuidPart4;
        public PixelFormatID pixelFormat;
        public uint Width;
        public uint Height;
        public uint TileWidth;
        public uint TileHeight;
        public double Xdpi;
        public double Ydpi;
        public uint Flags;
    }

    // Pulled from imaging.h in the Windows Mobile 5.0 Pocket PC SDK
    [ComImport, Guid("327ABDA7-072B-11D3-9D7B-0000F81EF32E"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    [ComVisible(true)]
    public interface IImagingFactory
    {
        uint CreateImageFromStream(Stream strm, out IImage img); // This is a place holder
        uint CreateImageFromFile(string filename, out IImage image);
        // We need the MarshalAs attribute here to keep COM interop from sending the buffer down as a Safe Array.
        uint CreateImageFromBuffer([MarshalAs(UnmanagedType.LPArray)] byte[] buffer, uint size, BufferDisposalFlag disposalFlag, out IImage image);
        uint CreateNewBitmap();            // This is a place holder
        uint CreateBitmapFromImage();      // This is a place holder
        uint CreateBitmapFromBuffer();     // This is a place holder
        uint CreateImageDecoder();         // This is a place holder
        uint CreateImageEncoderToStream(); // This is a place holder
        uint CreateImageEncoderToFile();   // This is a place holder
        uint GetInstalledDecoders();       // This is a place holder
        uint GetInstalledEncoders();       // This is a place holder
        uint InstallImageCodec();          // This is a place holder
        uint UninstallImageCodec();        // This is a place holder
    }

    // Pulled from imaging.h in the Windows Mobile 5.0 Pocket PC SDK
    [ComImport, Guid("327ABDA9-072B-11D3-9D7B-0000F81EF32E"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    [ComVisible(true)]
    public interface IImage
    {
        uint GetPhysicalDimension(out Size size);
        uint GetImageInfo(out ImageInfo info);
        uint SetImageFlags(uint flags);
        // "Correct" declaration: uint Draw(IntPtr hdc, ref Rectangle dstRect, ref Rectangle srcRect);
        uint Draw(IntPtr hdc, ref Rectangle dstRect, ref Rectangle srcRect);
        //uint Draw(IntPtr hdc, ref Rectangle dstRect, IntPtr NULL);
        uint PushIntoSink(); // This is a place holder
        uint GetThumbnail(uint thumbWidth, uint thumbHeight, out IImage thumbImage);
    }

    // Pulled from imaging.h in the Windows Mobile 5.0 Pocket PC SDK
    [ComImport, Guid("327ABDAA-072B-11D3-9D7B-0000F81EF32E"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    [ComVisible(true)]
    public interface IBitmapImage
    {
        uint GetSize(out Size size);
        uint GetPixelFormatID(out PixelFormatID pixelFormat);
        uint LockBits(ref Rectangle rect, uint flags, PixelFormatID pixelFormat, out BitmapData lockedBitmapData);
        uint UnlockBits(ref BitmapData lockedBitmapData);
        uint GetPalette();  // This is a place holder, note the lack of arguments
        uint SetPalette();  // This is a place holder, note the lack of arguments
    }
}
