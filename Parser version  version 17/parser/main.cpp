#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "scanner.h"
//#include "Tree.h"
#include "treeNode.h"
using namespace std;

TreeNode* repeat();
vector<TreeNode*> stmtSeq();
TreeNode* stmt();
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
	//Syntaxtree.push_back(assign_stmt());
	
	//Syntaxtree.push_back(stmt());
	//cout << endl;
	//if (Syntaxtree[0] != NULL)Syntaxtree[0]->traverseTree();
	

	//int i = 0;
	//while(!TokenValuesFinished())
	//{
	//	cout<<"head"<<endl;
	//	Syntaxtree.push_back(stmt());
	//	advanceToken();
	//	Syntaxtree[i++]->traverseTree();
	//	//cout<<"other head"<<endl;
	//}

	/*repeat
fact:= fact*x;
x := x-1;
until x = 0*/
	// remaining use stmtSeq
	vector<TreeNode*> fulltree = stmtSeq();
	/*int fulltreeSize = fulltree.size();
	cout <<"size of tree: "<<fulltreeSize<<endl;
	for (int i = 0; i < fulltreeSize; i++)
	{
		cout <<"head"<<endl;
		fulltree[i]->traverseTree();
	}*/
	fulltree[0]->traverseTree();
	/*while (!TokenTypesFinished() && !TokenValuesFinished())
	{
	cout << getTokenValue() << "   " << getTokenType() << endl;
	advanceToken();
	}*/

	getchar();
	return 0;
}
TreeNode* repeat()
{
	vector<TreeNode*> treepart;
	TreeNode* t = NULL;
	if (match("repeat"))
	{
		 t = new TreeNode("reserved word", "repeat");
		 advanceToken();
		treepart = stmtSeq();
		if (t != NULL) t->setChild(treepart[0], 0);
		if (match("until"))
		{
			//cout << "inside until";
			advanceToken();
			if (t != NULL) t->setChild(exp(), 1);
			
		}
		
		else {
			cout << "until error";
			
		}
		return t;
	}
	else
	{
		cout << "repeat statement error";
		return NULL;
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
vector<TreeNode*> stmtSeq()
{
	int i = 0;
	int treesize;
	while(!TokenValuesFinished() && getTokenValue() != "until")
	{
		Syntaxtree.push_back(stmt());
		advanceToken();
	}
	treesize = Syntaxtree.size();
	for (int l = 0; l < treesize - 1; l++)
		Syntaxtree[l]->setChild(Syntaxtree[l+1],3);
	
	//if (getLasttoken() == ";")
	//		cout<<"no semi at last stmt of program "<<endl;
	return Syntaxtree;


//from 3 to 4 commented now
	//int i = 0;
	//while(!TokenValuesFinished())
	//{
	//	Syntaxtree.push_back(stmt());
	//	advanceToken();
	//	/*if (!(match(";") && lastToken()))
	//	{
	//		cout<<"missing semi at end of statement"<<endl;
	//		break;
	//	}*/
	//}
	//cout<<"syntaxtree size: "<<Syntaxtree.size()<<endl;
	//if (getLasttoken() == ";")
	//		cout<<"no semi at last stmt of program "<<endl;
	//return Syntaxtree;
}
TreeNode* stmt()
{
	//TreeNode* t;
	// remaining if , repeat.   identifier for assign
	if (match("identifier"))
		return assign_stmt();
	else if(match("read"))
		return read_stmt();
	else if(match("write"))
		return write_stmt();
	else if(match("repeat"))
		return repeat();
	//else if (match("repeat"))
	//	return repeat();
	else
	{
		cout<<"stmt error"<<endl;
		return NULL;
	}
}

TreeNode* assign_stmt()
{
	if (match("identifier"))
	{
		TreeNode* t = new TreeNode(getTokenType(),getTokenValue());
		advanceToken();
		if (t != NULL)
		{
			if(match(":="))
			{
				advanceToken();
				t->setChild(exp(), 0);
				return t;
			}
			else
			{
				cout<<"missing assign operator "<<endl;
				return NULL;
			}
		}
		else
			return NULL;

	}
	else
		return NULL;

}
TreeNode* write_stmt()
{
	if (match("write"))
	{
		TreeNode* t = new TreeNode(getTokenType(),getTokenValue());
		advanceToken();
		if (t != NULL)
		{
			t->setChild(exp(), 0);
		}
		return t;
	}
	else 
	{
		cout << "write_stmt error"<<endl;
		return NULL;
	}

	
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
		//advanceToken();
		return true;//advance token vector
	}
	else if (getTokenType() == expectedToken)
	{
		//advanceToken();
		return true;//advance token vector
	}
	else
	{
		//cout << "Error" << "-->";
		return false;
	}
}