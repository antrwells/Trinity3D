using System;
using TrinityNET;

namespace Game
{
    public class TVMod : TrinityObject
    {
        public int Other
        {
            get;
            set;
        }
    }
    public class TestMod : TrinityObject
    {

        public int MyValue
        {
            get;
            set;
        }


        public int OtherValue
        {
            get;
            set;
        }

        public float Value3
        {
            get;
            set;
        }

        public void Hey()
        {
            Console.WriteLine("Testing!");
            MyValue = 25;
            Link.CheckTest(25);
        }

    }
}
