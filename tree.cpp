
#include "pch.h"
#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>


struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



void InorderPrint(TreeNode *root)
{
	if (root != NULL)
	{
		InorderPrint(root->left);
		printf("%d ", root->val);
		InorderPrint(root->right);
	}
}

int maxDepth(TreeNode* root)
{
	if (root == NULL)
		return 0;
	int leftMax = maxDepth(root->left);
	int rightMax = maxDepth(root->right);

	return leftMax > rightMax ? leftMax + 1 : rightMax + 1;
}

//Binary Search Tree

void SearchBinary_Insert(TreeNode *root, TreeNode *node)
{
	if (root == NULL)
	{
		root = node;
		return;
	}
	printf("val = %d\n", node->val);
	TreeNode *x = root;
	TreeNode *pre = NULL;
	while (x != NULL)
	{
		pre = x;
		if (x->val > node->val)
		{
			x = x->left;
		}
		else
			x = x->right;
	}

	if (node->val > pre->val)
		pre->right = node;
	else
		pre->left = node;
}

void SearchBinary_Delet(TreeNode *root, TreeNode *node)
{

}

bool isValidBST(TreeNode* root) 
{
	if (root == NULL)
		return false;
	using std::stack;
	stack<TreeNode *> s;
	int pre, cur,i = 0;
	while (root != NULL || !s.empty())
	{
		if (root != NULL)
		{
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			cur = root->val;
			s.pop();
			root = root->right;
			if (i == 0)
			{
				pre = cur;
				i++;
			}
			else
			{
				if (pre > cur)
					return false;
				pre = cur;
			}
			
		}
	}
	return true;
}



int main()
{
	//      2
	//   1     3

	TreeNode *node1 = new TreeNode(10);
	TreeNode *node2 = new TreeNode(5);
	TreeNode *node3 = new TreeNode(15);
	TreeNode *test = NULL;
	TreeNode *node4 = new TreeNode(4);
	node1->left = node2;
	node1->right = node3;

	TreeNode *tmp = NULL;
	for (int i = 7; i < 10; i++)
	{
		tmp = new TreeNode(i);
		SearchBinary_Insert(node1, tmp);
	}

	printf("\n------------------\n");
	InorderPrint(node1);
	printf("\n%d\n", maxDepth(node1));
	if (isValidBST(test))
		printf("hahhaha\n");
	return 0;
}
