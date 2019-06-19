#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using std::cout;
using std::endl;
using std::vector;

void PrintArray(int a[], int len)
{
	int n = len;
	int i = 0;
	for(i; i < n ;i++)
		printf("%d ",a[i]);

	printf("\n");
}

void PrintVector(vector<int> a)
{
	for(int i = 0 ; i < a.size(); i++)
		printf("%d ",a[i]);
	
	printf("\n");
}

void quick_sort(int a[], int left, int right)
{
	if(left < right)
	{
		int i,j,x;
		i = left;
		j = right;
		x = a[i];
		while(i < j)
		{
			while(i < j && a[j] > x)
				j--;
			if(i<j)
				a[i++] = a[j];
			
			while(i < j && a[i] < x)
				i++;
			
			if(i<j)
				a[j--] = a[i];
		}
		a[i] = x;
		quick_sort(a,left,i-1);
		quick_sort(a,i+1,right);
	}
}

 void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
void min_heap(int *arr,int index)
{
	int dad = index;
	int son = index * 2 + 1;
	while(dad >= 0)
	{
		if(arr[son] >= arr[son + 1] && son + 1 <= end) //找到最小的子节点
			son++;
		if(arr[son] > arrp[dad])
			return;
		else
		{
			swap(arr[son],arr[dad]);
			son = dad;
			dad = (dad - 1) / 2 ;
		}
	}
}




void heap_sort(int *arr, int len)
{
	//bulid heap
	int heapSize = len;
	for(int i = heapSize / 2  - 1 ; i >= 0 ; i--)
	{
		min_heap(arr,i);
	}
	
	
	//del top
} */

