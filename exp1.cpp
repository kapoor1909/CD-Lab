#include <iostream>
#include<fstream>
#include<string.h>
#include<vector>
#include<algorithm>
 
using namespace std;
int isKeyword(char buffer[])
{
	char keywords[33][10] = {
		"auto", "break", "case", "char", "const", "continue", "default",
		"do", "double", "else", "enum", "extern", "float", "for", "goto",
		"if", "int", "long", "register", "return", "typedef", "signed",
		"sizeof", "static", "struct", "switch", "main", "union",
		"unsigned", "void", "while","cout",
		};

	int i, flag = 0;
	for(i = 0; i < 32; ++i)
	{
		if(strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}
	
	return flag;
}
 
int main()
{
    vector<char> op, sym, constants;
    vector<string> key, id;

	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream fin("program.txt");
	int j=0;
	if(!fin.is_open())
	{
		cout<<"Error while opening the file\n";
		exit(0);
	}

	while(!fin.eof())
	{
   		ch = fin.get();
  
		for(int i=0; i<6; ++i)
   			if(ch == operators[i])
                op.push_back(ch);

        if(ch>=48 && ch<=57)
        {
            constants.push_back(ch);
            continue;
        }

		if(isalnum(ch))
			buffer[j++] = ch;
		else if( (ch==' ' || ch=='\n') && (j!=0) )
		{
			buffer[j]='\0';
			j=0;
			
			if(isKeyword(buffer)==1)
                key.push_back(buffer);
			else
                id.push_back(buffer);
		}
        else if(ch=='(' || ch=='{' || ch=='[' || ch==')' || ch=='}' || ch==']' || ch=='<' || ch=='>'|| ch=='(' || ch==')' || ch==';' || ch==',' || ch=='#')
            sym.push_back(ch);
	}

    cout<<"List of operators: ";
	op.erase( unique( op.begin(), op.end() ), op.end() );
    for(auto i: op)
        cout<<i<<" ";
    cout<<"\nTotal elements = "<<op.size();
    cout<<"\n\n";

    cout<<"List of symbols: ";
    sym.erase( unique( sym.begin(), sym.end() ), sym.end() );
    for(auto i: sym)
        cout<<i<<" ";
    cout<<"\nTotal elements = "<<sym.size();
    cout<<"\n\n";

    cout<<"List of identifiers: ";
    sort( id.begin(), id.end() );
    id.erase( unique( id.begin(), id.end() ), id.end() );
    for(auto i: id)
        cout<<i<<" ";
    cout<<"\nTotal elements = "<<id.size();
    cout<<"\n\n";

    cout<<"List of keywords: ";
    sort( key.begin(), key.end() );
    key.erase( unique( key.begin(), key.end() ), key.end() );
    for(auto i: key)
        cout<<i<<" ";
    cout<<"\nTotal elements = "<<key.size();
    cout<<"\n\n";
    
    cout<<"List of constants: ";
    constants.erase( unique( constants.begin(), constants.end() ), constants.end() );
    for(auto i: constants)
        cout<<i<<" ";
    cout<<"\nTotal elements = "<<constants.size();
    cout<<"\n\n";

	fin.close();
	return 0;
}