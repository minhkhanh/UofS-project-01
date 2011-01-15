using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImgCtrlContainer: MyControl
    {
        protected List<MyControl> listControls = new List<MyControl>();

        public ImgCtrlContainer(Rectangle rect)
            : base(rect)
            
        {
        }

        public ImgCtrlContainer(IGraphics igp)
            : base(new Rectangle(0, 0, igp.ScreenWidth, igp.ScreenHeight))
        {
        }

        //private void ManageControl(ImageControl control)
        //{
        //    this.MouseDown += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseDown);
        //    this.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseUp);
        //    this.MouseMove += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseMove);
        //    this.Click += new EventHandler<EventArgs>(control.OnClick);
        //}

        private void UnmanageControl(MyControl control)
        {
            this.MouseDown -= (EventHandler<System.Windows.Forms.MouseEventArgs>)control.OnMouseDown;
            this.MouseUp -= (EventHandler<System.Windows.Forms.MouseEventArgs>)control.OnMouseUp;
            this.MouseMove -= (EventHandler<System.Windows.Forms.MouseEventArgs>)control.OnMouseMove;

            //this.Click -= (EventHandler<EventArgs>)control.OnClick;
        }

        public override void Dispose()
        {
            foreach (MyControl i in listControls)
            {
                UnmanageControl(i);
                i.Dispose();
            }

            listControls.Clear();
        }

        public virtual int ManageControl(MyControl control)
        {
            listControls.Add(control);

            this.MouseDown += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseDown);
            this.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseUp);
            this.MouseMove += new EventHandler<System.Windows.Forms.MouseEventArgs>(control.OnMouseMove);
            //this.Click += new EventHandler<EventArgs>(control.OnClick);

            return listControls.Count - 1;
        }

        public virtual void RemoveAt(int idx)
        {
            if (listControls.Count == 0 || idx < 0 || idx >= listControls.Count)
                return;

            UnmanageControl(listControls[idx]);
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

                foreach (MyControl i in listControls)
                {
                    i.Enabled = value;
                }
            }
        }

        public override void Draw(IGraphics igp)
        {
            for (int i = 0; i < listControls.Count; ++i )
            {
                listControls[i].Draw(igp);
            }
        }
    }
}
