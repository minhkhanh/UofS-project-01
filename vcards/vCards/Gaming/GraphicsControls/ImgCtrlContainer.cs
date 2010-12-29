using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImgCtrlContainer: ImageControl
    {
        protected List<ImageControl> listControls = new List<ImageControl>();

        public ImgCtrlContainer() { }

        public ImgCtrlContainer(IGraphics igp)
            : base(new Rectangle(0, 0, igp.ScreenWidth, igp.ScreenHeight))
        {
        }

        private void ManageControl(ImageControl control)
        {
            this.MouseDown += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseDown);
            this.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseUp);
            this.MouseMove += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseMove);
            this.Click += new EventHandler<EventArgs>(control.OnClick);
        }

        private void ReleaseControl(ImageControl control)
        {
            this.MouseDown -= (EventHandler<System.Windows.Forms.MouseEventArgs>)control.OnMouseDown;
            this.MouseUp -= (EventHandler<System.Windows.Forms.MouseEventArgs>)control.OnMouseUp;
            this.MouseMove -= (EventHandler<System.Windows.Forms.MouseEventArgs>)control.OnMouseMove;

            this.Click -= (EventHandler<EventArgs>)control.OnClick;
        }

        public void Clear()
        {
            listControls.Clear();
        }

        public virtual void AddControl(ImageControl control)
        {
            listControls.Add(control);
            ManageControl(control);
        }

        public virtual void RemoveAt(int idx)
        {
            if (listControls.Count == 0 || idx < 0 || idx >= listControls.Count)
                return;

            ReleaseControl(listControls[idx]);
            listControls.RemoveAt(idx);
        }

        public override bool Enabled
        {
            get
            {
                return enabled;
            }
            set
            {
                enabled = value;

                foreach (ImageControl i in listControls)
                {
                    i.Enabled = value;
                }
            }
        }

        public override void Draw(IGraphics igp)
        {
            foreach (ImageControl i in listControls)
            {
                i.Draw(igp);
            }
        }
    }
}
