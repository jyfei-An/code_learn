#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
	//普通二分查找
	int search(vector<int>& nums, int target) {
		//搜索区间为[0,nums.size() - 1]
		int middle = 0, left = 0, right = nums.size() - 1;
		//注意：left <= right，不是<,终止条件是 left == right + 1，即[right + 1,right],搜索区间为空
		while (left <= right)
		{
			/*注意：middle=(left+right)/2,如果left和right都比较大的情况，可能会溢出，
			使用下面的方式计算中值可以避免这个问题*/
			middle = left + (right - left) / 2;
			if (nums[middle] == target)
			{
				return middle;
			}
			else if (nums[middle] < target)
			{
				//搜素区间变为[middle + 1,middle],此时middle不符合要求，从搜索区间中去除
				left = middle + 1;
			}
			else {
				//搜素区间变为[0,middle - 1]，此时middle不符合要求，从搜索区间中去除
				right = middle - 1;
			}
		}
		return -1;
	}

	/*
	搜索旋转排序数组
	示例 1：

	输入：nums = [4,5,6,7,0,1,2], target = 0
	输出：4
	示例 2：

	输入：nums = [4,5,6,7,0,1,2], target = 3
	输出：-1
	示例 3：

	输入：nums = [1], target = 0
	输出：-1
	*/
	//旋转排序数组二分查找
	int search1(vector<int>& nums, int target) {
		if (!nums.size())
		{
			return -1;
		}

		if (nums.size() == 1)
		{
			return nums[0] == target ? 0 : -1;
		}

		int size = nums.size();
		int left = 0, right = size - 1;
		while (left <= right)
		{
			int middle = left + (right - left) / 2;
			if (nums[middle] == target)
			{
				return middle;
			}
			if (nums[left] <= nums[middle])
			{//前半部分有序
				if (target >= nums[left] && target < nums[middle])
				{
					right = middle - 1;
				}
				else {
					left = middle + 1;
				}
			}
			else
			{//后半部分有序
				if (target > nums[middle] && target <= nums[right])
				{
					left = middle + 1;
				}
				else {
					right = middle - 1;
				}
			}

		}

		return -1;
	}


	//左边界二分查找
	int left_bound(vector<int>& nums, int target) {
		if (nums.size() == 0) return -1;
		int left = 0;
		int right = nums.size() - 1; // 注意
		int ans = -1;
		while (left <= right) { // 注意
			int middle = left + (right - left) / 2;
			if (nums[middle] == target) {
				right = middle - 1;
				ans = middle;
			}
			else if (nums[middle] < target) {
				left = middle + 1;
			}
			else if (nums[middle] > target) {
				right = middle - 1; // 注意
			}
		}
		return ans;
	}

	//右边界二分查找
	int right_bound(vector<int>& nums, int target) {
		if (nums.size() == 0) return -1;
		int left = 0;
		int right = nums.size() - 1; // 注意
		int ans = -1;
		while (left <= right) { // 注意
			int middle = left + (right - left) / 2;
			if (nums[middle] == target) {
				left = middle + 1;
				ans = middle;
			}
			else if (nums[middle] < target) {
				left = middle + 1;
			}
			else if (nums[middle] > target) {
				right = middle - 1; // 注意
			}
		}
		return ans;
	}

	//左右边界二分查找
	vector<int> searchRange(vector<int>& nums, int target) {
		int left = left_bound(nums, target);
		int right = right_bound(nums, target);
		if (left >= 0 && left <= right && right <= nums.size() - 1 && nums[left] == target && nums[right] == target)
		{
			return { left,right };
		}
		else {
			return { -1,-1 };
		}
	}

	vector<int> searchRangeSTL(vector<int>& nums, int target)
	{
		//<algorithm>
		//lower_bound和upper_bound使用二分查找计算
		//lower_bound返回第一个更大或者相等的元素位置，如果目标元素比所有元素都大，则返回end迭代器
		auto left = lower_bound(nums.begin(), nums.end(), target);
		//upper_bound返回第一个比目标元素更大的位置（求下标，需要减1），
		//如果目标元素比所有元素都大，则返回end迭代器
		auto right = upper_bound(nums.begin(), nums.end(), target);
		if (left==right)
		{
			return {-1,-1};
		}
		else
		{
			//left - nums.begin()求出左下标
			//right - nums.begin() -1 求出右下标
			return { int(left - nums.begin()) ,int(right - nums.begin() -1)};
		}
	}

};



int main()
{
	Solution solution;
	vector<int> vi{5,7,7,8,8,10};
	solution.searchRangeSTL(vi,6);
	solution.searchRangeSTL(vi,100);
	return 0;
}