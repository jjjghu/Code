#include <iostream>
int main(void) {
    std::string s;
    std::cin >> s;
    if(s.size()) {
        s[0] = toupper(s[0]);
    }
    std::cout << s;
}