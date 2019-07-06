#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<stack>
#include<map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stack;
using std::map;

map<char, int> GetOffset(string str)
{
	map<char, int> ans;
	int len = str.length();
	for(int i = str.length() - 1; i >= 0 ; i--)
	{
		if(!ans[str[i]])
		{
			ans[str[i]] = len - i;
		}
	}
	
	return ans;
}


int Sunday(string str, string p)
{
	map<char,int> shift = GetOffset(p);
	map<char,int>::iterator it;
	int i = 0;
	int j = 0;
	int tlen = str.length();
	int plen = p.length();
	while(i <= tlen - plen)
	{
		j = 0;
		while(str[i + j] == p[j])
		{
			j++;
			if(j == plen)
				return i;
		}
		
		if(shift[str[ i + plen]])
		{
			i = i + shift[str[ i + plen ]];
		}
		else
		{
			i = i + plen;
		}
	}
	return -1;
}




int main()
{
	string str = "substring searching alogritm";
	string p = "search";
	//int ans = Sunday(str,p);
	//cout<<ans<<endl;
	string T, P;
    	while(true) {
        // 获取一行
        getline(cin, T);
        getline(cin, P);
        int res = Sunday(T, P);
        if(res == -1) {
            cout << "主串和模式串不匹配。" << endl;
        } else {
            cout << "模式串在主串的位置为：" << res << endl;
        }
    }
	return 0;
}
