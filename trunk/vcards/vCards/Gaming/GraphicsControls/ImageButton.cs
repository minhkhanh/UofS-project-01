using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImageButton: ImageControl
    {
        //IImage _iimgDown;

        //IImage _iimgIcon;
        //Point _offSet = Point.Empty;

        public ImageButton(Rectangle regn, string pathBkgr, IGraphics igp)
            : base(regn, pathBkgr, igp)
        {
            //igp.CreateIImage(pathDownImg, out _iimgDown);
            //igp.CreateIImage(pathIconImg, out _iimgIcon);
        }

        public ImageButton(Rectangle regn, IImage iimgBkgr)
            : base(regn, iimgBkgr)
        {
            //_iimgDown = iimgDown;

            //_iimgIcon = iimgIcon;
        }

        //public void DrawIcon(IGraphics igp)
        //{
        //    igp.DrawImageAlphaChannel(_iimgIcon, region);
        //}

        public void DrawDownState(IGraphics igp)
        {
            //if (_iimgDown != null)
            //    igp.DrawImageAlphaChannel(_iimgDown, region);
            //else
            //{
            //    igp.DrawFilledRect(region, Color.Red);

            //    igp.DrawLine(Color.FromArgb(64, 0, 0), region.X, region.Y + region.Height, region.X, region.Y);
            //    igp.DrawLine(Color.FromArgb(64, 0, 0), region.X, region.Y, region.X + region.Width, region.Y);

            //    igp.DrawLine(Color.FromArgb(255, 145, 145), region.X + region.Width, region.Y, region.X + region.Width, region.Y + region.Height);
            //    igp.DrawLine(Color.FromArgb(255, 145, 145), region.X + region.Width, region.Y + region.Height, region.X, region.Y + region.Height);
            //}

            igp.DrawImageAlphaChannel(MyResourceManager.iimgBtnDownCover, region);
        }

        //public void DrawUpState(IGraphics igp)
        //{
        //    //if (_iimgBkgr != null)
        //    igp.DrawImageAlphaChannel(_iimgBkgr, region);
        //    //else
        //    //{
        //    //    igp.DrawFilledRect(region, Color.Red);

        //    //    igp.DrawLine(Color.FromArgb(255, 145, 145), region.X, region.Y + region.Height, region.X, region.Y);
        //    //    igp.DrawLine(Color.FromArgb(255, 145, 145), region.X, region.Y, region.X + region.Width, region.Y);

        //    //    igp.DrawLine(Color.FromArgb(64, 0, 0), region.X + region.Width, region.Y, region.X + region.Width, region.Y + region.Height);
        //    //    igp.DrawLine(Color.FromArgb(64, 0, 0), region.X + region.Width, region.Y + region.Height, region.X, region.Y + region.Height);
        //    //}
        //}        

        public override void DoDrawing(IGraphics igp)
        {
            DrawBackground(igp);

            if (mouseState == MouseState.MouseDown)
                DrawDownState(igp);
            //else if (mouseState == MouseState.MouseUp)
            //    DrawUpState(igp);
        }
    }
}
