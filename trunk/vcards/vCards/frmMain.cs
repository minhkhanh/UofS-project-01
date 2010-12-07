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

        IGraphics igphics;

        public frmMain()
        {
            InitializeComponent();

            igphics = new GdiGraphics(this) as IGraphics;
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            
        }

        int i = 1;
        int j = 1;
        private void frmMain_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (j == 13)
            {
                ++i;
                j = 1;

                if (i > 4)
                    i = 1;
            }
            else
                ++j;

            string filename = pathApp + @"Resources\Images\Cards\" + i.ToString() + "-" + j.ToString() + ".png";

            IBitmap a = new GdiBitmap(filename, false) as IBitmap;
            igphics.DrawBitmap(0, 0, a);
            igphics.Flip();

            a.Dispose();
        }
    }
}