#include "binary_search_tree.h"

BinarySearchTree::BinarySearchTree(NodeInfo* info)
{
	m_root = createNode(info);
}

BinarySearchTree::BinarySearchTree()
{
	m_root = createDefNode();
}

BinarySearchTree::~BinarySearchTree()
{
	this->postOrderNode(m_root, &BinarySearchTree::delNode);
	m_root = nullptr;
}

BinarySearchTreeNode* BinarySearchTree::searchNode(KEY_TYPE key, BinarySearchTreeNode** PNode)
{
	BinarySearchTreeNode* root = m_root;
	BinarySearchTreeNode* p = nullptr; //缓存父结点

	while (root)
	{		
		if (compareKey(root->info->key, key) > 0)
		{
			p = root;
			root = root->lChild;
		}
		else if (compareKey(root->info->key, key) < 0)
		{
			p = root;
			root = root->rChild;
		}
		else
		{
			break;
		}		
	}

	*PNode = p;
	return root;
}

int BinarySearchTree::insertNode(const NodeInfo& info)
{
	BinarySearchTreeNode* root = m_root;
	BinarySearchTreeNode* p = nullptr;	
	int isOnLeft = -1;

	while (root)
	{
		p = root;
		if (compareKey(root->info->key, info.key) > 0)
		{
			isOnLeft = 1;
			root = root->lChild;
		}
		else if (compareKey(root->info->key, info.key) < 0)
		{
			isOnLeft = 2;
			root = root->rChild;
		}
		else
		{
			isOnLeft = 0;
			break;
		}
	}

	switch (isOnLeft)
	{
		case 0: /*自身*/
			this->updateNode(p, info);
			break;
		case 1: /*插入左孩子*/	
			p->lChild = createNode(&info);
			break;
		case 2: /*插入右孩子*/
			p->rChild = createNode(&info);
			break;
	    default: /*空树*/
			m_root = createNode(&info);;
		    break;
	}
	return 0;
}

int BinarySearchTree::deleteNode(KEY_TYPE key)
{
	BinarySearchTreeNode* pNode = nullptr;
	BinarySearchTreeNode* node = this->searchNode(key, &pNode);

	//被删除结点不存在
	if (node == nullptr)
	{
		return -1;
	}

	int flag = 0;
	if (pNode == nullptr) //根结点
	{
		flag = 0;
	}
	else if (!isEmptyNode(pNode->lChild) && compareKey(pNode->lChild->info->key, key) == 0) /*待删除结点为左孩子*/
	{
		flag = -1;
	}
	else if (!isEmptyNode(pNode->rChild) && compareKey(pNode->rChild->info->key, key) == 0) /*待删除结点为右孩子*/
	{
		flag = 1;
	}
	
	if (node->lChild == nullptr && node->rChild == nullptr) /*叶子结点*/
	{
		if (flag == -1) /*待删除结点为左孩子*/
		{
			pNode->lChild = nullptr;
		}
		else if(flag == 1) /*待删除结点为右孩子*/
		{
			pNode->rChild = nullptr;
		}
		else
		{
			m_root = nullptr;
		}
		this->delNode(node);		
	}
	else if (node->lChild == nullptr &&  node->rChild != nullptr)	/*非叶子结点(只有一颗子树)*/	
	{
		if (flag == -1)
		{
			pNode->lChild = node->rChild;
		}
		else if (flag == 1)
		{
			pNode->rChild = node->rChild;
		}
		else
		{
			m_root = node->rChild;
		}
		this->delNode(node);
	}
	else if (node->lChild != nullptr &&  node->rChild == nullptr)
	{
		if (flag == -1)
		{
			pNode->lChild = node->lChild;
		}
		else if (flag == 1)
		{
			pNode->rChild = node->lChild;
		}
		else
		{
			m_root = node->lChild;
		}
		this->delNode(node);
	}
	else if (node->lChild != nullptr && node->rChild != nullptr) 	// 有两颗子树
	{
		//取左子树最大结点替换为被删除结点，然后删除左子树最大结点；
		//或取右子树最小结点替换为被删除结点，然后删除右子树最小结点

		//左子树最大结点
		BinarySearchTreeNode* leftMaxNode = node->lChild; 
		//左子树最大结点的父节点
		BinarySearchTreeNode* pLeftMaxNode = node;
		while (leftMaxNode->rChild != nullptr)
		{
			pLeftMaxNode = leftMaxNode;
			leftMaxNode = leftMaxNode->rChild;
		}
	
		//将左子树最大结点替换为被删除结点
		if (node->lChild != leftMaxNode)
		{ 
			//如果左子树最大结点，即为被删结点的左子树，则不应该改变该最大结点的左子树指向，不然会使得该结点指向自己
			leftMaxNode->lChild = node->lChild;
		}		
		leftMaxNode->rChild = node->rChild;
		if (flag == -1)
		{
			pNode->lChild = leftMaxNode; /*如果被删结点为左子树结点，将父节点指向左子树*/
		}
		else if (flag == 1)
		{
			pNode->rChild = leftMaxNode; /*如果被删结点为右子树结点，将父节点指向右子树*/
		}
		else
		{
			m_root = leftMaxNode; /*如果被删结点为根结点，直接替换*/
		}

		//左子树最大结点的父节点,变为叶子结点
		pLeftMaxNode->rChild = nullptr;
		
		this->delNode(node);
	}

	return 0;
}

