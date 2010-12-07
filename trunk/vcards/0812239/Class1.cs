using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.Runtime.InteropServices;

namespace _0812239
{
    public interface IMyInterface2
    {
        void Printf();
    }

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

        //[StructLayout(LayoutKind.Sequential)]

        public IMyInterface CreateInstance()
        {
            

            return new Class1();
        }
    }

    public class Class2: IMyInterface
    {
        public void Printf()
        {
            IMyInterface2 a = (IMyInterface2)new Class1();
            a.Printf();

            //MessageBox.Show("class2");
        }

        public IMyInterface CreateInstance()
        {
            return new Class2();
        }
    }
}
