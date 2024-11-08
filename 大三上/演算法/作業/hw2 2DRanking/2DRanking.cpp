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
bool cmpx(const Point &a, const Point &b)
{
    return a.x < b.x;
}
bool cmpy(const Point &a, const Point &b)
{
    return a.y < b.y;
}
void findRanks(vector<Point> &points)
{
    if (points.size() <= 1)
    {
        return;
    }
    sort(points.begin(), points.end(), cmpx);
    int mid = points.size() / 2;
    vector<Point> A(points.begin(), points.begin() + mid);
    vector<Point> B(points.begin() + mid, points.end());

    findRanks(A);
    findRanks(B);

    sort(A.begin(), A.end(), cmpy);
    sort(B.begin(), B.end(), cmpy);

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

int main(void)
{
    ifstream inputFile("D:\\Desktop\\test2.txt");
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

    ofstream outputFile("D:\\Desktop\\output.txt");
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

    return 0;
}
