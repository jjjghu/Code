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
    int n = points.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (points[i].x < points[j].x && points[i].y < points[i].y)
            {
                ++points[i].rank;
            }
        }
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

    outputFile << fixed << setprecision(3);
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

    return 0;
}
