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
        //std::cout<<"this time we have"<<Myctoi(str[i])<<"\n";
        result*=10;
        result+=Myctoi(str[i]);
    }

    std::cout<<"-------------\n";

    for(int j=str.length()-1;j>i;j--)
    {
        //std::cout<<"this time we have"<<Myctoi(str[j])<<"\n";
        lresult*=0.1;
        lresult+=0.1*Myctoi(str[j]);
    }
    return result+lresult;
    }

    else
    {
        std::cout<<"isint\n";
        for(int i=0;i<str.length();i++)
    {
        //std::cout<<"this time we have"<<Myctoi(str[i])<<"\n";
        result*=10;
        result+=Myctoi(str[i]);
    }
    return result;
    }
    return 0;
}
