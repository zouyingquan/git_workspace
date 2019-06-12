#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include <stack>
#include<algorithm>

using std::cout;
using std::endl;
using std::string;
using std::stack;
using std::vector;

bool isMatching(char a, char b)
{
	if((a == '(' && b == ')') || (b == '(' && a == ')'))return true;
	
	if((a == '{' && b == '}') || (b == '{' && a == '}'))return true;
	
	if((a == '[' && b == ']') || (b == '[' && a == ']'))return true;
	
	return false;
}
//LeetCode 20.有效括号
bool isValid(string s) 
{
	if(s.length() == 0)
		return true;
	if(s.length()%2)
		return false;
	stack<char> a;
	int len = s.length();
	int n = 0;
	char tmp = s[n++];
	char context;
	a.push(tmp);
	while( n < len)
	{
		tmp = s[n];
		context = a.top();
		if(isMatching(context,tmp))
		{
			a.pop();
			if(++n == len)
				break;
		
			a.push(s[n]);
		}
		else
			a.push(tmp);
		n++;
	}
	
	if(a.empty())
		return true;
	else
	{
		cout<<a.size()<<endl;
		return false;
	}
}

void PrintVector(vector<int>& a)
{
	for(int i = 0 ; i < a.size() ; i++)
		printf("%d ",a[i]);
	printf("\n");
}


 void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void pmt(vector<int> &seq, int idx, vector<vector<int>> &res)
{
	if(idx == seq.size() - 1)
		res.push_back(seq);
	else
	{
		for(int i = idx; i < seq.size(); i++)
		{
			swap(seq[idx], seq[i]);
			pmt(seq, idx + 1, res);
			swap(seq[i], seq[idx]);
		}
	}
}

vector<vector<int>> permute(vector<int>& nums)
{
	vector<vector<int>> res;
	pmt(nums, 0, res);
	return res;
}


void pmtUnique(vector<int> &nums,int index, vector<vector<int>> &ans)
{
	if(index == nums.size() - 1)
		ans.push_back(nums);
	else
	{
		int flag = 0;
		vector<int> mark;
		for(int i = index; i < nums.size(); i++)
		{
			if(!mark.empty())
			{
				vector<int>::iterator it = find(mark.begin(),mark.end(),nums[i]);
				if(it != mark.end())
					continue;
			}
			swap(nums[i],nums[index]);
			
			pmtUnique(nums,index + 1, ans);
	
			swap(nums[i],nums[index]);
			mark.push_back(nums[i]);
			
		}
	}
}

//LeetCode 47. 全排列II
vector<vector<int>> permuteUnique(vector<int>& nums) 
{
	vector<vector<int>> ans;
	pmtUnique(nums,0,ans);
	return ans;
}

//LeetCode 31. 下一个排列
void nextPermutation(vector<int>& nums) 
{
	int tail = nums.size() - 1;
	cout<<tail<<endl;
	int pos = 0;
	int i = 0;
	for(i = tail - 1; i >= 0; i--)
	{
		if(nums[i] < nums[tail])
		{
			pos = i;
			break;
		}
	}
	pos = i;
	if(i == -1)
	{
		std::reverse(nums.begin(),nums.end()); 
	}
	else
	{
		vector<int> tmp(nums.begin() + pos,nums.end() - 1);
		PrintVector(tmp);
		sort(tmp.begin(),tmp.end());
		nums[pos] = nums[tail];
		int j = 0;
		for(i = pos + 1; i < nums.size();i++)
		{
			nums[i] = tmp[j];
			j++;
		}
	}
	
	PrintVector(nums);

}

int CalcSum(vector<int> tmp)
{
	int sum = 0;
	for(int i = 0; i < tmp.size(); i++)
	{
		sum += tmp[i];
	}
	return sum;
}

void comb_backtrack(vector<int> &tmp, vector<int> candidates, vector<vector<int>> &ans, int target,int pos)
{

	for(int i = pos;i < candidates.size(); i++)
	{
		
		printf("push %d,pre %d,target %d\n",candidates[i],target,target - candidates[i]);
		if(target - candidates[i] < 0)
			continue;
		if(target - candidates[i] == 0)
		{
			tmp.push_back(candidates[i]);
			ans.push_back(tmp);
			tmp.pop_back();
			continue;
		}
		
		tmp.push_back(candidates[i]);
		comb_backtrack(tmp,candidates,ans,target - candidates[i],i);
	}
	tmp.pop_back();
}


//LeetCode 39.组合总和
vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
	vector<vector<int>> ans;
	vector<int> tmp;
	comb_backtrack(tmp,candidates,ans,target,0);
	return ans;
}

//LeetCode 34.在排序数组中查找元素的第一个和最后一个位置
vector<int> searchRange(vector<int>& nums, int target)
{
	int start = -1, end = -1;
	vector<int> ans;
	for(int i = 0 ; i < nums.size(); i++)
	{
		if(start == -1 && nums[i] == target)
		{
			start = i;
		}
		if(start != -1 && nums[i] == target)
		{
			end = i;
		}
	}
	if(start != -1 && end == -1)
		end = start;
	
	ans.push_back(start);
	ans.push_back(end);
	
	return ans;
}

//LeetCode 35.搜索插入位置
int searchInsert(vector<int>& nums, int target) 
{
	for(int i = 0; i < nums.size(); i++)
	{
		if(nums[i] < target)
			continue;
		else
			return i;
	}
	
	return nums.size();
}

int main()
{
	int pre[5] = {1,7,8,4,2};
	vector<int> preorder(pre,pre + 5);
	
	nextPermutation(preorder);
	
	
	return 0;
}
