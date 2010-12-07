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
        IGraphics igphics;

        public frmMain()
        {
            InitializeComponent();

            igphics = new GdiGraphics(this) as IGraphics;
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            //Bitmap a
        }
    }
}