void max_heapify(int arr[], int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比較
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sortII(int arr[], int len) {
    int i;
    // 初始化，i從最後一個父節點開始調整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    // 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
	PrintArray(arr,len);
	cout<<"======"<<endl;
    for (i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}


void bobble_find_max(int a[],int top ,int len)
{
	
	for(int i = 0 ; i < len ; i++)
	{
		for(int j = i ; j < len ; j++)
		{
			if(a[i] < a[j])
				swap(&a[i],&a[j]);
		}
		if(i == top)
			return;
	}
}


void swapII(int &a, int &b)
{
	
	int tmp = a;
	a = b;
	b = tmp;
}

void max_heapifyII(vector<int> &a, int start, int end)
{
	int dad = start;
	int son = dad * 2 + 1;
	while(son <= end)
	{
		if(son + 1 <= end && a[son] < a[son + 1])
			son++;
		if(a[son] < a[dad])
			return;
		else
		{
			swap(&a[son], &a[dad]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void MinK(vector<int> a,int min)
{
	if(min > a.size() || min <= 0)
		return;
	
	int len = a.size();
	int heapSize = min;
	vector<int> heap(a.begin(),a.begin() + min);
	PrintVector(heap);
	//bulid max heap
	for(int i = heapSize / 2 - 1; i >=0 ; i--)
	{
		max_heapifyII(heap,i,min - 1);
	}
	cout<<"buld"<<endl;
	
	for(int j = min; j < len; j++)
	{
		if(heap[0] > a[j])
		{
			swapII(heap[0],a[j]);
			max_heapifyII(heap,0,min - 1);
		}
	}
	
	PrintVector(heap);
}


void min_heap(vector<int> &a, int start, int end)
{
	int dad = start;
	int son = dad * 2 + 1;
	while(son <= end)
	{
		if(son + 1 <= end && a[son + 1] < a[son])
			son++;
		if(a[son] > a[dad])
			return;
		else
		{
			swapII(a[son],a[dad]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(vector<int> &a)
{
	int heapSize = a.size();
	for(int i = heapSize / 2 - 1; i >= 0 ; i--)
		min_heap(a,i,heapSize - 1);
	
	for(int i = heapSize - 1; i > 0; i--)
	{
		swapII(a[0],a[i]);
		min_heap(a,0,i-1);
	}
}


void TopK(vector<int> &a, int top)
{
	int heapSize = top;
	vector<int> heap(a.begin(),a.begin() + top);
	
	for(int i = heapSize / 2 - 1 ; i >= 0 ;i--)
		min_heap(heap,i,heapSize - 1);
	
	
	
	for(int i = heapSize ; i < a.size() ; i++)
	{
		
		if(heap[0] < a[i])
		{
			swapII(heap[0],a[i]);
			min_heap(heap,0, heapSize - 1);
		}
	}
	
	PrintVector(heap);
	
	printf("\n");
}

int partition(vector<int> &nums, int begin, int end)
{
    int pivot = nums[begin];
	cout<<"key = "<<pivot<<endl;
	printf("start[%d] , end[%d]\n",begin,end);
    while(begin < end)
    {
        while(begin < end && nums[end] >= pivot)
			end--;
		
		cout<<nums[begin]<<" "<<nums[end]<<endl;
        nums[begin] = nums[end];
		
        while(begin < end && nums[begin] <= pivot)
			begin++;
		
        nums[end] = nums[begin];
		
		cout<<nums[begin]<<" "<<nums[end]<<endl;
    }
    nums[begin] = pivot;
    return begin;
}

void q_sort(vector<int> &a, int left, int right)
{
	if(left >= right) return;

	int i = partition(a,left,right);
	//printf("i = %d\n",i);
	//PrintArray(a,4);
	cout<<"------------"<<endl;
	//PrintVector(a);
	q_sort(a,left,i - 1);
	q_sort(a,i + 1,right);
}

int selectK(vector<int> &a,int start,int end,int k)
{
	int index = 0;
	if(start == end) 
	{
		cout<<"ans = "<<start<<endl;
		return start;
	}
	
	if(start<end)
	{
		index = partition(a,start,end);
		printf("---%d --%d----",index,k);
		PrintVector(a);
		cout<<endl;
		int tmp = end - index + 1;
		if(tmp == k)//正好找到第k大的数
		{
			return index;
		}
		else if(tmp < k)//从index的左边找k-tmp个数
		{
			printf("++\n");
			index = selectK(a,start,index - 1,k-tmp);
		}
		else if(tmp > k)//从index的右边继续找k个最大的数
		{
			printf("##\n");
			index = selectK(a,index + 1,end,k);
		}
	}
	
	return index;
}

int Topk_II(vector<int> &a,int top)
{
	int ans = selectK(a,0,a.size() - 1,top);
	//cout<<ans<<endl;
	return ans;
}

int selectMinK(vector<int> &a,int start,int end,int k)
{
	int index = 0;
	if(start == end) 
	{
		cout<<"ans = "<<start<<endl;
		return start;
	}
	
	if(start<end)
	{
		index = partition(a,start,end);
		printf("---%d --%d----",index,k);
		PrintVector(a);
		cout<<endl;
		int tmp = index + 1;
		if(tmp == k)//正好找到第k大的数
		{
			return index;
		}
		else if(tmp < k)//从index的左边找k-tmp个数
		{
			printf("++\n");
			index = selectK(a,index + 1,end,k-tmp);
		}
		else if(tmp > k)//从index的右边继续找k个最大的数
		{
			printf("##\n");
			index = selectK(a,start,index - 1,k);
		}
	}
	
	return index;
}

int Mink_II(vector<int> &a,int top)
{
	int ans = selectMinK(a,0,a.size() - 1,top);
	cout<<ans<<endl;
	return ans;
}

int main()
{
	int a[20] = {3,4,0,1,10,9,14,17,13,15,18,6,19,16,12,8,11,2,5,7};
	int test[4] = {3,4,2,1};
	int len = sizeof(a)/sizeof(int);
	
	vector<int> arr(a,a+20);
	vector<int> arr_rand;
	//int arr_tmp[100];
	//printf(" a len = %d\n",len);
	//PrintArray(a,len);
	
/* 	
	PrintVector(arr);
	printf("-----\n");
	MinK(arr,6); */
	
	// srand((unsigned)time(0));
	int tmp;
	
	for(int i = 0 ; i < 100 ; i++)
	{
		tmp = rand()%100;
		arr_rand.push_back(tmp);
		//arr_tmp[i] = tmp;
	}
	//PrintArray(a,20);
	//q_sort(arr,0,19);
	
	int index = Mink_II(arr_rand,10);
	for(int i = 0 ; i <= index ;i++ )
		cout<<arr_rand[i]<<" ";
	cout<<endl;
	
	 //q_sort(arr_rand,0,arr_rand.size() - 1);
	// PrintVector(arr_rand);
	PrintVector(arr_rand);
/* 	printf("------arr_rand------\n");
	PrintVector(arr_rand);
	printf("------------\n");
	
	 quick_sort(arr_tmp,0,99);
	 PrintArray(arr_tmp,100);
	printf("###########\n");
	//heap_sort(arr_rand);
	TopK(arr_rand,10);
	PrintVector(arr_rand); */



	return 0;
}
