#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::string;
using std::stack;
using std::vector;
using std::queue;
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void PostPrint(TreeNode *root)
{
	if(root != NULL)
	{
		PostPrint(root->left);
		PostPrint(root->right);
		printf("%d ",root->val);
	}
}

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
	if (root == NULL)
		return root;

	TreeNode *del = NULL;
	TreeNode *cur = root;
	TreeNode *p = NULL;
	TreeNode *p_cur = NULL;
	TreeNode *tmp = NULL;

	//find the key
	while (cur != NULL && cur->val != key)
	{
		p = cur;
		if (cur->val > key)
			cur = cur->left;
		else if (cur->val < key)
			cur = cur->right;
	}
	if (cur == NULL) //can't find the key
		return root;

	if (cur == root)
		p = NULL;

	del = cur;

	if (del->left != NULL && del->right != NULL)
	{
		cur = del->right;
		//p_cur = del;
		while (cur->left != NULL) //寻找del的后继节点
		{
			p_cur = cur;
			cur = cur->left;
		}

		printf("find %d\n", cur->val);

		if (p_cur != NULL)//不是根节点
		{
			if (cur == p_cur->left)
				p_cur->left = cur->right;
			else
				p_cur->right = cur->right;
		}

		if (cur == del->right)
		{
			cur->right = NULL;
		}
		else
			cur->right = del->right;

		cur->left = del->left;

		if (del == root)
		{
			printf("transplant root!!\n");
			cur->left = root->left;
			root = cur;
		}
		else if (del == p->left)
			p->left = cur;
		else
			p->right = cur;

	}
	else if (del->left == NULL)
	{
		cur = del->right;
		if (del == root)
			root = cur;
		else if (del == p->left)
			p->left = cur;
		else
			p->right = cur;
	}
	else if (del->right == NULL)
	{
		cur = del->left;
		if (del == root)
			root = cur;
		else if (del == p->left)
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
	int pre, cur, i = 0;
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
	std::vector<int> dp(n + 1, 0);
	dp[0] = 1;
	dp[1] = 1;
	int ans = 0;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			dp[i] += dp[j] * dp[i - j - 1];
		}
	}
	return dp[n];
}

