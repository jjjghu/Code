#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class State {
public:
    map<char, vector<int>> pegs;  // 'A', 'B', 'C', 'D' -> vector of rings
    vector<string> moves;
    
    State() {
        pegs['A'] = vector<int>();
        pegs['B'] = vector<int>();
        pegs['C'] = vector<int>();
        pegs['D'] = vector<int>();
    }
    
    State(const map<char, vector<int>>& p, const vector<string>& m = vector<string>()) 
        : pegs(p), moves(m) {}
    
    // 複製狀態
    State clone() const {
        return State(pegs, moves);
    }
    
    // 生成雜湊鍵（用於判斷是否訪問過）
    string hash_key() const {
        stringstream ss;
        ss << "{";
        for (auto it = pegs.begin(); it != pegs.end(); ++it) {
            if (it != pegs.begin()) ss << ",";
            ss << "\"" << it->first << "\":[";
            for (size_t i = 0; i < it->second.size(); ++i) {
                if (i > 0) ss << ",";
                ss << it->second[i];
            }
            ss << "]";
        }
        ss << "}";
        return ss.str();
    }
    
    // 檢查是否達到目標狀態
    bool is_goal(int n) const {
        // 檢查每個環是否在正確的柱子上
        for (int i = 1; i <= n; ++i) {
            char target = "ABCD"[(i - 1) % 4];
            
            bool found = false;
            auto it = pegs.find(target);
            if (it != pegs.end()) {
                if (find(it->second.begin(), it->second.end(), i) != it->second.end()) {
                    found = true;
                }
            }
            
            if (!found) return false;
        }
        
        // 檢查每個柱子上的環是否按從大到小排列
        for (auto& p : pegs) {
            const vector<int>& peg = p.second;
            for (size_t i = 0; i < peg.size() - 1; ++i) {
                if (peg[i] < peg[i + 1]) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    // 獲取所有可能的移動
    vector<tuple<char, char, int>> get_possible_moves() const {
        vector<tuple<char, char, int>> moves;
        vector<char> peg_names = {'A', 'B', 'C', 'D'};
        
        for (char from_peg : peg_names) {
            auto from_it = pegs.find(from_peg);
            if (from_it == pegs.end() || from_it->second.empty()) {
                continue;
            }
            
            int ring = from_it->second.back();
            
            for (char to_peg : peg_names) {
                if (from_peg == to_peg) continue;
                
                auto to_it = pegs.find(to_peg);
                
                // 檢查是否可以移動
                if (to_it == pegs.end() || to_it->second.empty() || 
                    to_it->second.back() > ring) {
                    moves.push_back(make_tuple(from_peg, to_peg, ring));
                }
            }
        }
        
        return moves;
    }
    
    // 應用一個移動並返回新狀態
    State apply_move(const tuple<char, char, int>& move) const {
        char from_peg = get<0>(move);
        char to_peg = get<1>(move);
        int ring = get<2>(move);
        
        State new_state = this->clone();
        
        new_state.pegs[from_peg].pop_back();
        new_state.pegs[to_peg].push_back(ring);
        
        stringstream ss;
        ss << "ring " << ring << ": " << from_peg << "=>" << to_peg;
        new_state.moves.push_back(ss.str());
        
        return new_state;
    }
};

vector<string> solve_four_peg_four_color(int n) {
    // 初始狀態
    State initial;
    for (int i = n; i >= 1; --i) {
        initial.pegs['A'].push_back(i);
    }
    
    cout << "開始BFS搜索 N=" << n << "..." << endl;
    
    // BFS搜索
    deque<State> queue;
    queue.push_back(initial);
    
    unordered_set<string> visited;
    visited.insert(initial.hash_key());
    
    int iterations = 0;
    
    while (!queue.empty()) {
        iterations++;
        
        if (iterations % 50000 == 0) {
            cout << "已搜索 " << iterations << " 個狀態，隊列長度：" 
                 << queue.size() << endl;
        }
        
        State current = queue.front();
        queue.pop_front();
        
        if (current.is_goal(n)) {
            cout << "\n找到解！移動次數：" << current.moves.size() << endl;
            return current.moves;
        }
        
        vector<tuple<char, char, int>> possible_moves = current.get_possible_moves();
        
        for (const auto& move : possible_moves) {
            State next_state = current.apply_move(move);
            string hash_key = next_state.hash_key();
            
            if (visited.find(hash_key) == visited.end()) {
                visited.insert(hash_key);
                queue.push_back(next_state);
            }
        }
    }
    
    cout << "未找到解" << endl;
    return vector<string>();
}

int main() {
    int n;
    cout << "請輸入環的總數（4的倍數）：";
    cin >> n;
    
    if (n % 4 != 0) {
        cout << "錯誤：環的總數必須是4的倍數" << endl;
        return 1;
    }
    
    if (n < 4 || n > 280) {
        cout << "錯誤：N必須在4到280之間" << endl;
        return 1;
    }
    
    cout << "\n求解 N=" << n << " 的四柱四色河內塔..." << endl;
    cout << "注意：N較大時可能需要較長時間\n" << endl;
    
    vector<string> moves = solve_four_peg_four_color(n);
    
    if (!moves.empty()) {
        cout << "\n完整的 " << moves.size() << " 步移動序列：" << endl;
        cout << string(50, '=') << endl;
        
        for (size_t i = 0; i < moves.size(); ++i) {
            cout << (i + 1) << ". " << moves[i] << endl;
        }
        
        // 驗證解的正確性
        cout << "\n驗證解..." << endl;
        map<char, vector<int>> state;
        for (int i = n; i >= 1; --i) {
            state['A'].push_back(i);
        }
        state['B'] = vector<int>();
        state['C'] = vector<int>();
        state['D'] = vector<int>();
        
        for (const string& move : moves) {
            // 解析移動指令：ring X: Y=>Z
            size_t ring_pos = move.find("ring ") + 5;
            size_t colon_pos = move.find(": ");
            size_t arrow_pos = move.find("=>");
            
            int ring = stoi(move.substr(ring_pos, colon_pos - ring_pos));
            char from_peg = move[colon_pos + 2];
            char to_peg = move[arrow_pos + 2];
            
            // 執行移動
            auto& from_vec = state[from_peg];
            from_vec.erase(remove(from_vec.begin(), from_vec.end(), ring), from_vec.end());
            state[to_peg].push_back(ring);
        }
        
        // 檢查最終狀態
        bool correct = true;
        for (int i = 1; i <= n; ++i) {
            char target = "ABCD"[(i - 1) % 4];
            if (find(state[target].begin(), state[target].end(), i) == state[target].end()) {
                correct = false;
                break;
            }
        }
        
        if (correct) {
            cout << "✓ 解法正確！" << endl;
        } else {
            cout << "✗ 解法有誤" << endl;
        }
    }
    
    return 0;
}