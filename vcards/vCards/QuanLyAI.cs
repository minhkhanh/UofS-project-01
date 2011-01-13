using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Reflection;
using ShareLibrary;

namespace vCards
{
    class QuanLyAI
    {
        public static string[] GetAINameList()
        {
            string strPath = System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].FullyQualifiedName;
            strPath = strPath.Replace(System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0].Name, "");
            List<string> temp = new List<string>();
            foreach (string fileName in Directory.GetFiles(strPath))
            {
                //Tạo biến giữ thông tin file
                FileInfo file = new FileInfo(fileName);
                //Nếu file có đuôi là dll thì ok
                if (file.Extension.Equals(".dll"))
                {
                    Assembly asm = Assembly.LoadFrom(fileName);
                    foreach (Type loai in asm.GetTypes())
                    {
                        foreach (Type face in loai.GetInterfaces())
                        {
                            if (face.FullName=="ShareLibrary.InterfaceAI")
                            {
                                InterfaceAI t = (InterfaceAI)Activator.CreateInstance(asm.GetType(loai.ToString()));
                                temp.Add(t.NameAI);
                                break;
                            }
                        }
                    }
                }
            }
            return temp.ToArray();
        }
    }
}
