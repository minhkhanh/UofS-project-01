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

        ImageButton btnLeft;
        ImageButton btnRight;

        int iCurrIdx = 0;
        int iLimit = 0;

        //IFont _font;

        public ImgCtrlScrollList(Rectangle rect)
            : base(rect)
        {
            //_font = font;

            Rectangle rectArrow = new Rectangle(rect.X, rect.Y, rect.Height, rect.Height);
            btnLeft = new ImageButton(
                rectArrow
                , MyResourceManager.iimgLeftArrow
                );

            rectArrow.X = rect.X + rect.Width - rect.Height;
            btnRight = new ImageButton(
                rectArrow
                , MyResourceManager.iimgRightArrow
                );

            ManageControl(btnLeft);
            ManageControl(btnRight);

            btnLeft.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnLeft_MouseUp);
            btnRight.MouseUp += new EventHandler<System.Windows.Forms.MouseEventArgs>(btnRight_MouseUp);
        }

        public void btnRight_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            ++iCurrIdx;
            if (iCurrIdx >= iLimit)
                iCurrIdx = 0;
        }

        public void btnLeft_MouseUp(object o, System.Windows.Forms.MouseEventArgs e)
        {
            --iCurrIdx;
            if (iCurrIdx < 0)
                iCurrIdx = iLimit - 1;
        }

        public void AddItem(object val, string txt)
        {
            listItemText.Add(txt);
            listItemValue.Add(val);

            ++iLimit;
        }

        public string CurrentItemText
        {
            get { return listItemText[iCurrIdx]; }
        }

        public object CurrentItemValue
        {
            get { return listItemValue[iCurrIdx]; }
        }

        public int CurrentIndex
        {
            set { iCurrIdx = value; }
            get { return iCurrIdx; }
        }

        public override void Dispose()
        {
            base.Dispose();

            listItemValue.Clear();
            listItemText.Clear();
        }
        public string CurrentItemText
        {
            get { return listItemText[iCurrIdx]; }
        }
        public override void DoDrawing(IGraphics igp)
        {
            base.DoDrawing(igp);

            if (iLimit > 0)
                igp.DrawText(
                    new Rectangle(btnLeft.X + btnLeft.Width, btnLeft.Y, btnRight.X - btnLeft.X - btnLeft.Width, btnLeft.Height)
                    , listItemText[iCurrIdx]
                    , MyResourceManager.colorT1
                    , MyResourceManager.fontH1
                    , FontDrawOptions.DrawTextMiddle | FontDrawOptions.DrawTextCenter
                    );
        }
    }
}
