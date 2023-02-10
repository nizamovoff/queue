#pragma once

#include <iostream>

template<typename ValueType>
class Queue {
public:
    explicit Queue();

    ~Queue();

    Queue(const Queue &other);

    Queue &operator=(const Queue &other);

    Queue(Queue &&other) noexcept;

    Queue &operator=(Queue &&other) noexcept;

    ValueType Front() const;

    ValueType Back() const;

    bool Empty() const;

    size_t Size() const;

    void Clear();

    void Push(const ValueType value);

    void Pop();

    void Swap(Queue &other);

private:
    const size_t kDefaultSize = 0;
    const size_t kDefaultIndex = 0;
    const size_t kDefaultCapacity = 0;
    static const size_t kDoubleCapacity = -1;

    size_t size_ = kDefaultSize;
    size_t first_ = kDefaultIndex;
    size_t capacity_ = kDefaultCapacity;
    ValueType *array_ = nullptr;

    size_t GetFirstIndex() const;

    size_t GetLastIndex() const;

    size_t GetNextIndex(size_t index) const;

    void AddMemory(size_t new_capacity = kDoubleCapacity);

    void Copy(const Queue &other);

    void MakeDefault(Queue &other) noexcept;
};

template<typename ValueType>
Queue<ValueType>::Queue() : size_(kDefaultSize), first_(kDefaultIndex), capacity_(kDefaultCapacity), array_(nullptr) {}

template<typename ValueType>
Queue<ValueType>::~Queue() {
    delete[] array_;
}

template<typename ValueType>
Queue<ValueType>::Queue(const Queue &other) {
    Copy(other);
}

template<typename ValueType>
Queue<ValueType> &Queue<ValueType>::operator=(const Queue &other) {
    if (this == &other) {
        return *this;
    }

    Copy(other);
    return *this;
}

template<typename ValueType>
Queue<ValueType>::Queue(Queue &&other) noexcept : size_(other.size_), first_(other.first_), capacity_(other.capacity_),
                                                  array_(other.array_) {
    MakeDefault(*&other);
}

template<typename ValueType>
Queue<ValueType> &Queue<ValueType>::operator=(Queue &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] array_;
    size_ = other.size_;
    first_ = other.first_;
    capacity_ = other.capacity_;
    array_ = other.array_;

    MakeDefault(*&other);
    return *this;
}

template<typename ValueType>
ValueType Queue<ValueType>::Front() const {
    if (size_ == 0) {
        // return signal 11: SIGSEGV
        exit(139);
    }
    return array_[GetFirstIndex()];
}

template<typename ValueType>
ValueType Queue<ValueType>::Back() const {
    if (size_ == 0) {
        // return signal 11: SIGSEGV
        exit(139);
    }
    return array_[GetLastIndex()];
}

template<typename ValueType>
bool Queue<ValueType>::Empty() const {
    return size_ == 0;
}

template<typename ValueType>
size_t Queue<ValueType>::Size() const {
    return size_;
}

template<typename ValueType>
void Queue<ValueType>::Clear() {
    delete[] array_;
    MakeDefault(*this);
}

template<typename ValueType>
void Queue<ValueType>::Push(const ValueType value) {
    if (size_ >= capacity_) {
        AddMemory();
    }
    if (size_ == 0) {
        array_[first_] = value;
    } else {
        array_[GetNextIndex(GetLastIndex())] = value;
    }
    size_++;
}

template<typename ValueType>
void Queue<ValueType>::Pop() {
    if (size_ == 0) {
        // return signal 11: SIGSEGV
        exit(139);
    }
    first_ = GetNextIndex(first_);
    --size_;
}

template<typename ValueType>
void Queue<ValueType>::Swap(Queue &other) {
    std::swap(*this, other);
}

template<typename ValueType>
size_t Queue<ValueType>::GetFirstIndex() const {
    return first_;
}

template<typename ValueType>
size_t Queue<ValueType>::GetLastIndex() const {
    size_t index = first_ + size_ - 1;
    if (index >= capacity_) {
        index -= capacity_;
    }
    return index;
}

template<typename ValueType>
size_t Queue<ValueType>::GetNextIndex(size_t index) const {
    ++index;
    if (index >= capacity_) {
        index -= capacity_;
    }
    return index;
}

template<typename ValueType>
void Queue<ValueType>::AddMemory(size_t new_capacity) {
    if (new_capacity == kDoubleCapacity) {
        new_capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
    }

    ValueType *old_array = array_;
    array_ = new ValueType[new_capacity];

    int index = GetFirstIndex();
    for (size_t i = 0; i < size_; ++i) {
        array_[i] = old_array[index];
        index = GetNextIndex(index);
    }

    capacity_ = new_capacity;
    delete[] old_array;
}

template<typename ValueType>
void Queue<ValueType>::Copy(const Queue &other) {
    AddMemory(other.capacity_);
    size_ = other.size_;
    first_ = kDefaultIndex;

    int index = other.first_;
    for (size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[index];
        index = GetNextIndex(index);
    }
}

template<typename ValueType>
void Queue<ValueType>::MakeDefault(Queue &other) noexcept {
    other.size_ = kDefaultSize;
    other.first_ = kDefaultIndex;
    other.capacity_ = kDefaultCapacity;
    other.array_ = nullptr;
}
