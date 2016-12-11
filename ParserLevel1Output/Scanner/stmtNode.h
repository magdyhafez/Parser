#include <string>
#include <queue>
#include <vector>
#include "Tree.h" 

using namespace std;

class stmtNode :: treeNode {
	private:
		string TokenType;
		string TokenValue;
		stmtNode* child[3];
	public:
		stmtNode(string tokentype, string tokenvalue);
		~stmtNode();
		void setTokenValue(string tokenvalue);
		void setTokenType(string tokentype);
		void setChild(stmtNode* ptr_child, int value);
		//void setSecondChild(stmtNode* ptr_child);
		//void setThirdChild(stmtNode* ptr_child);
		string getTokenValue();
		string getTokenType();
		
};

stmtNode::stmtNode(string tokentype, string tokenvalue)
{
	TokenValue = tokenvalue;
	TokenType = tokentype;
	child[0] = NULL;
	child[1] = NULL;
	child[2] = NULL;
}

void stmtNode::setTokenValue(string tokenvalue)
{
	TokenValue = tokenvalue;
}

void stmtNode::setTokenType(string tokentype)
{
	TokenType = tokentype;
}

void stmtNode::setChild(stmtNode* ptr_child, int value)
{
	child[value] = ptr_child;
}

//void treeNode::setSecondChild(treeNode* ptr_child)
//{
//	child[1] = ptr_child;
//}
//
//void treeNode::setThirdChild(treeNode* ptr_child)
//{
//	child[2] = ptr_child;
//}

string stmtNode::getTokenValue()
{
	return TokenValue;
}

string stmtNode::getTokenType()
{
	return TokenType;
}

stmtNode::~stmtNode()
{
	delete[] child;
}
