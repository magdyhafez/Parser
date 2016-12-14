#ifndef TREENODE_H
#define TREENODE_H
#include <string>

using namespace std;

class TreeNode {
	private:
		string TokenType;
		string TokenValue;
		TreeNode* child[4];//from 3 to 4
	public:
		TreeNode();
		TreeNode(string tokentype, string tokenvalue);
		~TreeNode();
		void setTokenValue(string tokenvalue);
		void setTokenType(string tokentype);
		void setChild(TreeNode* ptr_child, int value);
		string getTokenValue();
		string getTokenType();
		void traverseTree();
};
TreeNode::TreeNode()
{
	;
}

TreeNode::TreeNode(string tokentype, string tokenvalue)
{
	TokenValue = tokenvalue;
	TokenType = tokentype;
	child[0] = NULL;
	child[1] = NULL;
	child[2] = NULL;
	child[3] = NULL;//from 3 to 4 added line 
}
void TreeNode::traverseTree()
{
	int i = 0;
	cout<<TokenValue<<"  "<<TokenType<<endl;
	//child[i] != NULL  changed now to i != 4
	while(i != 4)
	{
		if(child[i]!=NULL)child[i]->traverseTree();
		//cout<<"child  "<<child[i]->getTokenValue()<<"  "<<child[i]->getTokenType()<<endl;
		
				i++;
	}
	/*i = 0;
	child[i] = child[i]->child[i];
		traverseTree();*/
}

void TreeNode::setTokenValue(string tokenvalue)
{
	TokenValue = tokenvalue;
}

void TreeNode::setTokenType(string tokentype)
{
	TokenType = tokentype;
}

void TreeNode::setChild(TreeNode* ptr_child, int value)
{
	child[value] = ptr_child;
}

string TreeNode::getTokenValue()
{
	return TokenValue;
}

string TreeNode::getTokenType()
{
	return TokenType;
}

TreeNode::~TreeNode()
{
	delete[] child;
}
#endif