int BinarySearchTree::updateNode(BinarySearchTreeNode* node, const NodeInfo& info)
{
	if (isEmptyNode(node))
	{
		return 0;
	}

	if (node->info->key != info.key)
	{
		return 0;
	}

	node->info->data = info.data;

	return 0;
}

BinarySearchTreeNode * BinarySearchTree::createDefNode()
{
	return nullptr;
}

BinarySearchTreeNode * BinarySearchTree::createNode(const NodeInfo * info)
{
	if (info == nullptr)
	{
		return createDefNode();
	}
	BinarySearchTreeNode* node = new BinarySearchTreeNode();
	node->info = new NodeInfo();

	node->info->key = info->key;
	node->info->data = info->data;
	node->lChild = NULL;
	node->rChild = NULL;

	return node;
}

void BinarySearchTree::visitNode(const BinarySearchTreeNode * node)
{
	if (isEmptyNode(node))
	{
		return;
	}
	std::cout << "key: " << node->info->key << " data: " << node->info->data << std::endl;
}

void BinarySearchTree::delNode(const BinarySearchTreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->info != nullptr)
	{
		delete node->info;
	}
	delete node;
}

bool BinarySearchTree::isEmptyNode(const BinarySearchTreeNode * node)
{
	return node == nullptr || node->info == nullptr;
}

const BinarySearchTreeNode * BinarySearchTree::getRoot()
{
	return m_root;
}

void BinarySearchTree::preOrderNode(const BinarySearchTreeNode * node, VisitFunc visit)
{
	if (isEmptyNode(node))
	{
		return;
	}

	(this->*visit)(node); //成员函数指针作为函数参数的调用
	this->preOrderNode(node->lChild, visit);
	this->preOrderNode(node->rChild, visit);
}

void BinarySearchTree::inOrderNode(const BinarySearchTreeNode * node, VisitFunc visit)
{
	if (isEmptyNode(node))
	{
		return;
	}

	this->inOrderNode(node->lChild, visit);
	(this->*visit)(node);
	this->inOrderNode(node->rChild, visit);
}

void BinarySearchTree::postOrderNode(const BinarySearchTreeNode * node, VisitFunc visit)
{
	if (isEmptyNode(node))
	{
		return;
	}

	this->postOrderNode(node->lChild, visit);	
	this->postOrderNode(node->rChild, visit);
	(this->*visit)(node);
}

int compareKey(KEY_TYPE left, KEY_TYPE right)
{
	{
		if (left > right)
		{
			return 1;
		}
		else if (left < right)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}
