using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace _0812239
{
    public class GamePanel
    {
        static IImagingFactory factory = (IImagingFactory)Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid("327ABDA8-072B-11D3-9D7B-0000F81EF32E")));
        static public IImagingFactory IGameImagingFactory
        {
            get { return factory; }
            set { factory = value; }
        }

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

        bool m_bPlaying;
        public void GameLoop()
        {
            while (true) ;
        }
    }
}
