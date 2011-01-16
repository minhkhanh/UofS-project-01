using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ToggleImgBtn: ImageButton
    {
        bool toggleValue;

        public ToggleImgBtn(Rectangle regn, string ibmpPath, string iimgPath, string pathIcon, IGraphics igp, bool val)
            : base(regn, ibmpPath, igp)
        {
            toggleValue = val;
        }

        public override void DoDrawing(IGraphics igp)
        {
            if (toggleValue)
                DrawDownState(igp);
            else
                DrawBackground(igp);
        }

        public override void OnMouseDown(object o, System.Windows.Forms.MouseEventArgs e)
        {
            base.OnMouseDown(o, e);

            if (mouseState == MouseState.MouseDown)
                toggleValue = !toggleValue;
        }
    }
}
