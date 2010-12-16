using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class TapCacLaBai: MyUserControl
    {
        private List<LaBai> dsLaBai = new List<LaBai>();
        protected TapCacLaBai()
        {

        }
        public TapCacLaBai(Rectangle rect): base(rect)
        {

        }
        public void Add(LaBai lb)
        {
            if(lb!=null) dsLaBai.Add(lb);
        }
        public void Remove(LaBai lb)
        {
            if (lb != null) dsLaBai.Remove(lb);
        }
        public void Draw(IGraphics igr)     // update vi tri truoc khi xuat
        {
            foreach (LaBai lb in dsLaBai)
            {
                lb.DrawBkgr(igr);
            }
        }
        public void UpdatePos()
        {
            if (dsLaBai.Count<=0)
            {
                return;
            }
            dsLaBai.Sort();
            int denta = this.Region.Width - LaBai.iBaseWidth;
            int dentadef = LaBai.iMaxWidth * dsLaBai.Count;
            int left = Region.Left;
            int width = LaBai.iMaxWidth;
            if (denta>dentadef)
            {
                float temp = denta - dentadef;
                temp /= 2;
                left += (int)temp;
            } 
            else
            {
                float f = denta / (dsLaBai.Count - 1);
                width = (int)f;
            }            
            for (int i=0; i<dsLaBai.Count; ++i)
            {
                Rectangle rect = new Rectangle(left + width * i, dsLaBai[i].Region.Y, dsLaBai[i].Region.Width, dsLaBai[i].Region.Height);
                dsLaBai[i].Region = rect;
            }
        }
    }
}
