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
        std::cout<<"操作数:"<<data.number<<"\n";
    else
        std::cout<<"操作符:"<<data.opra<<"\n";
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
int Myctoi(char c){return c-'0';}
double Mystod(std::string str){
    double result=0,lresult=0;
    int isdouble=0;
    for (char c:str)
    {
        if (c=='.')
        {
            isdouble=1;
            break;
        }
        
    }
    if(isdouble){
    int i;
    for(i=0;str[i]!='.';i++)
    {
        result*=10;
        result+=Myctoi(str[i]);
    }
    for(int j=str.length()-1;j>i;j--)
    {
        lresult*=0.1;
        lresult+=0.1*Myctoi(str[j]);
    }
    return result+lresult;
    }
    else{
        for(int i=0;i<str.length();i++)
    {
        result*=10;
        result+=Myctoi(str[i]);
    }
    return result;
    }
    return 0;
}


void problem(std::string str){
    std::cout<<"有错误:"<<str<<std::endl;
    std::abort();
}



void show(Node n){n.show();}
int main(int argc, char const *argv[])
{
    MyStack oprandstack;
    MyStack numstack;
    std::string str;
    char c;
    while (true) 
    {
        std::cin.get(c);
        if (c == '\n') {
            if(str.length()!=0) show(Mystod(str)),str.clear();

            if(oprandstack.size()!=0) problem("左括号多了");
            break;}

        else if(c=='['||c=='{'||c=='('||c=='*'||c=='/'||c=='+'||c=='-'){
            if(str.length()!=0) show(Mystod(str)),str.clear();
            
            if(c=='['||c=='{'||c=='(') oprandstack.push(c);
            
            show(c);
            }
        else if (c==')'||c==']'||c=='}')
        {
            
            if(str.length()!=0) show(Mystod(str)),str.clear();

            if (oprandstack.size()==0) problem("右括号多了");
            char d=oprandstack.pop().getoprand();
            if(!(c==')'&&d=='('  ||c==']'&&d=='['  ||c=='{'&&d=='}'))
            {problem("符号不匹配");}
            show(c);
        }
        else if((c>='0'&&c<='9')||(c=='.')) str.push_back(c);                
    }

}
