using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace vCards
{
    public class GamePanel
    {
        IImagingFactory factory = (IImagingFactory)Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid("327ABDA8-072B-11D3-9D7B-0000F81EF32E")));
        public IImagingFactory IGameImgFactory
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
            playing = true;
        }

        bool playing;

        public void GameLoop()
        {
            while (playing)
            {

            }
        }
    }
}
