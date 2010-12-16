using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace vCards
{
    public class LaBai : MyBmpControl, IComparable<LaBai>
    {
        public static int iBaseHeight; //bề cao lá bài
        public static int iBaseWidth;   //bề rộng lá bài
        public static int iMaxWidth;    //khoảng cách lớn nhất giữa 2 lá bài
        private int iIndex;
        public int Index
        {
            get { return iIndex; }
            set { iIndex = value; }
        }
        protected LaBai()
        {

        }
        public LaBai(int index)
            : base(new Rectangle(0, 0, LaBai.iBaseWidth, LaBai.iBaseHeight), ResourcesManager.GetCardBitmap(index))
        {
            //this.BmpBackground = ResourcesManager.GetCardBitmap(index);
            iIndex = index;
            //this.Region= this.BmpBackground.Dispose//
        }

        #region IComparable<LaBai> Members

        public int CompareTo(LaBai other)
        {
            /* LEGEND
            * < 0 means that this object is less than other
            * 0 means that both objects are equal
            * > 0 means that this object is greater than other
            * */
            return iIndex.CompareTo(other.Index);
        }

        #endregion

        //public virtual void DrawBkgr(IGraphics igr)
        //{
        //    igr.DrawBitmap(Region.X, Region.Y, BmpBackground);
        //}
    }
}
