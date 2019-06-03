#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


//中序遍历
void InorderPrint(TreeNode *root)
{
	if (root != NULL)
	{
		InorderPrint(root->left);
		printf("%d ", root->val);
		InorderPrint(root->right);
	}
}

//树的最大深度
int maxDepth(TreeNode* root)
{
	if (root == NULL)
		return 0;
	int leftMax = maxDepth(root->left);
	int rightMax = maxDepth(root->right);

	return leftMax > rightMax ? leftMax + 1 : rightMax + 1;
}

//Binary Search Tree
//二叉搜索树的插入操作
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


//从二叉搜索树中删除一个节点
TreeNode* SearchBinary_Delet(TreeNode *root, int key)
{
	if(root == NULL)
		return root;
	TreeNode *del = NULL;
	TreeNode *cur = root;
	TreeNode *p = NULL;
	TreeNode *p_cur = NULL;
	TreeNode *tmp = NULL;
	
	//find the key
	while(cur != NULL)
	{
		p = cur;
		if(cur->val > key)
			cur = cur->left;
		else if(cur->val < key)
			cur = cur->right;
		if(cur->val == key)
		{
			if(cur == root)
				p = NULL;
			
			break;
		}
	}
	if(cur == NULL) //can't find the key
		return root;
	
	del = cur;

	if(del->left != NULL && del->right != NULL)
	{
		cur = del->right;
		//p_cur = del;
		while(cur->left != NULL)
		{
			p_cur = cur;
			cur = cur->left;
		}
		
		printf("find %d\n",cur->val);
		
		if(p_cur != NULL)
			p_cur->left = cur->right;
		
		if(cur == del->right)
		{
			cur->right = NULL;
		}
		else
			cur->right = del->right;
		
		cur->left = del->left;
		
		if(del == root)
		{
			printf("transplant root!!\n");
			root = cur;
		}
		else if(del == p->left)
			p->left = cur;
		else
			p->right = cur;
		
	}
	else if(del->left == NULL)
	{
		cur = del->right;
		if(del == root)
			root = cur;
		else if(del == p->left)
			p->left = cur;
		else
			p->right = cur;
	}
	else if(del->right == NULL)
	{
		cur = del->left;
		if(del == root)
			root = cur;
		else if(del == p->left)
			p->left = cur;
		else
			p->right = cur;
	}
	
	delete del;
	del = NULL;
	
	return root;
}

//是否为二叉搜索树
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

//不同的二叉搜索树的个数
int numTrees(int n) 
{
	std::vector<int> dp(n+1,0);
	dp[0] = 1;
	dp[1] = 1;
	int ans = 0;
	for(int i = 2;i<=n;i++)
	{
		for(int j = 0; j < i; j++)
		{
			dp[i] += dp[j]*dp[i-j-1];
		}
	}
	return dp[n];
}

//生成不同的二叉搜索树
vector<TreeNode*> getTree(int begin, int end)
{
	vector<TreeNode*> res;
	if(begin > end)
		res.push_back(NULL);
	
	for(int i = begin; i <= end ;i++)
	{
		vector<TreeNode*> lefts  = getTree(begin,i-1);
		vector<TreeNode*> rights = getTree(i+1,end);
		for(int j = 0; j < lefts.size(); j++)
		{
			for(int k = 0; k < rights.size();k++)
			{
				TreeNode *root = new TreeNode(i);
				root->left = lefts[j];
				root->right = rights[k];
				res.push_back(root);
			}
		}
	}
	return res;
		
}

vector<TreeNode*> generateTrees(int n) 
{
	if(n == 0)
		return vector<TreeNode*>{};
	else
		return getTree(1,n);
}

void BreadthFirstSearch(TreeNode *root)
{
	if(root == NULL)
		return;
	queue<TreeNode*> q;
	TreeNode* tmp = NULL;
	q.push(root);
	while(!q.empty())
	{
		tmp = q.front();
		q.pop();
		printf("%d ",tmp->val);
		if(tmp->left)
			q.push(tmp->left);
		if(tmp->right)
			q.push(tmp->right);
	}
	printf("\n");
}



int main()
{
	//      10
	//   5     15

	TreeNode *node1 = new TreeNode(10);
	TreeNode *node2 = new TreeNode(5);
	TreeNode *node3 = new TreeNode(15);
	TreeNode *test = NULL;
	TreeNode *node4 = new TreeNode(4);
	node1->left = node2;
	node1->right = node3;

	BreadthFirstSearch(node1);
	TreeNode *tmp = NULL;
	
	tmp = new TreeNode(16);
	SearchBinary_Insert(node1, tmp);
	
	tmp = new TreeNode(14);
	SearchBinary_Insert(node1, tmp);
	
	tmp = new TreeNode(13);
	SearchBinary_Insert(node1, tmp);
	
	tmp = new TreeNode(12);
	SearchBinary_Insert(node1, tmp);

	printf("\n------------------\n");
	InorderPrint(node1);
	printf("\n%d\n", maxDepth(node1));
	
	printf("\n------------------\n");
	node1 = SearchBinary_Delet(node1,5);
	
	printf("\n------------------\n");
	InorderPrint(node1);
	printf("\n%d\n", maxDepth(node1));
	
	int i;
	while(~scanf("%d",&i))
	{
		vector<TreeNode*> ans;
		ans = generateTrees(i);
		printf("hahahah\n");
		printf("creat %d\n",ans.size());
		for(int i = 0; i < ans.size();i++)
		{
			BreadthFirstSearch(ans[i]);
		}
		ans.clear();
		printf("%d\n",numTrees(i));
		
	}
	
	return 0;
}
