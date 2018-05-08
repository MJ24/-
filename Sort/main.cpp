#include <iostream>
using namespace std;

void PrintArr(int arr[], int len)
{
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void swap(int &a, int&b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

void BBSort(int arr[], int len)
{
	bool swaped = false;
	for (int i = len - 1; i >= 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				swaped = true;
			}
		}
		if (!swaped) return;
	}
}

void InsertSort(int arr[], int len)
{
	for (int i = 1; i < len; ++i)
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
			swap(arr[j], arr[j - 1]);
}


void ShellSort(int arr[], int len)
{
	for (int gap = len / 2; gap > 0; gap /= 2)
		for (int i = gap; i < len; ++i)
			for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap)
				swap(arr[j], arr[j - gap]);
}

void perc_down(int *arr, int parent, int len)
{
	int val = arr[parent], child = 2 * parent + 1;
	while (child < len)
	{
		if (child != len - 1 && arr[child + 1] > arr[child])
			++child;
		if (arr[child] <= val)
			break;
		arr[parent] = arr[child];
		parent = child;
		child = 2 * parent + 1;
	}
	arr[parent] = val;
}
void heap_sort(int *arr, int len)
{
	for (int i = len / 2 - 1; i >= 0; --i)
		perc_down(arr, i, len);
	for (int i = len - 1; i >= 0; --i)
	{
		swap(arr[i], arr[0]);
		perc_down(arr, 0, i);
	}
}

void percDown(int arr[], int parent, int len)
{
	int val = arr[parent];
	int child = 2 * parent + 1;
	while (child < len)
	{
		if (child != len - 1 && arr[child + 1] > arr[child])
			++child;
		if (val >= arr[child])
			break;
		arr[parent] = arr[child];
		parent = child;
		child = 2 * parent + 1;
	}
	arr[parent] = val;
}
void HeapSort(int arr[], int len)
{
	for (int i = len / 2 - 1; i >= 0; --i)
		percDown(arr, i, len);
	for (int i = len - 1; i > 0; --i)
	{
		swap(arr[i], arr[0]);
		percDown(arr, 0, i);
	}
}

void mergeArr(int arr[], int start, int mid, int end, int tmp[])
{
	int i = start, j = mid + 1, k = 0;
	while (i <= mid && j <= end)
		tmp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
	while (i <= mid)
		tmp[k++] = arr[i++];
	while (j <= end)
		tmp[k++] = arr[j++];
	for (int i = 0; i < k; i++)
		arr[start + i] = tmp[i];
}
void mSort(int arr[], int start, int end, int tmp[])
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		mSort(arr, start, mid, tmp);
		mSort(arr, mid + 1, end, tmp);
		mergeArr(arr, start, mid, end, tmp);
	}
}
void MergeSort(int arr[], int len)
{
	int *tmp = new int[len];
	mSort(arr, 0, len - 1, tmp);
	delete tmp;
}

void quickSort(int arr[], int first, int last)
{
	if (first < last)
	{
		int l = first, r = last;
		int val = arr[first];
		while (l < r)
		{
			while (arr[r] > val && l < r)
				--r;
			if (l < r)
				arr[l++] = arr[r];
			while (arr[l] <= val && l < r)
				++l;
			if (l < r)
				arr[r--] = arr[l];
		}
		arr[l] = val;
		quickSort(arr, first, l - 1);
		quickSort(arr, l + 1, last);
	}
}
void QuickSort(int arr[], int len)
{
	quickSort(arr, 0, len - 1);
}

int main()
{
	int arr[] = { 1, 4, 8, 9, 2, 5, 3, 7, 6 };
	//insert_sort(arr, 9);
	PrintArr(arr, 9);
	system("pause");
	return 0;
}