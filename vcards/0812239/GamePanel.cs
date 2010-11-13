using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace _0812239
{
    public class GamePanel
    {
        IGraphics g;
        public IGraphics IGameGracphics
        {
            get { return g; }
            set { g = value; }
        }

        public GamePanel(Control owner)
        {
            g = new GdiGraphics(owner);
        }
    }
}
