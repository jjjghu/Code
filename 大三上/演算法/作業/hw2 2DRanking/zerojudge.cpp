#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Point
{
    int id;
    int x, y;
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
bool cmpid(const Point &a, const Point &b)
{
    return a.id < b.id;
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
    int n;
    cin >> n;
    vector<Point> points;
    double x, y;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        Point temp;
        temp.id = i;
        temp.x = x;
        temp.y = y;
        temp.rank = 0;
        points.push_back(temp);
    }
    findRanks(points);
    heapSort(points, cmpid);
    for (int i = 0; i < points.size(); ++i)
    {
        cout << points[i].rank << "\n";
    }
    return 0;
}
