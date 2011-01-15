using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Media;
using ShareLibrary;

namespace vCards
{
    public partial class frmMain : Form
    {
        GamePanel gamePanel;
        MyResourceManager resrcManager;

        Thread threadLogic;

        //IImagingFactory imagingFactory = (IImagingFactory)Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid("327ABDA8-072B-11D3-9D7B-0000F81EF32E")));

        public frmMain()
        {
            InitializeComponent();

            string[] str = QuanLyAI.GetAINameList();
            InterfaceAI tmp = QuanLyAI.CreateObjAIByName("Chicken AI");

            gamePanel = new GamePanel(this);
            resrcManager = new MyResourceManager(gamePanel.GameGraphics);

            threadLogic = new Thread(new ThreadStart(ThreadFunc));
            threadLogic.Start();

            //MyResourceManager.songBkgr01.PlayLooping();
        }

        private void frmMain_Closing(object sender, CancelEventArgs e)
        {
            threadLogic.Abort();
            MyResourceManager.StopSounds();
        }

        void ThreadFunc()
        {
            gamePanel.GameLoop();

            MyResourceManager.StopSounds();

            Application.Exit();
        }

        void Test01()
        {
            IImage iimg;
            gamePanel.GameGraphics.CreateIImage(Program.AppPath + @"\Resources\Images\Misc\Untitled-1.png", out iimg);

            gamePanel.GameGraphics.DrawImageAlphaChannel(iimg, 50, 10);
            gamePanel.GameGraphics.Flip();
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //base.OnPaintBackground(e);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //Test01();
        }

        private void frmMain_MouseMove(object sender, MouseEventArgs e)
        {

        }

        private void frmMain_Resize(object sender, EventArgs e)
        {

        }

        private void frmMain_Click(object sender, EventArgs e)
        {
            
        }
    }
}