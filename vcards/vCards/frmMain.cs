using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace vCards
{
    public partial class frmMain : Form
    {
        //public static string pathApp = System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName.Replace(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].Name, "");

        GamePanel gpanel;

        Thread threadLogic;

        public frmMain()
        {
            InitializeComponent();

            gpanel = new GamePanel(this);
            ResourcesManager.gpanel = gpanel;
            threadLogic = new Thread(new ThreadStart(ThreadFunc));
            threadLogic.Start();
        }

        void ThreadFunc()
        {
            gpanel.GameLoop();
        }

        void Test01()
        {
            int i = 1;
            int j = 1;
            string filename = gpanel.AppPath + @"Resources\Images\Cards\" + i.ToString() + "-" + j.ToString() + ".png";
            string filename2 = gpanel.AppPath + @"Resources\Images\Misc\Untitled-1.png";

            IBitmap a = gpanel.IGameGracphics.CreateBitmap(filename, false);
            //a.SourceKey
            //gpanel.IGameGracphics.DrawBitmap(0, 0, a);
            gpanel.IGameGracphics.SetDrawOptions(DrawOptions.BlitMirrorLeftRight);
            gpanel.IGameGracphics.DrawBitmap(0, 0, a);

            IImage b;
            gpanel.IGameImgFactory.CreateImageFromFile(filename2, out b);
            gpanel.IGameGracphics.DrawImageAlphaChannel(b, 0, 0);

            gpanel.IGameGracphics.Flip();

            a.Dispose();
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

        private void frmMain_Closing(object sender, CancelEventArgs e)
        {
            threadLogic.Abort();
        }

        private void frmMain_MouseDown(object sender, MouseEventArgs e)
        {
            Point pos = new Point(e.X, e.Y);
            gpanel.SendMessage(MessageID.MouseDown, pos);

            //Test01();
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //base.OnPaintBackground(e);
        }

        private void frmMain_MouseUp(object sender, MouseEventArgs e)
        {
            Point pos = new Point(e.X, e.Y);
            gpanel.SendMessage(MessageID.MouseUp, pos);
        }
    }
}