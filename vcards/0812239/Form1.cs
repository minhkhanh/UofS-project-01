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
        //Bitmap _bmp;

        string _strAppPath = System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName.Replace(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].Name, "");
        GamePanel _gamePanel;
        public Form1()
        {
            InitializeComponent();
            _gamePanel = new GamePanel(this);
            //this.Create
        }

        private void menuItem1_Click(object sender, EventArgs e)
        {
            IBitmap ibmp = _gamePanel.IGameGracphics.CreateBitmap(_strAppPath + @"Resources\Cards\1-2.png", true);
            ibmp.SourceKey = Color.White;

            //_gamePanel.IGameGracphics.DrawBitmap(0, 0, new Rectangle(0, 0, ibmp.Width, ibmp.Height), ibmp);
            //_gamePanel.IGameGracphics.DrawImageTransparent(ibmp, new Rectangle(0,0,20,20));
            //_gamePanel.IGameGracphics.DrawImageTransparent(ibmp, new Rectangle(20, 20, 50, 50), 0, 0);

            _gamePanel.IGameGracphics.Flip();

            ibmp.Dispose();
        }

        private void menuItem2_Click(object sender, EventArgs e)
        {

        }
    }
}