//生成不同的二叉搜索树
vector<TreeNode*> getTree(int begin, int end)
{
	vector<TreeNode*> res;
	if (begin > end)
		res.push_back(NULL);

	for (int i = begin; i <= end; i++)
	{
		vector<TreeNode*> lefts = getTree(begin, i - 1);
		vector<TreeNode*> rights = getTree(i + 1, end);
		for (int j = 0; j < lefts.size(); j++)
		{
			for (int k = 0; k < rights.size(); k++)
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
	if (n == 0)
		return vector<TreeNode*>{};
	else
		return getTree(1, n);
}

void BreadthFirstSearch(TreeNode *root)
{
	if (root == NULL)
		return;
	queue<TreeNode*> q;
	TreeNode* tmp = NULL;
	q.push(root);
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		printf("%d ", tmp->val);
		if (tmp->left)
			q.push(tmp->left);
		if (tmp->right)
			q.push(tmp->right);
	}
	printf("\n");
}


void PrintLevelOrder(vector<vector<int>> level)
{
	printf("{\n");
	for(int i = 0;i < level.size();i++)
	{
		printf("	[ ");
		for(int j = 0;j < level[i].size(); j++)
		{
			printf("%d ",level[i][j]);
		}
		printf("],\n");
	}
	printf("}\n");
}

//LeetCode 102. 二叉树的层次遍历
vector<vector<int>> levelOrder(TreeNode* root) 
{
	if(root == NULL)
		return vector<vector<int>>{};
	
	vector<vector<int>> ans;
	vector<int> tmp;
	queue<TreeNode*> q;
	TreeNode *node = NULL;
	int cnt = 1;
	int count = 0;
	q.push(root);
	while(!q.empty())
	{
		cnt = q.size();
		tmp.clear();
		while(cnt > 0)
		{
			node = q.front();
			tmp.push_back(node->val);
			q.pop();
			if(node->left)
				q.push(node->left);
			
			if(node->right)
				q.push(node->right);
			cnt--;
		}
		node = NULL;
		ans.push_back(tmp);
	}
	return ans;
}

//LeetCode 103. 二叉树的锯齿形层次遍历
vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
{
}


//LeetCode 110.平衡二叉树 && 111.二叉树的最小深度
bool isBalanced(TreeNode* root) 
{
	if(root == NULL)
		return true;
	
	queue<TreeNode*> q;
	TreeNode *node = NULL;
	q.push(root);
	int cnt = 0;
	int height = 0;
	int last = 0,cur = 0;
	while(!q.empty())
	{
		cnt = q.size();
		if(cnt > 0)
		{
			height++;
			
			while(cnt > 0)
			{
				node = q.front();
				q.pop();
				printf("%d\n",node->val);
				if(node->left)
					q.push(node->left);
				if(node->right)
					q.push(node->right);
				if(node->left == NULL && node->right == NULL)//child node,mark height
				{
					cur = height;
					//find first child
					if(last == 0)
						last = cur;
					else
					{
						if(cur - last > 1)
							return false;
					}
				}
				cnt--;
			}
		}
	}
	return true;
}

void PrintVector(vector<int>& a)
{
	for(int i = 0; i < a.size();i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

//LeetCode 105. 前序遍历和中序遍历构造二叉树
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{
	if(preorder.empty() && inorder.empty())
		return NULL;
	int i = 0;
	for(i = 0; i < inorder.size();i++)
	{
		if(inorder[i] == preorder[0])
		{
			break;
		}
	}
	
	TreeNode *root = new TreeNode(preorder[0]);
	if( preorder.size() == 1)
	{
		return root;
	}
	
	vector<int> lefts(inorder.begin(),inorder.begin()+i);
	vector<int> rights(inorder.begin() + i + 1,inorder.end());
	
	int lefts_size = lefts.size();
	int rights_size = preorder.size() - 1 - lefts_size;
	vector<int> left_pre(preorder.begin()+1,preorder.begin()+1 + lefts_size);
	vector<int> right_pre(preorder.begin()+1 + lefts_size,preorder.end());

	
	root->left = buildTree(left_pre,lefts);
	root->right = buildTree(right_pre,rights);
	
	return root;
}
//LeetCode 106. 中序遍历和后序遍历构造二叉树
TreeNode* buildTreeII(vector<int>& inorder, vector<int>& postorder) 
{
	if(postorder.empty() && inorder.empty())
		return NULL;
	int i = 0;
	for(i = 0; i < inorder.size();i++)
	{
		if(inorder[i] == postorder[postorder.size()-1])
		{
			break;
		}
	}
	
	TreeNode *root = new TreeNode(postorder[postorder.size()-1]);
	//printf("%d\n",root->val);
	if( postorder.size() == 1)
	{
		return root;
	}
	
	vector<int> lefts(inorder.begin(),inorder.begin()+i);
	vector<int> rights(inorder.begin() + i + 1,inorder.end());
	
	
	int lefts_size = lefts.size();
	int rights_size = postorder.size() - 1 - lefts_size;
	vector<int> left_post(postorder.begin(),postorder.begin()+lefts_size);
	
	vector<int> right_post(postorder.begin()+ lefts_size,postorder.end()-1);
	//printf("----------hahaha-------\n");
	//printf("right post:");
	PrintVector(right_post);
	
	root->left = buildTreeII(lefts,left_post);
	root->right = buildTreeII(rights,right_post);
	
	return root;
}


int CalcSum(vector<int> tmp)
{
	int sum = 0;
	for (int i = 0; i < tmp.size(); i++)
	{
		sum += tmp[i];
	}
	return sum;
}

bool hasPathSum_backtrack(vector<int> &tmp,TreeNode* root, int sum,vector<vector<int>> &ans)
{
	int flag1 = false;
	int flag2 = false;
	if(root != NULL)
	{
		tmp.push_back(root->val);
		if(root->left == NULL && root->right == NULL)
		{
			int s = CalcSum(tmp);
			//PrintVector(tmp);
			if(s == sum)
				ans.push_back(tmp);
		}
		if(root->left != NULL)
		{
			hasPathSum_backtrack(tmp,root->left,sum,ans);
		}
		if(root->right != NULL)
		{
			hasPathSum_backtrack(tmp,root->right,sum,ans);
		}
		tmp.pop_back();
		
	}
}

//LeetCode 112 && 113.路径总和I、II
bool hasPathSum(TreeNode* root, int sum)
{
	vector<int> tmp;
	vector<vector<int>> ans;
	hasPathSum_backtrack(tmp,root,sum,ans);
	if(!ans.empty())
	{
		for(int i = 0; i < ans.size(); i++)
			PrintVector(ans[i]);
		return true;
	}
	else
		return false;
}

#if 0
int main()
{
	//      10
	//   5     15

	TreeNode *root = new TreeNode(5);
	
	vector<vector<int>> level;
	
	BreadthFirstSearch(node1);
	
	TreeNode *tmp = NULL;

	tmp = new TreeNode(4);
	SearchBinary_Insert(node1, tmp);

	tmp = new TreeNode(8);
	SearchBinary_Insert(node1, tmp);

	tmp = new TreeNode(7);
	SearchBinary_Insert(node1, tmp);
	
	tmp = new TreeNode(8);
	SearchBinary_Insert(node1, tmp);
	
	return 0;
}
#else

int main()
{
	#if 1
	int pre[10] = {5,4,11,7,2,8,13,4,5,1};
	int ord[10] = {7,11,2,4,5,13,8,5,4,1};
	int post[6] = {9,15,7,20,3};
	vector<int> preorder(pre,pre + 10);
	vector<int> inorder(ord,ord + 10);
	vector<int> postorder(post,post+5);
	#else
	int pre[9] = {5,3,2,1,4,6,8,7,9};
	int ord[9] = {1,2,3,4,5,6,7,8,9};
	int post[9] = {1,2,4,3,7,9,8,6,5};
	vector<int> preorder(pre,pre + 9);
	vector<int> inorder(ord,ord + 9);
	vector<int> postorder(post,post+9);
	#endif
	
	#if 1
	TreeNode* root = buildTree(preorder,inorder);
	vector<vector<int>> level;
	vector<vector<int>> levelII;
	
	level = levelOrder(root);
	PrintLevelOrder(level);
	
	// levelII = zigzagLevelOrder(root);
	// PrintLevelOrder(levelII);
	
	// printf("------\n");
	// PostPrint(root);
	// printf("------\n");
	
	// if(hasPathSum(root,22))
		// cout<<"hahahah"<<endl;
	
	#endif 

	#if 0 
	int i = 0;
	for(i = 0; i < inorder.size();i++)
	{
		if(inorder[i] == preorder[0])
		{
			break;
		}
	}
	vector<int> lefts(inorder.begin(),inorder.begin()+i);
	vector<int> rights(inorder.begin() + i + 1,inorder.end());
	
	int lefts_size = lefts.size();
	int rights_size = preorder.size() - 1 - lefts_size;
	vector<int> left_pre(preorder.begin()+1,preorder.begin()+1 + lefts_size);
	vector<int> right_pre(preorder.begin()+1 + lefts_size,preorder.end());
	
	if(!lefts.empty())
	{
		PrintVector(lefts);
	}
	if(!rights.empty())
	{
		PrintVector(rights);
	}
	
	printf("---------------------\n");
	if(!left_pre.empty())
	{
		PrintVector(left_pre);
	}
	if(!right_pre.empty())
	{
		PrintVector(right_pre);
	}
	
	printf("\n");
	#else
	
	// int lefts_size = 1;
	// int rights_size = postorder.size() - 1 - lefts_size;
	// vector<int> left_post(postorder.begin(),postorder.begin()+lefts_size);
	
	// vector<int> right_post(postorder.begin()+ lefts_size,postorder.end()-1);
	// PrintVector(right_post);
	#endif
}

#endif
