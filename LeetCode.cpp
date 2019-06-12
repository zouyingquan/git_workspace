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

void PrintVector(vector<int> &a)
{
	for (int i = 0; i < a.size(); i++)
		printf("%d ", a[i]);
	printf("\n");
}

//LeetCode 15.三数之和
vector<vector<int>> threeSum(vector<int>& nums) {
	if (nums.size() < 3)
		return vector<vector<int>>{};

	vector<vector<int>> ans;

	sort(nums.begin(), nums.end());
	//PrintVector(nums);
	int fix = 0;
	int head = 0, tail = nums.size() - 1;
	int target = 0;
	vector<int> tmp;
	for (int i = 0; i < nums.size() - 1; i++)
	{
		if (nums[i] > 0)break;
		if (i > 0 && nums[i] == nums[i - 1])continue;

		fix = nums[i];
		target = 0 - fix;
		head = i + 1;
		tail = nums.size() - 1;
		while (head < tail)
		{
			if (nums[head] + nums[tail] < target)
				head++;
			else if (nums[head] + nums[tail] > target)
				tail--;
			else
			{
				tmp.clear();
				tmp.push_back(fix);
				tmp.push_back(nums[head]);
				tmp.push_back(nums[tail]);

				ans.push_back(tmp);
				while (nums[head] == nums[++head] && head < tail);
				while (nums[tail] == nums[--tail] && head < tail);

			}
		}

	}
	return ans;
}


//LeetCode 18.四数之和
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	if (nums.size() < 4)
		return vector<vector<int>>{};

	vector<vector<int>> ans;

	sort(nums.begin(), nums.end());
	//PrintVector(nums);
	int fix = 0;
	int head = 0, tail = nums.size() - 1;
	int ptarget = 0;
	vector<int> tmp;
	for (int i = 0; i < nums.size() - 3; i++)
	{
		//if (nums[i] > target)break;
		if (i > 0 && nums[i] == nums[i - 1])continue;

		ptarget = target - nums[i];
		for (int j = i + 1; j < nums.size() - 1; j++)
		{
			//if(nums[j] > ptarget)break;
			if (j > i + 1 && nums[j] == nums[j - 1])continue;

			fix = nums[j];
			ptarget = target - fix - nums[i];

			head = j + 1;
			tail = nums.size() - 1;
			while (head < tail)
			{
				if (nums[head] + nums[tail] < ptarget)
					head++;
				else if (nums[head] + nums[tail] > ptarget)
					tail--;
				else
				{
					tmp.clear();
					tmp.push_back(nums[i]);
					tmp.push_back(fix);
					tmp.push_back(nums[head]);
					tmp.push_back(nums[tail]);

					ans.push_back(tmp);
					while (nums[head] == nums[++head] && head < tail);
					while (nums[tail] == nums[--tail] && head < tail);

				}
			}
		}
	}
	return ans;
}

bool isMatching(char &a, char &b)
{
	if ((a == '(' && b == ')') || (a == ')' && b == '(')) return true;
	else if ((a == '[' && b == ']') || (a == ']' && b == '[')) return true;
	else if ((a == '{' && b == '}') || (a == '}' && b == '{')) return true;

	return false;
}

//LeetCode 20.有效括号
bool isValid(string s) 
{
	if (s.length() <= 0)
		return true;

	stack<char> a;
	int len = s.length();
	int i = 0;
	while (i < len )
	{
		if (a.empty())
			a.push(s[i]);
		else
		{
			if (isMatching(a.top(), s[i]))
				a.pop();
			else
			{
				a.push(s[i]);
			}
		}
		i++;
	}

	if (a.empty())
		return true;
	else
		return false;
}

//LeetCode 26.删除排序数组中的重复项
int removeDuplicates(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int k = 0;
	for (int i = 0; i < nums.size(); i++)
		if (nums[i] != nums[k])
			nums[++k] = nums[i];
	return ++k;
}

//LeetCode 80.删除排序数组中的重复项II
int removeDuplicatesII(vector<int>& nums)
{
	if (nums.size() <= 1)
		return nums.size();
	int k = 2;
	int cnt = 0;
	for (int i = 2; i < nums.size(); i++)
	{
		if (nums[k - 1] != nums[i] || nums[k - 2] != nums[i])
		{
			nums[k] = nums[i];
			k++;
		}
	}
	return k;
}

void backtrack(vector<string> &ans, string cur, int open, int close, int max)
{
	if (cur.length() == max * 2)
	{
		ans.push_back(cur);
		//cout << "--------" << endl;
		return;
	}
	//cout << cur << "+" << open << "+" << close << endl;
	string tmp = cur;
	if (open < max)
		backtrack(ans, cur.append("("), open+1, close, max);

	cur = tmp;
	if (close < open)
		backtrack(ans, cur.append(")"), open, close+1, max);
}

