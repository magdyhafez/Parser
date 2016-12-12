//#include <iostream>
//#include <string>
//#include <queue>
//#include <vector>
//#include "scanner.h"
//#include "Tree.h"
//#include "treeNode.h"
//using namespace std;
//
//	//void read_stmt();
//	//bool match(string expectedToken);
//
////void parser::read_stmt()
////{
////	treeNode* temp1;
////	if(match("read"))
////	{
////		tree* ptr_treenode ;
////		temp1 = new treeNode("reserved word", "read");
////		ptr_treenode->setptr(temp1);
////		if(match("identifier"))
////		{
////			treeNode* temp = new treeNode("identifier", "x");
////			temp1->setChild(temp,0);
////		}
////	}
////	else
////		cout<< "read_stmt error"<<endl;
////}
//bool match(string expectedToken)
//{
//	if(getTokenValue() == expectedToken)
//	{
//		//advanceToken();
//		return true;//advance token vector
//	}
//	else if(getTokenType() == expectedToken)
//	{	
//		//advanceToken();
//		return true;//advance token vector
//	}
//	else
//	{
//			cout << "Error" << endl;
//			return false;
//	}
//}
//
