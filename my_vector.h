#pragma once
namespace my
{
    template <typename T>
    class vector
    {
    private:
        T* werte_; 
        size_t size_;
        size_t capacity_;

    public:
        //Ctor, Dtor
        vector<T>(int N = 0, T wert = T());
        vector<T>(const vector<T>& rhs);
        vector<T>(vector<T>&& rhs);
        vector<T>& operator=(vector<T> rhs);
        ~vector<T>();

        //methods
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        void clear();
        void reserve(size_t new_capacity);
        void shrink_to_fit();
        void push_back(const T& wert);
        T pop_back();
        T &operator[](size_t i);
        T operator[](size_t i) const;
        T &at(size_t i);
        T at(size_t) const;
    };

    // Implementation: constructors
    template <typename T>
    my::vector<T>::vector(int N, T wert)
    : werte_(nullptr), size_(0), capacity_(0){
    if(N != 0) reserve(N);
    if(wert != T()){
        push_back(wert);
    }
};

    // Copy Ctor
    template <typename T>
    my::vector<T>::vector(const vector<T>& rhs) : werte_(nullptr), size_(0), capacity_(0){
        if(rhs.capacity() != 0) reserve(rhs.capacity());
        for(int i = 0; i < rhs.size(); i++) {
            push_back(rhs[i]);
        }
    };

    // Move Ctor
    template <typename T>
    my::vector<T>::vector(vector<T>&& rhs) : vector<T>(){
        std::swap(*this, rhs);
    }

    // copy-assign
    template <typename T>
    my::vector<T>& my::vector<T>::operator=(vector<T> rhs) {
        std::swap(*this, rhs);
        return *this;
    }

    // Dtor
    template <typename T>
    my::vector<T>::~vector<T>() {
        if(capacity() <= 0) {
            return;
        }
        for (size_t i = 0; i < size(); i++)
        {
            (werte_+i) -> ~T();
        }
        free(werte_);
        
    }

    // Implementation: methods
    template <typename T>
    size_t my::vector<T>::size() const
    {
        return size_;
    };

    template <typename T>
    size_t my::vector<T>::capacity() const
    {
        return capacity_;
    };

    template <typename T>
    bool my::vector<T>::empty() const
    {
        return size_ == 0;
    };

    template <typename T>
    void my::vector<T>::clear()
    {
        for(int i=0; i < size(); i++){
            pop_back();
        }
        size_ = 0;
    };
    
    template <typename T>
    void my::vector<T>::reserve(size_t new_capacity)
    {
        if(new_capacity == 0) new_capacity = 1; // wenn nichts übergeben, dann trotzdem eins reserviert, sonst crashed pushback, falls als nächstes aufgerufen
        if(new_capacity < size()) return; // falls zu kleine capacity übergeben wird
        void* memoryBlock = malloc(new_capacity * sizeof(T)); //malloc für memory Reservierung
        T* temp = static_cast<T*>(memoryBlock); //cast Type von void* zu T*
        for(int i = 0; i < size(); i++) {
            new (temp+i) T (std::move(werte_[i]));
        }

        //das memory dem Pointer zuweisen
        for(int i = 0; i < size(); i++) (werte_+i) -> ~T();
        werte_=std::move(temp);
        capacity_ = new_capacity;
    }

    template <typename T>
    void my::vector<T>::shrink_to_fit(){
        reserve(size());
    }

    template <typename T>
    void my::vector<T>::push_back(const T& wert)
    {
        if(size() >= capacity()) reserve(capacity() * 2); //weiteren Speicher allozieren
        new(werte_+size()) T (wert);                       //neues Object hinten anfügen
        size_++;
    };

    template <typename T>
    T my::vector<T>::pop_back()
    {
        if(empty()) throw std::out_of_range("Vector empty");
        T back = werte_[size_ - 1];
        (werte_ + size_ - 1) -> ~T();
        size_--;
        return back;
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