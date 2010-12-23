using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class Deck: MyUserControl
    {
        private List<Card> listCard = new List<Card>();
        protected Deck()
        {

        }
        public Deck(Rectangle rect): base(rect)
        {

        }
        public void Add(Card lb)
        {
            if(lb!=null) listCard.Add(lb);
        }
        public void Remove(Card lb)
        {
            if (lb != null) listCard.Remove(lb);
        }
        public void Draw(IGraphics igr)     // update vi tri truoc khi xuat
        {
            foreach (Card lb in listCard)
            {
                lb.DrawBkgr(igr);
            }
        }
        public void UpdatePos()
        {
            if (listCard.Count<=0)
            {
                return;
            }
            listCard.Sort();
            int denta = this.Region.Width - Card.iBaseWidth;
            int dentadef = Card.iMaxWidth * listCard.Count;
            int left = Region.Left;
            int width = Card.iMaxWidth;
            if (denta>dentadef)
            {
                float temp = denta - dentadef;
                temp /= 2;
                left += (int)temp;
            } 
            else
            {
                float f = denta / (listCard.Count - 1);
                width = (int)f;
            }            
            for (int i=0; i<listCard.Count; ++i)
            {
                Rectangle rect = new Rectangle(left + width * i, listCard[i].Region.Y, listCard[i].Region.Width, listCard[i].Region.Height);
                listCard[i].Region = rect;
            }
        }

        #region IDisposable Members

        public override void Dispose()
        {

        }

        #endregion
    }
}
