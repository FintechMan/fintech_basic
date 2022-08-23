/**
 * @author FintechMan
 * @date   2022.08.17
 * @brief  数据结构相关对象单元测试入口
*/

#include "binary_search_tree.h"

using namespace std;

int bst_test()
{
	NodeInfo info[7] = { {1, 8}, {5, 10}, {10, 8}, {7, 6}, {5, 12}, {4, 8}, {3, 9}};

	BinarySearchTree tree;
	for (int i = 0; i < 7; i++)
	{
		tree.insertNode(info[i]);
	}

	const BinarySearchTreeNode* root = tree.getRoot();

	std::cout << "preOrderNode: " << std::endl;
	tree.preOrderNode(root);

	std::cout << "inOrderNode: " << std::endl;
	tree.inOrderNode(root);

	std::cout << "postOrderNode: " << std::endl;
	tree.postOrderNode(root);

	BinarySearchTreeNode* node = nullptr;
	BinarySearchTreeNode* pNode = nullptr;
	node = tree.searchNode(10, &pNode);
	std::cout << "node: " << node->info->key << " " << node->info->data << std::endl;
	std::cout << "pNode: " << pNode->info->key << " " << pNode->info->data << std::endl;

	tree.deleteNode(5);

	root = tree.getRoot();
	std::cout << "after delete node preOrderNode: " << std::endl;
	tree.preOrderNode(root);


	return 0;
}

int main()
{
	bst_test();

	cout << "Hello CMake。" << endl;

	system("pause");
	return 0;
}