//LeetCode 22.括号生成
vector<string> generateParenthesis(int n) 
{
	vector<string> ans;
	int open = 0;
	int close = 0;
	if (n > 0)
		backtrack(ans,"",open,close,n);

	return ans;
}

int strStr(string haystack, string needle) 
{
	if (needle.length() == 0)
		return 0;
	if (haystack.length() == 0)
		return -1;

	string tmp;
	int k;
	for (int i = 0; i < haystack.length(); i++)
	{
		if (haystack[i] == needle[0])
		{
			k = i;
			for (int j = 0; j < needle.length(); j++)
			{
				
			}
		}
	}

}

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void pmt(vector<int> &seq, int idx, vector<vector<int>> &res)
{
	if (idx == seq.size() - 1)
		res.push_back(seq);
	else
	{
		for (int i = idx; i < seq.size(); i++)
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


void pmtUnique(vector<int> &nums, int index, vector<vector<int>> &ans)
{
	if (index == nums.size() - 1)
		ans.push_back(nums);
	else
	{
		int flag = 0;
		vector<int> mark;
		for (int i = index; i < nums.size(); i++)
		{
			if (!mark.empty())
			{
				vector<int>::iterator it = find(mark.begin(), mark.end(), nums[i]);
				if (it != mark.end())
					continue;
			}
			swap(nums[i], nums[index]);

			pmtUnique(nums, index + 1, ans);

			swap(nums[i], nums[index]);
			mark.push_back(nums[i]);

		}
	}
}

//LeetCode 47. 全排列II
vector<vector<int>> permuteUnique(vector<int>& nums)
{
	vector<vector<int>> ans;
	pmtUnique(nums, 0, ans);
	return ans;
}

//LeetCode 31. 下一个排列
void nextPermutation(vector<int>& nums)
{
	int tail = nums.size() - 1;
	cout << tail << endl;
	int pos = 0;
	int i = 0;
	for (i = tail - 1; i >= 0; i--)
	{
		if (nums[i] < nums[tail])
		{
			pos = i;
			break;
		}
	}
	pos = i;
	if (i == -1)
	{
		std::reverse(nums.begin(), nums.end());
	}
	else
	{
		vector<int> tmp(nums.begin() + pos, nums.end() - 1);
		PrintVector(tmp);
		sort(tmp.begin(), tmp.end());
		nums[pos] = nums[tail];
		int j = 0;
		for (i = pos + 1; i < nums.size(); i++)
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
	for (int i = 0; i < tmp.size(); i++)
	{
		sum += tmp[i];
	}
	return sum;
}

void comb_backtrack(vector<int> &tmp, vector<int> candidates, vector<vector<int>> &ans, int target, int pos)
{

	for (int i = pos; i < candidates.size(); i++)
	{

		printf("push %d,pre %d,target %d\n", candidates[i], target, target - candidates[i]);
		if (target - candidates[i] < 0)
			continue;
		if (target - candidates[i] == 0)
		{
			tmp.push_back(candidates[i]);
			ans.push_back(tmp);
			tmp.pop_back();
			continue;
		}

		tmp.push_back(candidates[i]);
		comb_backtrack(tmp, candidates, ans, target - candidates[i], i);
	}
	tmp.pop_back();
}


//LeetCode 39.组合总和
vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
	vector<vector<int>> ans;
	vector<int> tmp;
	comb_backtrack(tmp, candidates, ans, target, 0);
	return ans;
}

//LeetCode 34.在排序数组中查找元素的第一个和最后一个位置
vector<int> searchRange(vector<int>& nums, int target)
{
	int start = -1, end = -1;
	vector<int> ans;
	for (int i = 0; i < nums.size(); i++)
	{
		if (start == -1 && nums[i] == target)
		{
			start = i;
		}
		if (start != -1 && nums[i] == target)
		{
			end = i;
		}
	}
	if (start != -1 && end == -1)
		end = start;

	ans.push_back(start);
	ans.push_back(end);

	return ans;
}

//LeetCode 35.搜索插入位置
int searchInsert(vector<int>& nums, int target)
{
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] < target)
			continue;
		else
			return i;
	}

	return nums.size();
}


int main()
{
	int arr[6] = { -1,0,1,2,-1,-4 };
	vector<int> nums(arr, arr + 6);
	vector<string> ans = generateParenthesis(10);
	for (int i = 0; i < ans.size(); i++)
		//printf("%s\n",ans[i]);
		cout << ans[i] << endl;
	return 0;
}
