#include <iostream>
//class ga
//{public:virtual void fun()=0;};


class Fa
{
    public:
        Fa(){std::cout<<"mkfa";}
        virtual void fun() {std::cout<<1;}
        ~Fa(){std::cout<<"defa";}
};
class So :public Fa{
    public:
        So(){std::cout<<"mkson";}
        void fun() {std::cout<<2;}
        ~So(){std::cout<<"deson";}
};
void run(Fa &obj){
    obj.fun();
}

int main(int argc, char const *argv[])
{
    So* s=new So();

    s->fun();
    delete(s);
    return 0;
}
