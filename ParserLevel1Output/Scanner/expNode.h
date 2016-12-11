#include <string>
#include <queue>
#include <vector>

using namespace std;

class expNode {
	private:
		string TokenType;
		string TokenValue;
		expNode* child[2];
	public:
		expNode(string tokentype, string tokenvalue);
		~expNode();
		void setTokenValue(string tokenvalue);
		void setTokenType(string tokentype);
		void setChild(expNode* ptr_child, int value);
		//void setSecondChild(expNode* ptr_child);
		//void setThirdChild(expNode* ptr_child);
		string getTokenValue();
		string getTokenType();
		
};

expNode::expNode(string tokentype, string tokenvalue)
{
	TokenValue = tokenvalue;
	TokenType = tokentype;
	child[0] = NULL;
	child[1] = NULL;
}

void expNode::setTokenValue(string tokenvalue)
{
	TokenValue = tokenvalue;
}

void expNode::setTokenType(string tokentype)
{
	TokenType = tokentype;
}

void expNode::setChild(expNode* ptr_child, int value)
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

string expNode::getTokenValue()
{
	return TokenValue;
}

string expNode::getTokenType()
{
	return TokenType;
}

expNode::~expNode()
{
	delete[] child;
}
