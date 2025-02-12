#include <iostream>
#include <memory>

class Child;
class Parent;

class Parent
{
public:
    std::shared_ptr<Child> in_class_child;
    Parent() { std::cout << "Parent 產生\n"; }
    ~Parent() { std::cout << "Parent 被釋放\n"; }
};

class Child
{
public:
    // 錯誤寫法：會造成循環引用
    std::shared_ptr<Parent> in_class_parent;

    // 正確寫法：使用 weak_ptr
    // std::weak_ptr<Parent> parent;
    Child() { std::cout << "Child 產生\n"; }
    ~Child() { std::cout << "Child 被釋放\n"; }
};

int main()
{
    std::shared_ptr<Parent> parent(new Parent());
    std::shared_ptr<Child> child(new Child());

    parent->in_class_child = child;
    child->in_class_parent = parent; // 這裡是關鍵差異
    return 0;
}