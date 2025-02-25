#include <iostream>
using namespace std;
class A
{
public:
    A(int size) : size_(size)
    {
        data_ = new int[size];
        *data_ = size;
    }
    A() {}
    A(A &a)
    {
        this->data_ = a.data_;
        a.data_ = nullptr;
        cout << "move " << endl;
    }
    A(A &&a)
    {
        size_ = a.size_;
        data_ = new int[size_];
        *data_ = *a.data_;
        cout << "copy " << endl;
    }
    ~A()
    {
        if (data_ != nullptr)
        {
            delete[] data_;
        }
        cout << "~A()\n";
    }
    int *data_;
    int size_;
};
int main()
{
    A a(10);
    A b(a);
    cout << *b.data_<<endl;
    return 0;
}