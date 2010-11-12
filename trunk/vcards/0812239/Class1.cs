using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace _0812239
{
    public interface IMyInterface
    {
        void Printf();
        IMyInterface CreateInstance();
    }

    public class Class1 : IMyInterface
    {
        public void Printf()
        {
            MessageBox.Show("class1");
        }

        public IMyInterface CreateInstance()
        {
            Font a = new Font("a", 1, FontStyle.Bold);
            //DrawOptions.
            return new Class1();
        }
    }

    public class Class2: IMyInterface
    {
        public void Printf()
        {
            MessageBox.Show("class2");
        }

        public IMyInterface CreateInstance()
        {
            return new Class2();
        }
    }
}
