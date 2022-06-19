#pragma once
namespace my
{
    template <typename T>
    class vector
    {
    private:
        T* werte_; 
        size_t size_;

    public:
        //constructor, deconstructor
        vector<T>(int size = 0, T wert = T()); //derefferenzieren ist wichtig, sonst malloc error von test_it, da new nur referenz gibt
        vector<T>(int size);
        ~vector<T>(){delete[] werte_;}

        //methods
        bool empty() const;
        size_t size() const;
        void clear();
        void push_back(const T &wert);
        T pop_back();
        T &operator[](size_t i);
        T operator[](size_t i) const;
        T &at(size_t i);
        T at(size_t) const;
        vector(vector<T> const &) = delete;
        vector<T> &operator=(vector<T> const &) = delete;
    };

    // Implementation: constructors
    template <typename T>
    my::vector<T>::vector(int n, T wert) : werte_(new T[n]), size_(n)
    {
        werte_[0] = wert; 
    };

    template <typename T>
    my::vector<T>::vector(int n) : werte_(new T[n]), size_(n){};

    // Implementation: methods
    template <typename T>
    size_t my::vector<T>::size() const
    {
        return size_;
    };

    template <typename T>
    bool my::vector<T>::empty() const
    {
        return size_ == 0;
    };

    template <typename T>
    void my::vector<T>::clear()
    {
        delete[] werte_;
    };

    template <typename T>
    void my::vector<T>::push_back(const T &wert)
    {
        size_ += 1;
        auto temp = werte_;
        werte_ = new T[size_];
        for(int i = 0; i < size_-1; i++) {
            werte_[i] = temp[i];
        }
        delete[] temp;
        werte_[size_-1] = wert;
    };

    template <typename T>
    T my::vector<T>::pop_back()
    {
        auto temp = werte_;
        size_ -= 1;
        werte_ = new T[size_];
        for(int i = 0; i < size_; i++) {
            werte_[i] = temp[i];
        }
        auto tempElement = temp[size_];
        delete[] temp;
        return tempElement;
    };

    template <typename T>
    T& my::vector<T>::operator[](size_t i) {
        return werte_[i];
    }

    template <typename T>
    T my::vector<T>::operator[](size_t i) const{
        return werte_[i];
    }

    template <typename T>
    T& my::vector<T>::at(size_t i) {
        if(size_ <= i) throw std::out_of_range("Index out of range!");
        return werte_[i];
    }

    template <typename T>
    T my::vector<T>::at(size_t i) const {
        if(size_ <= i) throw std::out_of_range("Index out of range!");
        return werte_[i];
    }
}