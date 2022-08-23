#ifndef __FINTECH_BASIC_DS_BINARY_TREE_H__
#define __FINTECH_BASIC_DS_BINARY_TREE_H__

/**
 * @author FintechMan
 * @date   2022.08.17
 * @brief  封装二叉查找树相关操作 
 * @knowledge point:
    二叉查找树( binary search tree)是一棵二叉树，可能为空；一棵非空的二叉查找树满足以下特征:
      1. 每个元素有一个关键字，并且任意两个元素的关键字都不同;因此，所有的关键字都是唯一的。
      2. 在根节点的左子树中，元素的关键字（如果有的话）都小于根节点的关键字。
      3. 在根节点的右子树中，元素的关键字（如果有的话）都大于根节点的关键字。
      4. 根节点的左、右子树也都是二叉查找树。
*/

typedef int KEY_TYPE;
typedef int DATA_TYPE;

#include "non_copyable.h"
#include <iostream>

/*结点信息*/
struct NodeInfo 
{
	KEY_TYPE  key; 
	DATA_TYPE data;
};

/*结点*/
struct BinarySearchTreeNode: public NonCopyable
{
	NodeInfo* info;
	BinarySearchTreeNode* lChild; 
	BinarySearchTreeNode* rChild; 
};

/*二叉查找树*/
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

