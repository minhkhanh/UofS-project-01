using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;

namespace _0812239
{
    public class Animation
    {
        public Animation(string fileName, IGraphics graphics,
            int numberColumns, int startCell,
            int cellWidth, int cellHeight)
        {
            
        }

        public Animation(Stream stream, IGraphics graphics,
            int numberColumns, int startCell,
            int cellWidth, int cellHeight)
        {
            
        }

        public Animation(IBitmap bmp, int numberColumns, IGraphics graphics)
        {
            
        }

        /// <summary>
        /// Thay doi rectSrc cho phu hop voi khung hinh hien tai
        /// </summary>
        /// <param name="rectSrc"></param>
        /// <returns></returns>
        public bool ValidateRegions(ref Rectangle rectSrc)
        {
            //if (rectSrc.Width < 0 || rectSrc.Height < 0)
            //    return false;

            //if (rectSrc.X < 0)
            //{
            //    rectSrc.Width += rectSrc.X;     // giam mot luong bang X
            //    rectSrc.X = 0;
            //}
            //else if (rectSrc.X > m_iCellWidth)
            //    return false;

            //if (rectSrc.Y < 0)
            //{
            //    rectSrc.Height += rectSrc.Y;    // giam mot luong bang Y
            //    rectSrc.Y = 0;
            //}
            //else if (rectSrc.Y > m_iCellHeight)
            //    return false;

            //if (rectSrc.X + rectSrc.Width > m_iCellWidth)
            //    rectSrc.Width -= (rectSrc.X + rectSrc.Width) - m_iCellWidth;

            //if (rectSrc.Y + rectSrc.Height > m_iCellHeight)
            //    rectSrc.Height -= (rectSrc.Y + rectSrc.Height) - m_iCellHeight;

            //rectSrc.X += m_iCurCell * m_iCellWidth;     // dieu chinh theo khung hinh hien tai

            return true;
        }

        
        public void Update()
        {
            //if (m_iCurDelay >= m_iAnimationRate)
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

        public void Update(ref bool cycleFinished)
        {
            //if (m_iCurDelay >= m_iAnimationRate)
            //{
            //    m_iCurDelay = 0;

            //    ++m_iCurCell;
            //    if (m_iCurCell >= m_iCellNumber)
            //    {
            //        m_iCurCell = 0;
            //        cycleFinished = true;                    
            //    }
            //    else
            //    {
            //        ++m_iCurCell;
            //        cycleFinished = false;
            //    }
            //}
            //else
            //{
            //    ++m_iCurDelay;
            //    cycleFinished = false;
            //}
        }

        public void Dispose()
        {
        }
    }
}
