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

        public object Test
        {
            get;
            set;
        }

        public int Hey(object b)
        {

            Test = b;

            return 200;

        }

    }
}
