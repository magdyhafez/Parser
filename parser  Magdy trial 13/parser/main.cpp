#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "scanner.h"
//#include "Tree.h"
#include "treeNode.h"
using namespace std;

TreeNode* assign_stmt();
TreeNode* write_stmt();
TreeNode* read_stmt();
bool match(string expectedToken);
TreeNode* exp();
TreeNode* simpleExp();
TreeNode* addop();
TreeNode* comparisonop();
TreeNode* term();
TreeNode* mulop();
TreeNode* factor();
vector<TreeNode*> Syntaxtree;

int main()
{

	string line;
	queue<string> Queue;
	ifstream myfile("examples.txt");
	// reading from file
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			Queue.push(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	scannerOutput(Queue);
	//parser parse;
	Syntaxtree.push_back(assign_stmt());
	cout << endl;
	//TreeNode* testTree = Syntaxtree[0];
	//cout<<testTree->getTokenValue()<<"   "<<testTree->getTokenType()<<endl;
	if (Syntaxtree[0] != NULL)Syntaxtree[0]->traverseTree();
	/*while (!TokenTypesFinished() && !TokenValuesFinished())
	{
	cout << getTokenValue() << "   " << getTokenType() << endl;
	advanceToken();
	}*/

	getchar();
	return 0;
}
TreeNode* assign_stmt()
{
	TreeNode* t1=NULL;
	if (match("identifier"))
	{
		TreeNode* t = new TreeNode("identifier",getTokenValue());
		advanceToken();
		if (t != NULL)
		{
			if (match(":="))
			{
				if (t1 != NULL) 
				{
					t1->setChild(t, 0);
					t1->setChild(exp(), 1);
				}
				t = t1;
				cout << "in inner if";
				return t1;
			}
			else {
				cout << "error assignment identifier";
			}
		}
		cout << "in if";
		return t1;
	
	}
	else
	{
		cout << "assignment statment error";
		cout << "in else";
		return NULL;
	}
}
TreeNode* write_stmt()
{
	if (match("write"))
	{
		TreeNode* t = new TreeNode("reserved", "read");
		advanceToken();
		if (t != NULL)
		{
			t->setChild(exp(), 0);
		}
		return t;
	}

}
TreeNode* exp()
{
	TreeNode* t;
	t = simpleExp();
	TreeNode* t1;
	while ((getTokenValue() == "<") || (getTokenValue() == "="))
	{
		t1 = comparisonop();
		if (t1 != NULL)
		{
			t1->setChild(t, 0);
			t1->setChild(simpleExp(), 1);
			t = t1;
		}
	}
	return t;
}

TreeNode* simpleExp()
{
	TreeNode* t;
	t = term();
	TreeNode* t1;
	while ((getTokenValue() == "+") || (getTokenValue() == "-"))
	{
		t1 = addop();
		if (t1 != NULL)
		{
			t1->setChild(t, 0);
			t1->setChild(term(), 1);
			t = t1;
		}
	}
	return t;
}

TreeNode* term()
{
	TreeNode* t;
	t = factor();
	int i = 0;
	TreeNode* t1;
	while ((getTokenValue() == "*") || (getTokenValue() == "/"))
	{
		t1 = mulop();
		if (t1 != NULL)
		{
			t1->setChild(t, 0);
			t1->setChild(factor(), 1);
			t = t1;
		}
	}
	return t;
}
TreeNode* comparisonop()
{
	if (match("<") || match("="))
	{
		TreeNode* temp = new TreeNode("comparisonop", getTokenValue());
		advanceToken();
		return temp;

	}

	else
	{
		advanceToken();
		cout << "comparisonop missing" << endl;
		return NULL;
	}
}

TreeNode* mulop()
{
	if (match("*") || match("/"))
	{
		TreeNode* temp = new TreeNode("mulop", getTokenValue());
		advanceToken();
		return temp;

	}

	else
	{
		advanceToken();
		cout << "mulop missing" << endl;
		return NULL;
	}
}

TreeNode* addop()
{
	if (match("+") || match("-"))
	{
		TreeNode* temp = new TreeNode("addop", getTokenValue());
		advanceToken();
		return temp;

	}

	else
	{
		//advanceToken();
		cout << "addop missing" << endl;
		
		return NULL;
	}
}
TreeNode* factor()
{
	if (match("("))
	{
		bool b;
		advanceToken();
		TreeNode* temp1 = exp();

		b = match(")");
		advanceToken();
		return temp1;
	}
	if (match("number"))
	{
		TreeNode* temp = new TreeNode("number", getTokenValue());
		advanceToken();
		cout << endl << "number";
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
		cout << "factor error" << endl;
	return NULL;//Not sure
}

TreeNode* read_stmt()
{
	//treeNode* temp1;
	if (match("read"))
	{
		//		tree ptr_treenode ;
		TreeNode* temp1 = new TreeNode("reserved word", "read");
		//	ptr_treenode.setptr(temp1);
		//Syntaxtree.push_back(temp1);
		advanceToken();
		if (match("identifier"))
		{
			TreeNode* temp = new TreeNode("identifier", getTokenValue());
			advanceToken();
			temp1->setChild(temp, 0);
			return temp1;
		}
		else
		{
			cout << "missing identifier" << endl;
			return temp1;
		}


	}
	else
		cout << "read_stmt error" << endl;
	return NULL;
}
bool match(string expectedToken)
{
	if (getTokenValue() == expectedToken)
	{
		cout << "true";
		//advanceToken();
		return true;//advance token vector
	}
	else if (getTokenType() == expectedToken)
	{
		cout << "true";
		//advanceToken();
		return true;//advance token vector
	}
	else
	{
		cout << "Error" << "-->";
		return false;
	}
}