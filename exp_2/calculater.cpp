#include <iostream>
#include <string>

enum nodeType {num,opr};

union nodeData{double number;char opra;};
class Node
{
private:
    nodeType type;
    nodeData data;
public:
    Node(double number);
    Node(char opra);
    void show();
    nodeType getType(){return type;}
    double getnumber()const;
    char getoprand()const;
    Node* next;   
    ~Node();

};
double Node::getnumber()const{
    if(type==nodeType::num)
        return data.number;
    throw "wrong";
    }
char Node::getoprand()const{
    if(type==nodeType::opr)
        return data.opra;
    throw "wrong";
    }
Node::Node(double number){type=nodeType::num;data.number=number;}
Node::Node(char c){type=nodeType::opr;data.opra=c;}
void Node::show(){
    if(type==nodeType::num) 
        std::cout<<data.number;
    else
        std::cout<<data.opra;
    }
Node::~Node()
{}


class MyStack
{
private:
    Node* top;
    int n;
public:
    
    Node pop();
    Node TopNode() const;//看一下const的函数是不是会在这种情况下act
    void push(const Node& n);
    void push(Node* n);
    int size();
    void show();
    MyStack();
    ~MyStack();
};

Node MyStack::TopNode() const{
    if(top==nullptr) std::cout << "nomore thing";
    return *top;}
void MyStack::show(){
    for (Node* p = top;p!=nullptr; p=p->next)
    {
        p->show();
        std::cout<<std::endl;
    }
}
void MyStack::push(const Node& node){
    Node* new_top =new Node(node);
    new_top->next=top;
    top=new_top;
    n=n+1;
    }
void MyStack::push(Node* new_top){
    new_top->next=top;
    top=new_top;
    n=n+1;
}

Node MyStack:: pop(){
    Node *old_top=top;
    Node temp=*old_top;
    top=top->next;
    delete old_top;
    n=n-1;
    return temp;
}

MyStack::MyStack()
{
    top=nullptr;
    n=0;
}
int MyStack::size(){
    return n;
}
MyStack::~MyStack()
{
    while (top!=nullptr)
    {
        Node* old_top=top;
        top=top->next;
        delete old_top;
    }
    
}

class calculator:public MyStack{
    public:
    //1,看下const怎么调用函数，2，看下与父类不同怎么操作的
        void push(const Node& node)
        {
         switch (Node(node).getType())
         {
         case nodeType::num:
            MyStack::push(node);
            break;
        case nodeType::opr:
        Node n2=pop(),n1=pop();

        switch (node.getoprand())
        {
        case '+':
            MyStack::push(n1.getnumber()+n2.getnumber());
            break;
        case '-':
            MyStack::push(n1.getnumber()-n2.getnumber());
            break;
        case '*':
            MyStack::push(n1.getnumber()*n2.getnumber());
            break;    
        case '/':
            MyStack::push(n1.getnumber()/n2.getnumber());
            break;
        }
            break;
        }   
        }
};

void problem(std::string str){
    std::cout<<"有错误:"<<str<<std::endl;
    std::abort();
}



int main(int argc, char const *argv[])
{
    calculator stack;
    MyStack oprandstack;
    std::string str;
    char c;
    while (true) 
    {
        std::cin.get(c);

        if (c == '\n') {
            if(str.length()!=0)
                stack.push(std::stod(str)),str.clear();
            break;}

        else if(c=='('||c=='*'||c=='/'||c=='['||c=='{'){
            if(str.length()!=0)
            stack.push(std::stod(str)),str.clear();
                oprandstack.push(c);
            }

        else if(c=='+'||c=='-'){
            
            if(str.length()!=0)
            stack.push(std::stod(str)),str.clear();

            
            while((oprandstack.size()!=0)&&(oprandstack.TopNode().getoprand()=='*'||oprandstack.TopNode().getoprand()=='/'))
            {   
                stack.push(oprandstack.pop());
            }

            oprandstack.push(c);
        }

        else if (c==')'||c==']'||c=='}')
        {
            if(str.length()!=0) stack.push(std::stod(str)),str.clear();
            if (oprandstack.size()==0) problem("右括号多了");
            char left_oprand;
            while(left_oprand=oprandstack.pop().getoprand(), left_oprand != '(' && left_oprand!='['&&left_oprand!='{')
            {
            stack.push(left_oprand);
            if (oprandstack.size()==0){problem("右括号多了");}
            }
            //left_oprand = oprandstack.pop().getoprand();
            if(!(c==')'&&left_oprand=='('  ||c==']'&&left_oprand=='['  ||c=='{'&&left_oprand=='}')){problem("符号不匹配");}
            
        }

        else if((c>='0'&&c<='9')||(c=='.')) str.push_back(c);
        else problem("输错东西了");
                
    }

    while (oprandstack.size()>0)
        stack.push(oprandstack.pop());
    
    stack.show();

    return 0;
}
