#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>

/**
 * @file Vector.h
 * @brief Custom Vector container — drop-in replacement for std::vector.
 */

/**
 * @class Vector
 * @brief Dynamic array template container mimicking std::vector.
 *
 * Uses raw heap memory (operator new / placement new) so elements are only
 * constructed when needed, exactly like the standard library implementation.
 *
 * @tparam T Element type.
 */
template <typename T>
class Vector {
public:
    // ── Member types ──────────────────────────────────────────────────────────
    using value_type             = T;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;

    // ── iterator ──────────────────────────────────────────────────────────────
    /**
     * @class iterator
     * @brief Random-access iterator over Vector elements.
     */
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() noexcept : ptr_(nullptr) {}
        explicit iterator(T* p) noexcept : ptr_(p) {}

        reference operator*()  const noexcept { return *ptr_; }
        pointer   operator->() const noexcept { return ptr_; }
        reference operator[](difference_type n) const noexcept { return ptr_[n]; }

        iterator& operator++()    noexcept { ++ptr_; return *this; }
        iterator  operator++(int) noexcept { iterator t(*this); ++ptr_; return t; }
        iterator& operator--()    noexcept { --ptr_; return *this; }
        iterator  operator--(int) noexcept { iterator t(*this); --ptr_; return t; }

        iterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; }
        iterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; }
        iterator  operator+(difference_type n) const noexcept { return iterator(ptr_ + n); }
        iterator  operator-(difference_type n) const noexcept { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& o) const noexcept { return ptr_ - o.ptr_; }

        friend iterator operator+(difference_type n, const iterator& it) noexcept {
            return iterator(it.ptr_ + n);
        }

        bool operator==(const iterator& o) const noexcept { return ptr_ == o.ptr_; }
        bool operator!=(const iterator& o) const noexcept { return ptr_ != o.ptr_; }
        bool operator< (const iterator& o) const noexcept { return ptr_ <  o.ptr_; }
        bool operator<=(const iterator& o) const noexcept { return ptr_ <= o.ptr_; }
        bool operator> (const iterator& o) const noexcept { return ptr_ >  o.ptr_; }
        bool operator>=(const iterator& o) const noexcept { return ptr_ >= o.ptr_; }

        T* base() const noexcept { return ptr_; }
    private:
        T* ptr_;
    };

    // ── const_iterator ────────────────────────────────────────────────────────
    /**
     * @class const_iterator
     * @brief Read-only random-access iterator over Vector elements.
     */
    class const_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() noexcept : ptr_(nullptr) {}
        explicit const_iterator(const T* p) noexcept : ptr_(p) {}
        const_iterator(const iterator& it) noexcept : ptr_(it.base()) {}

        reference operator*()  const noexcept { return *ptr_; }
        pointer   operator->() const noexcept { return ptr_; }
        reference operator[](difference_type n) const noexcept { return ptr_[n]; }

        const_iterator& operator++()    noexcept { ++ptr_; return *this; }
        const_iterator  operator++(int) noexcept { const_iterator t(*this); ++ptr_; return t; }
        const_iterator& operator--()    noexcept { --ptr_; return *this; }
        const_iterator  operator--(int) noexcept { const_iterator t(*this); --ptr_; return t; }

        const_iterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; }
        const_iterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; }
        const_iterator  operator+(difference_type n) const noexcept { return const_iterator(ptr_ + n); }
        const_iterator  operator-(difference_type n) const noexcept { return const_iterator(ptr_ - n); }
        difference_type operator-(const const_iterator& o) const noexcept { return ptr_ - o.ptr_; }

        friend const_iterator operator+(difference_type n, const const_iterator& it) noexcept {
            return const_iterator(it.ptr_ + n);
        }

        bool operator==(const const_iterator& o) const noexcept { return ptr_ == o.ptr_; }
        bool operator!=(const const_iterator& o) const noexcept { return ptr_ != o.ptr_; }
        bool operator< (const const_iterator& o) const noexcept { return ptr_ <  o.ptr_; }
        bool operator<=(const const_iterator& o) const noexcept { return ptr_ <= o.ptr_; }
        bool operator> (const const_iterator& o) const noexcept { return ptr_ >  o.ptr_; }
        bool operator>=(const const_iterator& o) const noexcept { return ptr_ >= o.ptr_; }

        const T* base() const noexcept { return ptr_; }
    private:
        const T* ptr_;
    };

    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // ── Private helpers ───────────────────────────────────────────────────────
