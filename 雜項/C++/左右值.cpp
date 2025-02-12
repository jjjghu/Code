#include <iostream>
class A
{
public:
    A()
    {
        std::cout << "A() \n";
    }

    ~A()
    {
        std::cout << "~A() \n";
    }

    A(const A &a)
    {
        count_ = a.count_;
        std::cout << "A copy \n";
    }

    A &operator=(const A &a)
    {
        count_ = a.count_;
        std::cout << "A = \n";
        return *this;
    }

    A(A &&a)
    {
        count_ = a.count_;
        std::cout << "A move \n";
    }

    A &operator=(A &&a)
    {
        count_ = a.count_;
        std::cout << "A move = \n";
        return *this;
    }

    std::string count_;
};

int main()
{
    A a; // A()
    a.count_ = "12345";
    A b = std::move(a);                 // A move
    A c;                                // A()
    c = std::move(b);                   // A move =
    std::cout << a.count_ << std::endl; // 12345
    std::cout << b.count_ << std::endl; // 12345
    return 0;
}