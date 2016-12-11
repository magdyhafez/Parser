#ifndef TREE_H
#define TREE_H
#include <string>
#include <queue>
#include <vector>
#include "treeNode.h" 

using namespace std;

class tree{
private:
	TreeNode* ptr_node;
public:
	tree()
	{
		ptr_node = NULL;
	}
	~tree()
	{
		delete ptr_node;
	}
	void setptr(TreeNode* ptr)
	{
		ptr_node = ptr;
	}
};

//tree::tree()
//{
//	ptr_node = NULL;
//}
//void tree::setptr(treeNode* ptr)
//{
//	ptr_node = ptr;
//}
#endif