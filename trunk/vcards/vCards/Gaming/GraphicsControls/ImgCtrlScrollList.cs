using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class ImgCtrlScrollList: ImgCtrlContainer
    {
        List<object> listItemValue = new List<object>();
        List<string> listItemText = new List<string>();

        ImageButton btnLeft;// = new ImageButton()
        ImageButton btnRight;

        int iCurr = 0;
        int iLimit = 0;

        public ImgCtrlScrollList(Rectangle rect)
            : base(rect)
        {
            Rectangle rectArrow = new Rectangle(rect.X, rect.Y, rect.Height, rect.Height);
            btnLeft = new ImageButton(
                rectArrow
                , MyResourceManager.iimgLeftArrowBkgr
                , MyResourceManager.iimgLeftArrowHover
                );

            rectArrow.X = rect.X + rect.Width - rect.Height;
            btnRight = new ImageButton(
                rectArrow
                , MyResourceManager.iimgRightArrowBkgr
                , MyResourceManager.iimgRightArrowHover
                );

            ManageControl(btnLeft);
            ManageControl(btnRight);

            btnLeft.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnLeft_MouseUp);
            btnRight.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnRight_MouseUp);
        }

        public void btnRight_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            ++iCurr;
            if (iCurr >= iLimit)
                iCurr = 0;
        }

        public void btnLeft_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            --iCurr;
            if (iCurr < 0)
                iCurr = iLimit - 1;
        }

        public void AddItem(object val, string txt)
        {
            listItemText.Add(txt);
            listItemValue.Add(val);

            ++iLimit;
        }

        public object GetCurrValue()
        {
            return listItemValue[iCurr];
        }

        public override void Dispose()
        {
            base.Dispose();

            listItemValue.Clear();
            listItemText.Clear();
        }

        public override void Draw(IGraphics igp)
        {
            base.Draw(igp);

            igp.DrawText(
                new Rectangle(btnLeft.X+btnLeft.Width, btnLeft.Y, btnRight.X-btnLeft.X-btnLeft.Width, btnLeft.Height)
                , listItemText[iCurr]
                , Color.GreenYellow
                , MyResourceManager.fontH1
                , FontDrawOptions.DrawTextMiddle | FontDrawOptions.DrawTextCenter
                );
        }
    }
}
