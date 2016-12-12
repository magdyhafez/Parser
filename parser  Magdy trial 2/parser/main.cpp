#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "scanner.h"
//#include "Tree.h"
#include "treeNode.h"
using namespace std;

void read_stmt();
bool match(string expectedToken);
TreeNode* exp();
void simpleExp();
void addop();
void comparisonop();
TreeNode* term();
void mulop();
TreeNode* factor();
vector<TreeNode*> Syntaxtree; 

int main()
{
	
    string line ;
    queue<string> Queue;
    ifstream myfile ("examples.txt");
    // reading from file
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            getline (myfile,line);
            Queue.push(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

	scannerOutput(Queue);
	//parser parse;
	read_stmt();
	cout <<endl;
	//TreeNode* testTree = Syntaxtree[0];
	//cout<<testTree->getTokenValue()<<"   "<<testTree->getTokenType()<<endl;
	Syntaxtree[0]->traverseTree();
	/*while (!TokenTypesFinished() && !TokenValuesFinished())
	{
		cout << getTokenValue() << "   " << getTokenType() << endl;
		advanceToken();
	}*/
	
	getchar();
	return 0;
}
TreeNode* exp()
{
	simpleExp();
	while(!(getTokenValue() == ";"))
	{
		comparisonop();
		simpleExp();
	}
}
void simpleExp()
{
	term();
	while(!(getTokenValue() == ";"))
	{
		addop();
		term();
	}
}

TreeNode* term()
{
	TreeNode* t;
	t=factor();
	while(!(getTokenValue() == ";"))
	{
		mulop();
		factor();
	}
}
void comparisonop()
{
	if(match("<") || match("="))
		;
	else
		cout<<"comparison op missing"<<endl;
}

void mulop()
{
	if(match("*") || match("/"))
		;
	else
		cout<<"mulop missing"<<endl;
}

void addop()
{
	if(match("+") || match("-"))
		;
	else
		cout<<"addop missing"<<endl;
}

TreeNode* factor()
{
	if(match("("))
	{
		bool b;
		TreeNode* temp1 = exp();
		advanceToken();
		b = match(")");
		advanceToken();
		return temp1;
	}
	else if (match("number"))
	{
		TreeNode* temp = new TreeNode("number", getTokenValue());
		advanceToken();
		return temp;
	}//correct
	else if (match("identifier"))
	{
		TreeNode* temp = new TreeNode("identifier", getTokenValue());
		advanceToken();
		return temp;
	}//correct
	else
		//return NULL//Not sure
		cout<<"factor error"<<endl;
	return NULL;//Not sure
}

void read_stmt()
{
	//treeNode* temp1;
	if(match("read"))
	{
//		tree ptr_treenode ;
		TreeNode* temp1 = new TreeNode("reserved word", "read");
	//	ptr_treenode.setptr(temp1);
		Syntaxtree.push_back(temp1);
		advanceToken();
		if(match("identifier"))
		{
			TreeNode* temp = new TreeNode("identifier", "x");
			//advanceToken();
			temp1->setChild(temp,0);
		}
		else
		{
			cout<<"missing identifier"<<endl;
		}

	}
	else
		cout<< "read_stmt error"<<endl;
}
bool match(string expectedToken)
{
	if(getTokenValue() == expectedToken)
	{
		cout<<"true";
		//advanceToken();
		return true;//advance token vector
	}
	else if(getTokenType() == expectedToken)
	{	
		cout<<"true";
		//advanceToken();
		return true;//advance token vector
	}
	else
	{
			cout << "Error" <<"-->";
			return false;
	}
}