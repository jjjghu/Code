#include <iostream>
#include <string>
using namespace std;
int main(void) 
{
    string a, b;
    while(cin >> a >> b)
    {
        int a_freq[26]{}, b_freq[26]{};
        for(char c : a) {
            ++a_freq[c - 'a'];
        }
        for(char c : b) {
            ++b_freq[c - 'a'];
        }
        string x;
        for(int i = 0; i < 26; ++i) {
            // for(int cnt = 0; cnt < min(a_freq[i], b_freq[i]); ++cnt){
            //     x += (char)(i + 'a');
            // }
            x.append(min(a_freq[i], b_freq[i]), i + 'a');
        }
        cout << x << endl;
    }    
}