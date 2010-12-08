using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace vCards
{
    public partial class frmMain : Form
    {
        string pathApp = System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName.Replace(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].Name, "");

        GamePanel gpanel;

        public frmMain()
        {
            InitializeComponent();

            gpanel = new GamePanel(this);
            //igphics = new GdiGraphics(this) as IGraphics;
        }

        void Test01()
        {
            int i = 1;
            int j = 1;
            string filename = pathApp + @"Resources\Images\Cards\" + i.ToString() + "-" + j.ToString() + ".png";
            string filename2 = pathApp + @"Resources\Images\Misc\Untitled-1.png";

            IBitmap a = gpanel.IGameGracphics.CreateBitmap(filename, false);
            //a.SourceKey
            //gpanel.IGameGracphics.DrawBitmap(0, 0, a);
            gpanel.IGameGracphics.SetDrawOptions(DrawOptions.BlitMirrorLeftRight);
            gpanel.IGameGracphics.DrawBitmap(0, 0, a);

            IImage b;
            gpanel.IGameImgFactory.CreateImageFromFile(filename2, out b);
            //gpanel.IGameGracphics.DrawImageAlphaChannel(b, new Rectangle(0, 0, 100, 100), new Rectangle(0, 0, 100, 100));

            gpanel.IGameGracphics.Flip();

            a.Dispose();
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            //Test01();
        }

        private void frmMain_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //if (j == 13)
            //{
            //    ++i;
            //    j = 1;

            //    if (i > 4)
            //        i = 1;
            //}
            //else
            //    ++j;

            //string filename = pathApp + @"Resources\Images\Cards\" + i.ToString() + "-" + j.ToString() + ".png";

            //IBitmap a = new GdiBitmap(filename, false) as IBitmap;
            //gpanel.IGameGracphics.DrawBitmap(0, 0, a);
            //gpanel.IGameGracphics.Flip();

            //a.Dispose();
        }
    }
}