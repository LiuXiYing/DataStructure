#ifndef VECTOR_H
#define VECTOR_H

typedef int Rank;

template <typename T>
class Vector {
private:
    Rank _size;
    Rank _capacity;
    T* _elem;

protected:
    void expand() {
        if (_size < _capacity) return;
        _capacity = (_capacity < 3) ? 3 : _capacity * 2;
        T* oldElem = _elem;
        _elem = new T[_capacity];
        for (Rank i = 0; i < _size; ++i)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

public:
    Vector(Rank c = 3) {
        _capacity = (c <= 0) ? 3 : c;
        _size = 0;
        _elem = new T[_capacity];
    }

    ~Vector() { delete[] _elem; }

    Vector(const Vector&) = delete;
    Vector& operator=(const Vector&) = delete;

    Rank size() const { return _size; }
    bool empty() const { return _size == 0; }
    Rank capacity() const { return _capacity; }

    T& operator[](Rank r) { return _elem[r]; }
    const T& operator[](Rank r) const { return _elem[r]; }

    Rank find(const T& e) const {
        for (Rank i = _size - 1; i >= 0; --i)
            if (_elem[i] == e) return i;
        return -1;
    }

    Rank insert(Rank r, const T& e) {
        T value = e; // 先保存副本，防止扩容导致引用失效
        expand();
        for (Rank i = _size; i > r; --i)
            _elem[i] = _elem[i - 1];
        _elem[r] = value;
        ++_size;
        return r;
    }

    Rank insert(const T& e) { return insert(_size, e); }

    T remove(Rank r) {
        T value = _elem[r];
        for (Rank i = r; i < _size - 1; ++i)
            _elem[i] = _elem[i + 1];
        --_size;
        return value;
    }

    Rank remove(Rank lo, Rank hi) {
        if (lo == hi) return 0;
        Rank n = hi - lo;
        for (Rank i = hi; i < _size; ++i)
            _elem[lo++] = _elem[i];
        _size -= n;
        return n;
    }
};

#endif