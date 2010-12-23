using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class Card : MyBmpControl, IComparable<Card>
    {
        public static int iBaseHeight;  //bề cao lá bài
        public static int iBaseWidth;   //bề rộng lá bài
        public static int iMaxWidth;    //khoảng cách lớn nhất giữa 2 lá bài
        private int iIndex;
        public int Index
        {
            get { return iIndex; }
            set { iIndex = value; }
        }
        protected Card()
        {

        }
        public Card(int index)
            : base(new Rectangle(0, 0, Card.iBaseWidth, Card.iBaseHeight), ResourcesManager.GetCardBitmap(index))
        {
            //this.BmpBackground = ResourcesManager.GetCardBitmap(index);
            iIndex = index;
            //this.Region= this.BmpBackground.Dispose//
        }

        #region IComparable<LaBai> Members

        public int CompareTo(Card other)
        {
            /* LEGEND
            * < 0 means that this object is less than other
            * 0 means that both objects are equal
            * > 0 means that this object is greater than other
            * */
            return iIndex.CompareTo(other.Index);
        }

        #endregion

        #region IDisposable Members

        public override void Dispose()
        {
            
        }
        
        #endregion

        public override void DrawBkgr(IGraphics igr)
        {
            //igr.DrawBitmap(Region.X, Region.Y, BmpBackground);
            IFont font = igr.CreateFont("Tahoma", 15, FontStyle.Bold);
            igr.DrawText(Region, "K", Color.Blue, font, FontDrawOptions.DrawTextCenter | FontDrawOptions.DrawTextMiddle);
        }
    }
}
