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

        private void frmMain_Paint(object sender, PaintEventArgs e)
        {
            IBitmap a = new GdiBitmap(pathApp + @"Resources\Images\Cards\1-1.png", false) as IBitmap;
            igphics.DrawBitmap(0, 0, a);
            igphics.Flip();

            a.Dispose();
        }
    }
}