#ifndef __FINTECH_BASIC_DS_BINARY_TREE_H__
#define __FINTECH_BASIC_DS_BINARY_TREE_H__

/**
 * @author FintechMan
 * @date   2022.08.17
 * @brief  ��װ�����������ز��� 
 * @knowledge point:
    ���������( binary search tree)��һ�ö�����������Ϊ�գ�һ�÷ǿյĶ��������������������:
      1. ÿ��Ԫ����һ���ؼ��֣�������������Ԫ�صĹؼ��ֶ���ͬ;��ˣ����еĹؼ��ֶ���Ψһ�ġ�
      2. �ڸ��ڵ���������У�Ԫ�صĹؼ��֣�����еĻ�����С�ڸ��ڵ�Ĺؼ��֡�
      3. �ڸ��ڵ���������У�Ԫ�صĹؼ��֣�����еĻ��������ڸ��ڵ�Ĺؼ��֡�
      4. ���ڵ����������Ҳ���Ƕ����������
*/

typedef int KEY_TYPE;
typedef int DATA_TYPE;

#include "non_copyable.h"
#include <iostream>

/*�����Ϣ*/
struct NodeInfo 
{
	KEY_TYPE  key; 
	DATA_TYPE data;
};

/*���*/
struct BinarySearchTreeNode: public NonCopyable
{
	NodeInfo* info;
	BinarySearchTreeNode* lChild; 
	BinarySearchTreeNode* rChild; 
};

/*���������*/
class BinarySearchTree: public NonCopyable
{
public:
	BinarySearchTree(NodeInfo* info);
	BinarySearchTree();
	~BinarySearchTree();

public:

	const BinarySearchTreeNode* getRoot();
	typedef void(BinarySearchTree::*VisitFunc)(const BinarySearchTreeNode* node);

	void preOrderNode(const BinarySearchTreeNode * node, VisitFunc visit= &BinarySearchTree::visitNode);
	void inOrderNode(const BinarySearchTreeNode * node, VisitFunc visit = &BinarySearchTree::visitNode);
	void postOrderNode(const BinarySearchTreeNode * node, VisitFunc visit = &BinarySearchTree::visitNode);

	BinarySearchTreeNode* searchNode(KEY_TYPE key, BinarySearchTreeNode** PNode);
	int insertNode(const NodeInfo& info);
	int deleteNode(KEY_TYPE key);
	int updateNode(BinarySearchTreeNode* node, const NodeInfo& info);

private:
	BinarySearchTreeNode* createDefNode();
	BinarySearchTreeNode* createNode(const NodeInfo* info);

	void visitNode(const BinarySearchTreeNode* node);
	void delNode(const BinarySearchTreeNode* node);
	bool isEmptyNode(const BinarySearchTreeNode* node);

private:
	BinarySearchTreeNode* m_root;
};

int compareKey(KEY_TYPE left, KEY_TYPE right);

#endif // __FINTECH_BASIC_DS_BINARY_TREE_H__

