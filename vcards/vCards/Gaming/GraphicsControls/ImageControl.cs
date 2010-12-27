using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace vCards
{
    public enum MouseState
    {
        MouseUp,
        MouseDown,

        Click
    }

    public abstract class ImageControl
    {
        #region data members

        protected MouseState mouseState = MouseState.MouseUp;
        protected Rectangle region;
        bool enabled = false;
        //protected IBitmap bkgrBmp;

        #endregion

        #region events

        public event EventHandler<MouseEventArgs> MouseDown;
        public event EventHandler<MouseEventArgs> MouseUp;
        public event EventHandler<MouseEventArgs> MouseMove;

        public event EventHandler<EventArgs> Click;

        #endregion

        #region properties

        //public int Width
        //{
        //    get { return region.Width; }
        //}
        //public int Height
        //{
        //    get { return region.Height; }
        //}

        public int X
        {
            set { region.X = value; }
            get { return region.X; }
        }
        public int Y
        {
            set { region.Y = value; }
            get { return region.Y; }
        }

        //public Point Location
        //{
        //    set { region.Location = value; }
        //}

        public Rectangle Region
        {
            set { region = value; }
            get { return region; }
        }

        #endregion

        #region constructors

        public ImageControl() { }

        public ImageControl(Rectangle regn, bool isEnabled)
        {
            region = regn;
            enabled = isEnabled;
        }

        #endregion

        #region private methods

        private void RaiseClickEvent(EventArgs e)
        {
            EventHandler<EventArgs> handler = Click;

            if (handler != null)
            {
                handler(this, e);
            }
        }

        private void RaiseMouseDownEvent(MouseEventArgs e)
        {
            EventHandler<MouseEventArgs> handler = MouseDown;

            if (handler != null)
            {
                handler(this, e);
            }
        }

        private void RaiseMouseUpEvent(MouseEventArgs e)
        {
            EventHandler<MouseEventArgs> handler = MouseUp;

            if (handler != null)
            {
                handler(this, e);
            }
        }

        private void RaiseMouseMoveEvent(MouseEventArgs e)
        {
            EventHandler<MouseEventArgs> handler = MouseMove;

            if (handler != null)
            {
                handler(this, e);
            }
        }

        #endregion

        #region public methods

        public void Enable()
        {
            enabled = true;
        }

        public void Disable()
        {
            enabled = false;
        }

        #endregion

        #region virtual methods

        public virtual void OnMouseDown(object o, MouseEventArgs e)
        {
            if (enabled && region.Contains(e.X, e.Y))
            {
                mouseState = MouseState.MouseDown;
                RaiseMouseDownEvent(e);
            }
        }

        public virtual void OnMouseUp(object o, MouseEventArgs e)
        {
            if (mouseState == MouseState.MouseDown)
            {
                mouseState = MouseState.MouseUp;
                RaiseMouseUpEvent(e);
            }
        }

        public virtual void OnMouseMove(object o, MouseEventArgs e)
        {
            if (mouseState == MouseState.MouseDown)
            {
                RaiseMouseMoveEvent(e);
            }
        }

        public virtual void OnClick(object o, EventArgs e)
        {
            if (mouseState == MouseState.MouseDown)
            {
                mouseState = MouseState.MouseUp;
                RaiseClickEvent(e);
            }
        }

        public abstract void DrawBackground(IGraphics igr);
        public abstract void Draw(IGraphics igr);

        #endregion
    }
}
