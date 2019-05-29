#include<iostream>
#include<string>
#include<stack>

template <class T>
struct TreeNode
{
	T data;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode(const T &x):data(x),left(NULL),right(NULL){}
};

void Inoder(TreeNode<int> *root)
{
	if(root != NULL)
	{
		Inoder(root->left);
		std::cout<<root->data;
		Inoder(root->right);
	}
}

void Pre(TreeNode<int> *root)
{
	if(root != NULL)
	{
		
		std::cout<<root->data;
		Pre(root->left);
		Pre(root->right);
	}
}

void print(TreeNode<int> *root)
{
	if(root != NULL)
	{
		print(root->left);
		print(root->right);
		std::cout<<root->data;
	}
}

void PreII(TreeNode<int> *root)
{
	if(root == NULL)
		return;
	using std::stack;
	stack<TreeNode<int> *> s;
	while(root != NULL || !s.empty())
	{
		if(root != NULL)
		{
			std::cout<<root->data;
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			s.pop();
			root = root->right;
		}
	}
}

void InoderII(TreeNode<int> *root)
{
	if(root == NULL)
		return;
	using std::stack;
	stack<TreeNode<int> *> s;
	while(root != NULL || !s.empty())
	{
		if(root != NULL)
		{
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			std::cout<<root->data;
			s.pop();
			root = root->right;
		}
	}
}


int main()
{
	//      1
	//   2     3
	// 4   5 6   7
	
	TreeNode<int> *node1 = new TreeNode<int>(1);
    TreeNode<int> *node2 = new TreeNode<int>(2);
    TreeNode<int> *node3 = new TreeNode<int>(3);
    TreeNode<int> *node4 = new TreeNode<int>(4);
    TreeNode<int> *node5 = new TreeNode<int>(5);
    TreeNode<int> *node6 = new TreeNode<int>(6);
    TreeNode<int> *node7 = new TreeNode<int>(7);
    node1->left  = node2;
    node1->right = node3;
    node2->left  = node4;
    node2->right = node5;
    node3->left  = node6;
    node3->right = node7;
	
	InoderII(node1);
	std::cout<<std::endl;
	PreII(node1);
	std::cout<<std::endl;
	print(node1);
	
	return 0;
}
