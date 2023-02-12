using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace TrinityNET
{
    public  class Link
    {

        [DllImport("TrinityLink.dll")]
        public static extern void CheckTest(int a);

    }
}
