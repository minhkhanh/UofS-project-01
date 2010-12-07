using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace _0812239
{
    public partial class frmMain : Form
    {
        Thread m_threadLogic;

        string m_strAppPath = System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName.Replace(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].Name, "");
        GamePanel m_gamePanel;

        public frmMain()
        {
            InitializeComponent();
            m_gamePanel = new GamePanel(this);

            m_threadLogic = new Thread(new ThreadStart(ThreadFunc));
            m_threadLogic.Start();
        }

        void ThreadFunc()
        {
            m_gamePanel.GameLoop();
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            //IBitmap ibmp = m_gamePanel.IGameGracphics.CreateBitmap(m_strAppPath + @"Resources\Cards\1-1.png", true);

            //m_gamePanel.IGameGracphics.DrawBitmap(0,0, )
            
        }

        private void menuItem2_Click(object sender, EventArgs e)
        {
            // Load the image with alpha data through Imaging.
            
            
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            Close();
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
        }
    }
}