private:
    T*        data_;
    size_type size_;
    size_type capacity_;

    static T* mem_alloc(size_type n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    static void mem_free(T* p) noexcept {
        ::operator delete(p);
    }
    void destroy_range(size_type from, size_type to) noexcept {
        for (size_type i = from; i < to; ++i)
            data_[i].~T();
    }
    void reallocate(size_type new_cap) {
        T* nd = mem_alloc(new_cap);
        size_type i = 0;
        try {
            for (; i < size_; ++i)
                new(nd + i) T(std::move_if_noexcept(data_[i]));
        } catch (...) {
            for (size_type j = 0; j < i; ++j) nd[j].~T();
            mem_free(nd);
            throw;
        }
        destroy_range(0, size_);
        mem_free(data_);
        data_     = nd;
        capacity_ = new_cap;
    }
    size_type next_cap() const noexcept {
        return capacity_ == 0 ? 1 : capacity_ * 2;
    }

    // Build a fresh buffer with all existing elements + n slots inserted at idx.
    // Used by multi-element insert variants to keep the logic simple and correct.
    template <typename F>
    iterator insert_impl(size_type idx, size_type n, F&& fill) {
        if (n == 0) return iterator(data_ + idx);
        Vector tmp;
        tmp.data_     = mem_alloc(size_ + n);
        tmp.capacity_ = size_ + n;
        // Move [0, idx) into tmp
        for (size_type i = 0; i < idx; ++i)
            new(tmp.data_ + tmp.size_++) T(std::move(data_[i]));
        // Fill n new elements
        fill(tmp);
        // Move [idx, size_) into tmp
        for (size_type i = idx; i < size_; ++i)
            new(tmp.data_ + tmp.size_++) T(std::move(data_[i]));
        swap(tmp);
        return iterator(data_ + idx);
    }

public:
    // ── Constructors ──────────────────────────────────────────────────────────

    /// Default constructor — empty vector, no allocation.
    Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

    /// Constructs a vector with @p n value-initialised elements.
    explicit Vector(size_type n) : data_(nullptr), size_(0), capacity_(0) {
        if (n == 0) return;
        data_     = mem_alloc(n);
        capacity_ = n;
        for (; size_ < n; ++size_)
            new(data_ + size_) T();
    }

    /// Constructs a vector with @p n copies of @p val.
    Vector(size_type n, const T& val) : data_(nullptr), size_(0), capacity_(0) {
        if (n == 0) return;
        data_     = mem_alloc(n);
        capacity_ = n;
        for (; size_ < n; ++size_)
            new(data_ + size_) T(val);
    }

    /// Range constructor — copies elements from [@p first, @p last).
    template <typename InputIt,
              typename = typename std::enable_if<
                  !std::is_integral<InputIt>::value>::type>
    Vector(InputIt first, InputIt last) : data_(nullptr), size_(0), capacity_(0) {
        for (auto it = first; it != last; ++it)
            push_back(*it);
    }

    /// Initialiser-list constructor.
    Vector(std::initializer_list<T> il) : data_(nullptr), size_(0), capacity_(0) {
        reserve(il.size());
        for (const auto& v : il)
            new(data_ + size_++) T(v);
    }

    /// Copy constructor.
    Vector(const Vector& o) : data_(nullptr), size_(0), capacity_(0) {
        if (o.size_ == 0) return;
        data_     = mem_alloc(o.size_);
        capacity_ = o.size_;
        for (; size_ < o.size_; ++size_)
            new(data_ + size_) T(o.data_[size_]);
    }

    /// Move constructor — takes ownership, leaves @p o empty.
    Vector(Vector&& o) noexcept
        : data_(o.data_), size_(o.size_), capacity_(o.capacity_) {
        o.data_ = nullptr; o.size_ = 0; o.capacity_ = 0;
    }

    /// Destructor.
    ~Vector() {
        destroy_range(0, size_);
        mem_free(data_);
    }

    // ── Assignment ────────────────────────────────────────────────────────────

    /// Copy assignment.
    Vector& operator=(const Vector& o) {
        if (this != &o) { Vector tmp(o); swap(tmp); }
        return *this;
    }

    /// Move assignment.
    Vector& operator=(Vector&& o) noexcept {
        if (this != &o) {
            destroy_range(0, size_);
            mem_free(data_);
            data_ = o.data_; size_ = o.size_; capacity_ = o.capacity_;
            o.data_ = nullptr; o.size_ = 0; o.capacity_ = 0;
        }
        return *this;
    }

    /// Initialiser-list assignment.
    Vector& operator=(std::initializer_list<T> il) {
        assign(il); return *this;
    }

    /// Replaces contents with @p n copies of @p val.
    void assign(size_type n, const T& val) {
        clear();
        reserve(n);
        for (size_type i = 0; i < n; ++i)
            new(data_ + size_++) T(val);
    }

    /// Replaces contents with the range [@p first, @p last).
    template <typename InputIt,
              typename = typename std::enable_if<
                  !std::is_integral<InputIt>::value>::type>
    void assign(InputIt first, InputIt last) {
        clear();
        for (auto it = first; it != last; ++it)
            push_back(*it);
    }

    /// Replaces contents with initialiser list.
    void assign(std::initializer_list<T> il) {
        clear();
        reserve(il.size());
        for (const auto& v : il)
            new(data_ + size_++) T(v);
    }

    // ── Element access ────────────────────────────────────────────────────────

    /// Bounds-checked element access; throws std::out_of_range.
    reference at(size_type pos) {
        if (pos >= size_) throw std::out_of_range("Vector::at");
        return data_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= size_) throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    reference       operator[](size_type pos)       noexcept { return data_[pos]; }
    const_reference operator[](size_type pos) const noexcept { return data_[pos]; }

    reference       front()       noexcept { return data_[0]; }
    const_reference front() const noexcept { return data_[0]; }
    reference       back()        noexcept { return data_[size_ - 1]; }
    const_reference back()  const noexcept { return data_[size_ - 1]; }

    T*       data()       noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    // ── Iterators ─────────────────────────────────────────────────────────────

    iterator       begin()        noexcept { return iterator(data_); }
    iterator       end()          noexcept { return iterator(data_ + size_); }
    const_iterator begin()  const noexcept { return const_iterator(data_); }
    const_iterator end()    const noexcept { return const_iterator(data_ + size_); }
    const_iterator cbegin() const noexcept { return const_iterator(data_); }
    const_iterator cend()   const noexcept { return const_iterator(data_ + size_); }

    reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
    reverse_iterator       rend()          noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend()    const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend()   const noexcept { return const_reverse_iterator(cbegin()); }

    // ── Capacity ──────────────────────────────────────────────────────────────

    bool      empty()    const noexcept { return size_ == 0; }
    size_type size()     const noexcept { return size_; }
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
    size_type capacity() const noexcept { return capacity_; }

    /// Increases capacity to at least @p new_cap. No-op if already sufficient.
    void reserve(size_type new_cap) {
        if (new_cap > capacity_) reallocate(new_cap);
    }

    /// Reduces capacity to match size (non-binding hint per standard).
    void shrink_to_fit() {
        if (size_ == capacity_) return;
        if (size_ == 0) {
            mem_free(data_); data_ = nullptr; capacity_ = 0; return;
        }
        reallocate(size_);
    }

    // ── Modifiers ─────────────────────────────────────────────────────────────

    /// Destroys all elements; capacity unchanged.
    void clear() noexcept {
        destroy_range(0, size_);
        size_ = 0;
    }

    /// Appends a copy of @p val; reallocates if capacity is exhausted.
    void push_back(const T& val) {
        if (size_ == capacity_) reallocate(next_cap());
        new(data_ + size_++) T(val);
    }

    /// Appends @p val by move; reallocates if capacity is exhausted.
    void push_back(T&& val) {
        if (size_ == capacity_) reallocate(next_cap());
        new(data_ + size_++) T(std::move(val));
    }

    /// In-place constructs an element at the end.
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (size_ == capacity_) reallocate(next_cap());
        new(data_ + size_) T(std::forward<Args>(args)...);
        return data_[size_++];
    }

    /// Removes the last element; undefined if empty.
    void pop_back() noexcept { data_[--size_].~T(); }

    /// Resizes to @p n elements, value-initialising any new ones.
    void resize(size_type n) {
        if (n < size_) { destroy_range(n, size_); size_ = n; }
        else if (n > size_) {
            if (n > capacity_) reallocate(n);
            for (; size_ < n; ++size_) new(data_ + size_) T();
        }
    }

    /// Resizes to @p n elements, filling new slots with @p val.
    void resize(size_type n, const T& val) {
        if (n < size_) { destroy_range(n, size_); size_ = n; }
        else if (n > size_) {
            if (n > capacity_) reallocate(n);
            for (; size_ < n; ++size_) new(data_ + size_) T(val);
        }
    }

    /// Swaps contents with @p o in O(1).
    void swap(Vector& o) noexcept {
        std::swap(data_,     o.data_);
        std::swap(size_,     o.size_);
        std::swap(capacity_, o.capacity_);
    }

    // ── insert ────────────────────────────────────────────────────────────────

    /// Inserts a copy of @p val before @p pos.
    iterator insert(const_iterator pos, const T& val) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        if (size_ == capacity_) reallocate(next_cap());
        if (idx < size_) {
            new(data_ + size_) T(std::move(data_[size_ - 1]));
            for (size_type i = size_ - 1; i > idx; --i)
                data_[i] = std::move(data_[i - 1]);
            data_[idx] = val;
        } else {
            new(data_ + idx) T(val);
        }
        ++size_;
        return iterator(data_ + idx);
    }

    /// Inserts @p val (by move) before @p pos.
    iterator insert(const_iterator pos, T&& val) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        if (size_ == capacity_) reallocate(next_cap());
        if (idx < size_) {
            new(data_ + size_) T(std::move(data_[size_ - 1]));
            for (size_type i = size_ - 1; i > idx; --i)
                data_[i] = std::move(data_[i - 1]);
            data_[idx] = std::move(val);
        } else {
            new(data_ + idx) T(std::move(val));
        }
        ++size_;
        return iterator(data_ + idx);
    }

    /// Inserts @p n copies of @p val before @p pos.
    iterator insert(const_iterator pos, size_type n, const T& val) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        return insert_impl(idx, n, [&](Vector& tmp) {
            for (size_type i = 0; i < n; ++i)
                new(tmp.data_ + tmp.size_++) T(val);
        });
    }

    /// Inserts elements from range [@p first, @p last) before @p pos.
    template <typename InputIt,
              typename = typename std::enable_if<
                  !std::is_integral<InputIt>::value>::type>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        Vector vals(first, last);
        size_type n = vals.size_;
        return insert_impl(idx, n, [&](Vector& tmp) {
            for (size_type i = 0; i < n; ++i)
                new(tmp.data_ + tmp.size_++) T(std::move(vals.data_[i]));
        });
    }

    /// Inserts elements from initialiser list before @p pos.
    iterator insert(const_iterator pos, std::initializer_list<T> il) {
        return insert(pos, il.begin(), il.end());
    }

    /// In-place constructs an element before @p pos.
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        T val(std::forward<Args>(args)...);
        return insert(pos, std::move(val));
    }

    // ── erase ─────────────────────────────────────────────────────────────────

    /// Removes the element at @p pos.
    iterator erase(const_iterator pos) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        for (size_type i = idx + 1; i < size_; ++i)
            data_[i - 1] = std::move(data_[i]);
        data_[--size_].~T();
        return iterator(data_ + idx);
    }

    /// Removes elements in [@p first, @p last).
    iterator erase(const_iterator first, const_iterator last) {
        size_type f = static_cast<size_type>(first.base() - data_);
        size_type l = static_cast<size_type>(last.base()  - data_);
        size_type n = l - f;
        if (n == 0) return iterator(data_ + f);
        // Move remaining elements left
        for (size_type i = l; i < size_; ++i)
            data_[i - n] = std::move(data_[i]);
        destroy_range(size_ - n, size_);
        size_ -= n;
        return iterator(data_ + f);
    }
};

// ── Non-member functions ───────────────────────────────────────────────────────

template <typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (typename Vector<T>::size_type i = 0; i < a.size(); ++i)
        if (!(a[i] == b[i])) return false;
    return true;
}

template <typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b) { return !(a == b); }

template <typename T>
bool operator<(const Vector<T>& a, const Vector<T>& b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template <typename T>
bool operator<=(const Vector<T>& a, const Vector<T>& b) { return !(b < a); }

template <typename T>
bool operator>(const Vector<T>& a, const Vector<T>& b) { return b < a; }

template <typename T>
bool operator>=(const Vector<T>& a, const Vector<T>& b) { return !(a < b); }

template <typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept { a.swap(b); }

#endif // VECTOR_H
