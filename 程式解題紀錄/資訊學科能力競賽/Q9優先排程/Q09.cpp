#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int gcd(long long a, long long b) // 找出最小公倍數
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
struct Task
{
    int execTime;      // 需要的工作時長
    int period;        // 發布工作的時間
    int remainingTime; // 再執行多少時間就能完成工作
    int nextDeadline;  // 完成工作的期限
    int id;            // 任務編號
};

struct Compare
{
    int currentTaskId;
    Compare() : currentTaskId(0) {}
    void setCurrentTaskId(int id) { currentTaskId = id; }
    bool operator()(const Task &t1, const Task &t2) const
    {
        // 先根據截止時間排序, 若截止時間相同，盡量不要切換工作
        if (t1.nextDeadline != t2.nextDeadline)
        {
            return t1.nextDeadline > t2.nextDeadline;
        }
        if (t1.remainingTime != t2.remainingTime)
        {
            return t1.remainingTime < t2.remainingTime;
        }
        if (t1.id == currentTaskId)
        {
            return false;
        }
        return true;
    }
};

int solve()
{
    int n;
    cin >> n;
    vector<Task> tasks(n);
    int minPeriod = INT_MAX;
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> tasks[i].execTime >> tasks[i].period;
        // 如果一個任務需要執行的時間跟發布任務的時間相同, 則無法完成工作
        if (tasks[i].execTime == tasks[i].period && n != 1)
        {
            return 0;
        }
        tasks[i].remainingTime = tasks[i].execTime;
        tasks[i].nextDeadline = tasks[i].period;
        tasks[i].id = i;
        sum += tasks[i].execTime;
        minPeriod = min(minPeriod, tasks[i].period);
    }
    // 假如所有工作所需花費的時間, 能夠在最短的週期內完成, 提早結束
    if (sum < minPeriod)
    {
        return sum;
    }

    // 標記工作完成的狀況
    vector<bool> completed(n, false);
    int completedCount = 0;

    // 找出最大公因數, 在期限內要完成所有工作一遍
    long long lcm = 1;
    for (const Task &task : tasks)
    {
        lcm = lcm * task.period / gcd(lcm, task.period);
    }
    // cerr << "lcm " << lcm << "\n";

    Compare compare;
    priority_queue<Task, vector<Task>, Compare> pq(compare);
    for (Task &task : tasks)
    {
        pq.push(task);
    }
    for (int time = 1; time <= lcm; ++time)
    {
        // cerr << "\n\nTime " << time << "\n";
        if (!pq.empty())
        {
            // 執行最緊急的任務, 更新工作 id
            Task current = pq.top();
            pq.pop();
            compare.setCurrentTaskId(current.id);

            --current.remainingTime;
            --tasks[current.id].remainingTime;
            // cerr << "Executing " << current.id << " right now\n";

            // 沒完成 Task, 繼續做
            if (current.remainingTime > 0)
            {
                pq.push(current);
            }
            else
            {
                if ((!completed[current.id])) // 第一次完成
                {
                    // cerr << "First time complete job " << current.id << "\n";
                    completed[current.id] = true;
                    completedCount++;
                    if (completedCount == n)
                    {
                        return time;
                    }
                }
                else
                {
                    compare.setCurrentTaskId(0);
                    // cerr << "another time complete job " << current.id << "\n";
                }
            }
        }
        for (Task &task : tasks)
        {
            if (time % task.period == 0)
            {
                // 已經要發布工作, 但工作還沒有完成
                if (task.remainingTime > 0)
                {
                    // cerr << "Task " << task.id << " Fail!\n";
                    return 0;
                }
                // 發布工作
                // cerr << "Release Task " << task.id << "\n";
                task.remainingTime = task.execTime;
                task.nextDeadline = time + task.period;
                pq.push(task);
            }
        }
    }
    return 0;
}

int main(void)
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        cout << solve() << endl;
        // 將 '/' 和 '.' 符號忽略掉
        if (i < t - 1)
        {
            char dummy;
            cin >> dummy;
        }
    }
    return 0;
}