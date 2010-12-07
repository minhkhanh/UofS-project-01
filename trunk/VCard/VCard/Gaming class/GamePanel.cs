using System;
using System.Drawing;
using System.Windows.Forms;
namespace VCard
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