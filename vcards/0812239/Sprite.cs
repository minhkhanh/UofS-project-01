using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using System.Drawing.Imaging;

namespace _0812239
{
    public class Sprite
    {

        public Sprite(int width, int height, string strFileName, IGraphics g, byte team)
        {
        }

        public Sprite(Bitmap bmp, IGraphics g, int widthFrame, int x, int y)
        {

        }

        public void Update()
        {
            //if (m_iCurDelay >= m_iAniRate)
            //{
            //    m_iCurDelay = 0;

            //    ++m_iCurCell;
            //    if (m_iCurCell >= m_iCellNumber)
            //        m_iCurCell = 0;
            //    else
            //        ++m_iCurCell;
            //}
            //else
            //    ++m_iCurDelay;
        }

        public void Paint(IGraphics g, int xcur, int ycur)
        {
            
        }
    }
}
