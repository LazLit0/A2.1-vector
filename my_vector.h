#pragma once
namespace my
{
    template <typename T>
    class vector
    {
    private:
        int capacity;
        size_t current;
        T* werte_; 

    public:
        vector();
        vector(int size, T wert);
        vector(int size);
        ~vector();
        // bool empty();
        size_t size();
        // clear();
        // push_back(const T &);
        // pop_back();
        // T &operator[](size_t i);
        // T operator[](size_t i) const;
        // at(size_t i);
        vector(vector<T> const &) = delete;
        vector<T> &operator=(vector<T> const &) = delete;
    };

    template <typename T>
    vector<T>::vector() : werte_(new T[0]){
        capacity = 0;
        current = 0;
    };

    template <typename T>
    vector<T>::vector(int n, T wert) : werte_(new T[n]){
        capacity = n;
        current = 0;
        werte_[0] = wert;
                               };

    template <typename T>
    vector<T>::vector(int n) : werte_(new T[n]){
        capacity = n;
        current = 0;
    };

    template <typename T>
    vector<T>::~vector()
    {
        delete werte_;
    };

    template <typename T>
    size_t vector<T>::size()
    {
        return capacity;
    };

}