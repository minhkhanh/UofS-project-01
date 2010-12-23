using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace vCards
{
    public enum ImageControlState
    {
        MouseUp,
        MouseDown
    }

    public abstract class ImageControl
    {
        ImageControlState state = ImageControlState.MouseUp;

        public ImageControl(Rectangle regn, bool visi, string capt, IBitmap ibmp, IGraphics igr)
        {
            region = regn;
            visible = visi;

            ibmpBkgr = igr.CreateBitmap(ibmp);
        }

        Rectangle region;
        public Rectangle Region
        {
            get { return region; }
        }

        public int Width
        {
            get { return region.Width; }
        }
        public int Height
        {
            get { return region.Height; }
        }
        public int X
        {
            get { return region.X; }
        }
        public int Y
        {
            get { return region.Y; }
        }

        bool visible = false;

        protected IBitmap ibmpBkgr;

        public bool IsIn(Point pos)
        {
            return (
                pos.IsEmpty == false
                && pos.X >= region.X
                && pos.X <= region.X + region.Width
                && pos.Y >= region.Y
                && pos.Y <= region.Y + region.Height
                );
        }

        public event EventHandler<MouseEventArgs> MouseDown;
        public event EventHandler<MouseEventArgs> MouseUp;

        public void OnRaiseMouseDownEvent(MouseEventArgs e)
        {
            EventHandler<MouseEventArgs> handler = MouseDown;

            if (handler != null)
            {
                handler(this, e);
            }
        }

        public void OnRaiseMouseUpEvent(MouseEventArgs e)
        {
            EventHandler<MouseEventArgs> handler = MouseUp;

            if (handler != null)
            {
                handler(this, e);
            }
        }

        public void OnMouseDown(object o, MouseEventArgs e)
        {
            if (visible && IsIn(new Point(e.X, e.Y)))
                OnRaiseMouseDownEvent(e);
        }

        public void OnMouseUp(object o, MouseEventArgs e)
        {
            if (state == ImageControlState.MouseDown)
            {
                state = ImageControlState.MouseUp;
            }
        }

        public void DrawBackground(IGraphics igr)
        {
            igr.DrawBitmap(region, ibmpBkgr);
        }
    }
}
