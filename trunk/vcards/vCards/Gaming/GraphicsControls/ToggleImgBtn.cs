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

        public ToggleImgBtn(Rectangle regn, string ibmpPath, IGraphics igp, string iimgPath, bool val)
            : base(regn, ibmpPath, igp, iimgPath)
        {
            toggleValue = val;
        }

        public override void Draw(IGraphics igp)
        {
            if (toggleValue)
                DrawHover(igp);
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
