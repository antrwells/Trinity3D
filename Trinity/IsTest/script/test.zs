class test

    int best,other

    method void test()

        best = 40
        other = 15

    end 

    method int get()

        return best

    end 

end 

class IDE


    
    method void InitIDE()

        test t1 = new test()

        console(t1.get(),t1.other)


    end 

end 
