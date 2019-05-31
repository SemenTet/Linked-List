#include <iostream>

template<typename Tp>
class list
{
private:
    struct node
    {
        node* next;
        Tp data;
    };

public:
    class iterator
    {
        friend class list;

    private:
        node* nd_;

    public:
        Tp* base() const noexcept
        {
            return &nd_->data;
        }

        Tp* operator->() const noexcept
        {
            return &nd_->data;
        }

        Tp& operator*() const noexcept
        {
            return nd_->data;
        }

        iterator& operator++() noexcept
        {
            nd_ = nd_->next;
            return *this;
        }

        iterator& operator++(int) noexcept
        {
            nd_ = nd_->next;
            return *this;
        }

        bool operator==(iterator i) const noexcept
        {
            return i.nd_ == nd_;
        }

        bool operator!=(iterator i) const noexcept
        {
            return i.nd_ != nd_;
        }

    private:
        iterator(node* nd) : nd_(nd) { }
    };

private:
    node* first_ = nullptr;
    node* last_ = nullptr;
    size_t size_ = 0;

public:
    list() = default;

    template<typename T>
    list(std::initializer_list<T> l)
    {
        for (auto e : l)
            push_back(e);
    }

    template<typename U>
    void push_back(U&& value)
    {
        auto new_node = new node{nullptr, std::forward<U>(value)};
        if (last_)
            last_->next = new_node;
        else
            first_ = new_node;
        last_ = new_node;
        ++size_;
    }

    void erase_after(iterator i)
    {
        auto new_next = i.nd_->next->next;
        delete i.nd_->next;
        i.nd_->next = new_next;
        --size_;
    }

    iterator begin()
    {
        return first_;
    }

    iterator end()
    {
        return nullptr;
    }

    auto size() const noexcept
    {
        return size_;
    }
};

//template<typename T>
//list(std::initializer_list<T>) -> list<T>;

int main()
{
    list <int> l{1, 2, 3, 4, 5};

    for (auto e : l)
        std::cout << e << std::endl;

    auto two_itr = l.begin()++;
    l.erase_after(two_itr);

    for (auto e : l)
        std::cout << e << std::endl;

    l.push_back(6);
    for (auto e : l)
        std::cout << e << std::endl;

    return 0;
}

