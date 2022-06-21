#pragma once
namespace my
{
    template <typename ValueT>
    class vector
    {
    private:
        ValueT *werte_;
        size_t size_;
        size_t capacity_;
        void fill(const ValueT &wert);

    public:
        // Ctor, Dtor
        vector<ValueT>();
        vector<ValueT>(const size_t& n, const ValueT& wert);
        vector<ValueT>(const vector<ValueT> &rhs);
        vector<ValueT>(vector<ValueT> &&rhs);
        vector<ValueT> &operator=(vector<ValueT> rhs);
        ~vector<ValueT>();

        // methods
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        void clear();
        void reserve(size_t new_capacity);
        void shrink_to_fit();
        void push_back(const ValueT &wert);
        ValueT pop_back();
        ValueT &operator[](size_t i);
        ValueT operator[](size_t i) const;
        ValueT &at(size_t i);
        ValueT at(size_t) const;
    };
}

    // Implementation: constructors
    template <typename ValueT>
    my::vector<ValueT>::vector()
        : werte_(nullptr), size_(0), capacity_(0)
    {
    }

    template <typename ValueT>
    my::vector<ValueT>::vector(const size_t& n, const ValueT& wert) : werte_(nullptr), size_(0), capacity_(0)
    {
        push_back(wert);
        for(size_t i= 1; i < n; i++){
            new (werte_ + i) ValueT(wert);
            capacity_++;
        }
    }

    // Copy Ctor
    template <typename ValueT>
    my::vector<ValueT>::vector(const vector<ValueT> &rhs) : werte_(nullptr), size_(0), capacity_(0)
    {
        if (rhs.capacity() != 0)
            reserve(rhs.capacity());
        for (size_t i = 0; i < rhs.size(); i++)
        {
            push_back(rhs[i]);
        }
    };

    // Move Ctor
    template <typename ValueT>
    my::vector<ValueT>::vector(vector<ValueT> &&rhs) : vector<ValueT>()
    {
        std::swap(*this, rhs);
    }

    // copy-assign
    template <typename ValueT>
    my::vector<ValueT> &my::vector<ValueT>::operator=(vector<ValueT> rhs)
    {
        std::swap(*this, rhs);
        return *this;
    }

    // Dtor
    template <typename ValueT>
    my::vector<ValueT>::~vector()
    {
        if(capacity()<= 0)
        {
        return;
        }

        for (size_t i = 0; i < capacity(); i++)
        {
            (werte_ + i) -> ~ValueT();
        }

    free(werte_);
    }

// Implementation: methods
template <typename ValueT>
size_t my::vector<ValueT>::size() const
{
    return size_;
};

template <typename ValueT>
size_t my::vector<ValueT>::capacity() const
{
    return capacity_;
};

template <typename ValueT>
bool my::vector<ValueT>::empty() const
{
    return size_ == 0;
};

template <typename ValueT>
void my::vector<ValueT>::clear()
{
    for (int i = 0; i < size(); i++)
    {
        pop_back();
    }
    size_ = 0;
};

template <typename ValueT>
void my::vector<ValueT>::reserve(size_t new_capacity)
{
    std::cout << "neuie cap ::" << new_capacity << std::endl;
    int new_capacity_int = new_capacity;
    if(new_capacity_int == 0){
        new_capacity = 1;  // in case capacity is not specified and reserved is being called by push_back
    };
    if(new_capacity < size()) return;  // new_capacity must be bigger

    void* memory = malloc(new_capacity * sizeof(ValueT));     // reserving memory
    ValueT* temp = static_cast<ValueT*>(memory);

    for(int i = 0; i < size(); i++){
        new (temp+i) ValueT (std::move(werte_[i]));
    };

    // assigning new allocated memory to intern pointer
    for(int i = 0; i< size(); i++){
        (werte_+i) -> ~ValueT();
    };

    werte_=std::move(temp);

    capacity_ = new_capacity;


}

template <typename ValueT>
void my::vector<ValueT>::shrink_to_fit()
{
    reserve(size());
}

template <typename ValueT>
void my::vector<ValueT>::push_back(const ValueT &wert)
{
    if (size() >= capacity())
        reserve(capacity() + capacity());        // weiteren Speicher allozieren
    new (werte_ + size()) ValueT(wert); // neues Object hinten anfügen
    size_++;
};

template <typename ValueT>
ValueT my::vector<ValueT>::pop_back()
{
    if (empty())
        throw std::out_of_range("Vector empty");
    ValueT back = werte_[size_ - 1];
    (werte_ + size_ - 1)->~ValueT();
    size_--;
    return back;
};

template <typename ValueT>
ValueT &my::vector<ValueT>::operator[](size_t i)
{
    return werte_[i];
}

template <typename ValueT>
ValueT my::vector<ValueT>::operator[](size_t i) const
{
    return werte_[i];
}

template <typename ValueT>
ValueT &my::vector<ValueT>::at(size_t i)
{
    if (size_ <= i)
        throw std::out_of_range("Index out of range!");
    return werte_[i];
}

template <typename ValueT>
ValueT my::vector<ValueT>::at(size_t i) const
{
    if (size_ <= i)
        throw std::out_of_range("Index out of range!");
    return werte_[i];
}