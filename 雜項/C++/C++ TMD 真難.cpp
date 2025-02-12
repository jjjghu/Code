// 手撕智能指針!

// 實現unique_ptr（獨佔所有權）
template <typename T>
class my_unique_ptr
{
public:
    explicit my_unique_ptr(T *p = nullptr) : ptr(p) {}

    ~my_unique_ptr() { delete ptr; }

    // 禁用拷貝
    my_unique_ptr(const my_unique_ptr &) = delete;
    my_unique_ptr &operator=(const my_unique_ptr &) = delete;

    // 允許移動語義
    my_unique_ptr(my_unique_ptr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    my_unique_ptr &operator=(my_unique_ptr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
    T *get() const { return ptr; }

    // 釋放所有權
    T *release()
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T *p = nullptr)
    {
        delete ptr;
        ptr = p;
    }

private:
    T *ptr;
};

// 實現shared_ptr（共享所有權）
template <typename T>
class my_shared_ptr
{
public:
    explicit my_shared_ptr(T *p = nullptr) : ptr(p), count(new long(1)) {}

    // 拷貝構造
    my_shared_ptr(const my_shared_ptr &other) : ptr(other.ptr), count(other.count)
    {
        ++(*count);
    }

    ~my_shared_ptr()
    {
        if (--(*count) == 0)
        {
            delete ptr;
            delete count;
        }
    }

    // 賦值操作符
    my_shared_ptr &operator=(const my_shared_ptr &other)
    {
        if (this != &other)
        {
            // 先減少原引用
            if (--(*count) == 0)
            {
                delete ptr;
                delete count;
            }

            ptr = other.ptr;
            count = other.count;
            ++(*count);
        }
        return *this;
    }

    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
    T *get() const { return ptr; }

    long use_count() const { return *count; }

private:
    T *ptr;
    long *count; // 引用計數
};