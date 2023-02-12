using System;


namespace TestLib
{
    public class Class1
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
        }

    }
}
