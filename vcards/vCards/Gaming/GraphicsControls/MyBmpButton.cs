using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace vCards
{
    public enum MyButtonState
    {
        Up,
        Down
    }

    public class MyBmpButton : MyBmpControl
    {
        IImage iimgCover;
        IBitmap ibmpHolding;

        MyButtonState btnState = MyButtonState.Up;
        public MyButtonState State
        {
            get { return btnState; }
            set { btnState = value; }
        }

        public MyBmpButton(string cap, Rectangle loc, IBitmap bkgr, IBitmap holding, string filename, IImagingFactory fac)
            : base(cap, loc, bkgr)
        {
            ibmpHolding = holding;
            fac.CreateImageFromFile(filename, out iimgCover);
        }

        public MyBmpButton(GamePanel gpn, string cap, Rectangle loc, string bmpFile, string imgFile)
            : base(cap, loc, null)
        {
            //iimgHolding = hover;
            //BmpBackground = gpn.IGameGracphics.CreateBitmap(bmpFile, true);
            //gpn.IGameImgFactory.CreateImageFromFile(imgFile, out iimgHolding);
        }

        public bool IsIn(Point pos)
        {
            return (
                pos.X >= Region.X && pos.X <= Region.X + Region.Width
                && pos.Y >= Region.Y && pos.Y <= Region.Y + Region.Height
                );
        }

        public void DrawHolding(IGraphics igr)
        {
            igr.DrawBitmap(Region, ibmpHolding);
        }

        public void DrawCover(IGraphics igr)
        {
            igr.DrawImageAlphaChannel(iimgCover, Region.X, Region.Y);
        }

        public void Draw(IGraphics igr)
        {
            if (btnState == MyButtonState.Down)
                DrawHolding(igr);
            else if (btnState == MyButtonState.Up)
                DrawBkgr(igr);

            DrawText(igr);

            DrawCover(igr);
        }
    }
}
