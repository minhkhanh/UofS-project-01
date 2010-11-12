using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace _0812239
{
    public partial class Form1 : Form
    {
        private Class1 cls = new Class1();
        private Class2 cls2 = new Class2();

        public Form1()
        {
            InitializeComponent();
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            int[] aaa = {1,2};
            aaa.OrderBy(g => g);
            IMyInterface inf = cls as IMyInterface;

            inf.Printf();

            inf = cls2 as IMyInterface;
            //Font a = new Font();

            inf.Printf();
        }

        private void menuItem2_Click(object sender, EventArgs e)
        {
            //IGra
        }
    }
}