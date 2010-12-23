using System;
using System.Linq;
using System.Collections.Generic;
using System.Windows.Forms;

namespace vCards
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [MTAThread]
        static void Main()
        {
            Application.Run(new frmMain());
        }

        public static string AppPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().GetName().CodeBase);      
    }
}