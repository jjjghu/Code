#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
void quickSort(vector<double> &nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int i = left - 1, j = right + 1;
    double pivotValue = nums[left + rand() % (right - left)];
    while (i < j)
    {
        do
        {
            ++i;
        } while (nums[i] < pivotValue);
        do
        {
            --j;
        } while (pivotValue < nums[j]);
        if (i < j)
        {
            swap(nums[i], nums[j]);
        }
    }
    quickSort(nums, left, j);
    quickSort(nums, j + 1, right);
}
void insertionSort(vector<double> &nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        int value = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > value)
        {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = value;
    }
}
int main(void)
{
    ifstream inputFile("D:\\Desktop\\test1.txt");
    if (!inputFile)
    {
        cerr << "打開輸入文件時出錯！\n";
        return 1;
    }

    vector<double> nums;
    double num;
    while (inputFile >> num)
    {
        nums.push_back(num);
    }
    inputFile.close();

    if (nums.empty())
    {
        cerr << "輸入文件中沒有數字。\n";
        return 1;
    }
    string choice;
    while (true)
    {
        vector<double> temp = nums;
        cout << "\n請選擇一個選項：\n";
        cout << "1. 快速排序\n";
        cout << "2. 插入排序\n";
        cout << "3. 退出程序\n";

        cin >> choice;

        if (choice == "1")
        {
            cout << "正在執行快速排序...\n";
            quickSort(temp, 0, temp.size() - 1);
        }
        else if (choice == "2")
        {
            cout << "正在執行插入排序...\n";
            insertionSort(temp);
        }
        else if (choice == "3")
        {
            cout << "程式結束\n";
            return 0;
        }
        else
        {
            cout << "無效的選擇。請輸入 1、2 或 3。\n";
            cin.clear();
            cin.ignore();
            continue;
        }

        for (int i = 0; i < temp.size(); ++i)
        {
            cout << fixed << setw(4) << setprecision(2) << temp[i] << " ";
            if (i > 0 && !((i + 1) % 10))
            {
                cout << "\n";
            }
        }
        cout << "\n";

        ofstream outputFile("D:\\Desktop\\output.txt");
        if (!outputFile)
        {
            cerr << "打開輸出文件時出錯！\n";
            return 1;
        }
        outputFile << "數字個數: " << temp.size() << "\n";
        outputFile << "最大的數: " << temp.back() << "\n";
        outputFile << "最小的數: " << temp.front() << "\n\n";
        outputFile.close();
    }

    return 0;
}