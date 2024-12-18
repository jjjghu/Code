#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Point
{
    double x, y;
    int rank;
};
void heapify(vector<Point> &arr, int n, int i, bool (*comp)(const Point &, const Point &))
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && comp(arr[largest], arr[left]))
        largest = left;

    if (right < n && comp(arr[largest], arr[right]))
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, comp);
    }
}

void heapSort(vector<Point> &arr, bool (*comp)(const Point &, const Point &))
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i, comp);

    for (int i = n - 1; i > 0; --i)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, comp);
    }
}
bool cmpx(const Point &a, const Point &b)
{
    return a.x < b.x;
}
bool cmpy(const Point &a, const Point &b)
{
    return a.y < b.y;
}
bool cmpRank(const Point &a, const Point &b)
{
    return (a.rank != b.rank) ? a.rank < b.rank : a.x < b.x;
}
void findRanks(vector<Point> &points)
{
    if (points.size() <= 1)
    {
        return;
    }
    heapSort(points, cmpx);
    int mid = points.size() / 2;
    int value = points[mid].x;
    while (points[mid].x == value)
    {
        ++mid;
    }
    if (mid >= points.size())
    {
        return;
    }
    vector<Point> A(points.begin(), points.begin() + mid);
    vector<Point> B(points.begin() + mid, points.end());

    findRanks(A);
    findRanks(B);

    heapSort(A, cmpy);
    heapSort(B, cmpy);

    int aIndex = 0;
    for (int i = 0; i < B.size(); i++)
    {
        while (aIndex < A.size() && A[aIndex].y < B[i].y)
        {
            ++aIndex;
        }
        B[i].rank += aIndex;
    }

    for (int i = 0; i < A.size(); i++)
    {
        points[i] = A[i];
    }
    for (int i = 0; i < B.size(); i++)
    {
        points[mid + i] = B[i];
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cerr << "打開輸入文件時出錯！\n";
        return 1;
    }

    vector<Point> points;
    double x, y;
    while (inputFile >> x >> y)
    {
        Point temp;
        temp.x = x;
        temp.y = y;
        temp.rank = 0;
        points.push_back(temp);
    }

    findRanks(points);
    heapSort(points, cmpRank);
    ofstream outputFile("output.txt");
    int mxRank = 0;
    int mnRank = INT_MAX;
    double totalRank = 0;

    outputFile << fixed << setprecision(2);
    outputFile << left << setw(10) << "X"
               << left << setw(10) << "Y"
               << left << setw(10) << "Rank" << "\n";
    outputFile << "----------------------------------" << "\n";

    for (const auto &point : points)
    {
        outputFile << left << setw(10) << point.x
                   << left << setw(10) << point.y
                   << left << setw(10) << point.rank << "\n";
        totalRank += point.rank;
        mnRank = min(mnRank, point.rank);
        mxRank = max(mxRank, point.rank);
    }

    double averageRank = totalRank / points.size();
    outputFile << "----------------------------------" << "\n";
    outputFile << "一共有 " << points.size() << " 個點" << "\n";
    outputFile << "最小 Rank: " << mnRank << "\n";
    outputFile << "最大 Rank: " << mxRank << "\n";
    outputFile << "平均 Rank: " << averageRank << "\n";

    // 上面是檔案輸出, 下面是 cout 輸出

    mxRank = 0;
    mnRank = INT_MAX;
    totalRank = 0;

    cout << fixed << setprecision(2);
    cout << left << setw(10) << "X"
         << left << setw(10) << "Y"
         << left << setw(10) << "Rank" << "\n";
    cout << "----------------------------------" << "\n";

    for (const auto &point : points)
    {
        cout << left << setw(10) << point.x
             << left << setw(10) << point.y
             << left << setw(10) << point.rank << "\n";
        totalRank += point.rank;
        mnRank = min(mnRank, point.rank);
        mxRank = max(mxRank, point.rank);
    }

    averageRank = totalRank / points.size();
    cout << "----------------------------------" << "\n";
    cout << "一共有 " << points.size() << " 個點" << "\n";
    cout << "最小 Rank: " << mnRank << "\n";
    cout << "最大 Rank: " << mxRank << "\n";
    cout << "平均 Rank: " << averageRank << "\n";

    return 0;
}
