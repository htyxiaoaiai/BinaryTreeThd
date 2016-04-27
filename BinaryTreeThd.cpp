# BinaryTreeThd
二叉树的线索化
#include"BinaryTreeThreaded.h"

void TestBinaryThreeTh()
{
	int a1[10] = { 1,2,3,'#','#',4,'#','#',5,6 };
	int a2[15] = { 1,2,'#',3,'#','#',4,5,'#',6 ,'#' ,7,'#' ,'#' ,8 };
	//BinaryTreeThd<int> t1(a2,15,'#');
	BinaryTreeThd<int> t1(a1, 10, '#');
	//t1.PrevOrderThreading();
	//t1.InOrderThreading();
	//cout << "先序遍历 " << endl;
	//t1.PrevOrderThd();
	//cout << "中序遍历" << endl;
	//t1.InOrderThd();
	t1.PosOrderThreading();
	cout << "后序遍历" << endl;
	t1.PosOrderThd();
}
int main()
{
	TestBinaryThreeTh();
	getchar();
	return 0;
}
