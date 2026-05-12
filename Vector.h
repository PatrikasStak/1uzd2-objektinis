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
 * @author Patrikas
 */

/**
 * @class Vector
 * @brief Dynamic array template container mimicking std::vector.
 *
 * Manages a heap-allocated contiguous buffer using @c operator @c new and
 * placement-new so that elements are only constructed when they are actually
 * inserted — exactly like the standard library implementation.  The buffer
 * doubles in size on each reallocation, giving amortised O(1) push_back.
 *
 * Satisfies the *SequenceContainer* and *ReversibleContainer* named
 * requirements and provides a random-access iterator pair that models
 * *LegacyRandomAccessIterator*.
 *
 * @tparam T Element type.  Must be *MoveInsertable* into the container.
 */
template <typename T>
class Vector {
public:
    // ── Member types ──────────────────────────────────────────────────────────
    using value_type             = T;             ///< Element type.
    using size_type              = std::size_t;   ///< Unsigned size/index type.
    using difference_type        = std::ptrdiff_t;///< Signed difference type.
    using reference              = T&;            ///< Mutable element reference.
    using const_reference        = const T&;      ///< Immutable element reference.
    using pointer                = T*;            ///< Pointer to element.
    using const_pointer          = const T*;      ///< Pointer to const element.

    // ── iterator ──────────────────────────────────────────────────────────────
    /**
     * @class iterator
     * @brief Mutable random-access iterator over Vector elements.
     *
     * Models *LegacyRandomAccessIterator*.  Wraps a raw pointer so all
     * arithmetic operations are O(1).
     */
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        /// Constructs a singular (null) iterator.
        iterator() noexcept : ptr_(nullptr) {}
        /// Constructs an iterator pointing to @p p.
        explicit iterator(T* p) noexcept : ptr_(p) {}

        reference operator*()  const noexcept { return *ptr_; }   ///< Dereference.
        pointer   operator->() const noexcept { return ptr_; }    ///< Member access.
        /// Subscript — equivalent to `*(it + n)`.
        reference operator[](difference_type n) const noexcept { return ptr_[n]; }

        iterator& operator++()    noexcept { ++ptr_; return *this; } ///< Pre-increment.
        iterator  operator++(int) noexcept { iterator t(*this); ++ptr_; return t; } ///< Post-increment.
        iterator& operator--()    noexcept { --ptr_; return *this; } ///< Pre-decrement.
        iterator  operator--(int) noexcept { iterator t(*this); --ptr_; return t; } ///< Post-decrement.

        iterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; } ///< Advance by @p n.
        iterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; } ///< Retreat by @p n.
        iterator  operator+(difference_type n) const noexcept { return iterator(ptr_ + n); } ///< Returns advanced copy.
        iterator  operator-(difference_type n) const noexcept { return iterator(ptr_ - n); } ///< Returns retreated copy.
        /// Distance between two iterators.
        difference_type operator-(const iterator& o) const noexcept { return ptr_ - o.ptr_; }

        /// Supports `n + it` syntax.
        friend iterator operator+(difference_type n, const iterator& it) noexcept {
            return iterator(it.ptr_ + n);
        }

        bool operator==(const iterator& o) const noexcept { return ptr_ == o.ptr_; } ///< Equality.
        bool operator!=(const iterator& o) const noexcept { return ptr_ != o.ptr_; } ///< Inequality.
        bool operator< (const iterator& o) const noexcept { return ptr_ <  o.ptr_; } ///< Less-than.
        bool operator<=(const iterator& o) const noexcept { return ptr_ <= o.ptr_; } ///< Less-or-equal.
        bool operator> (const iterator& o) const noexcept { return ptr_ >  o.ptr_; } ///< Greater-than.
        bool operator>=(const iterator& o) const noexcept { return ptr_ >= o.ptr_; } ///< Greater-or-equal.

        /// Returns the underlying raw pointer.
        T* base() const noexcept { return ptr_; }
    private:
        T* ptr_;
    };

    // ── const_iterator ────────────────────────────────────────────────────────
    /**
     * @class const_iterator
     * @brief Read-only random-access iterator over Vector elements.
     *
     * Implicitly constructible from @c iterator, allowing mutable iterators
     * to be passed where a const one is expected.
     */
    class const_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        /// Constructs a singular (null) const_iterator.
        const_iterator() noexcept : ptr_(nullptr) {}
        /// Constructs a const_iterator pointing to @p p.
        explicit const_iterator(const T* p) noexcept : ptr_(p) {}
        /// Implicit conversion from mutable iterator.
        const_iterator(const iterator& it) noexcept : ptr_(it.base()) {}

        reference operator*()  const noexcept { return *ptr_; }  ///< Dereference.
        pointer   operator->() const noexcept { return ptr_; }   ///< Member access.
        /// Subscript — equivalent to `*(it + n)`.
        reference operator[](difference_type n) const noexcept { return ptr_[n]; }

        const_iterator& operator++()    noexcept { ++ptr_; return *this; } ///< Pre-increment.
        const_iterator  operator++(int) noexcept { const_iterator t(*this); ++ptr_; return t; } ///< Post-increment.
        const_iterator& operator--()    noexcept { --ptr_; return *this; } ///< Pre-decrement.
        const_iterator  operator--(int) noexcept { const_iterator t(*this); --ptr_; return t; } ///< Post-decrement.

        const_iterator& operator+=(difference_type n) noexcept { ptr_ += n; return *this; } ///< Advance by @p n.
        const_iterator& operator-=(difference_type n) noexcept { ptr_ -= n; return *this; } ///< Retreat by @p n.
        const_iterator  operator+(difference_type n) const noexcept { return const_iterator(ptr_ + n); } ///< Returns advanced copy.
        const_iterator  operator-(difference_type n) const noexcept { return const_iterator(ptr_ - n); } ///< Returns retreated copy.
        /// Distance between two const_iterators.
        difference_type operator-(const const_iterator& o) const noexcept { return ptr_ - o.ptr_; }

        /// Supports `n + it` syntax.
        friend const_iterator operator+(difference_type n, const const_iterator& it) noexcept {
            return const_iterator(it.ptr_ + n);
        }

        bool operator==(const const_iterator& o) const noexcept { return ptr_ == o.ptr_; } ///< Equality.
        bool operator!=(const const_iterator& o) const noexcept { return ptr_ != o.ptr_; } ///< Inequality.
        bool operator< (const const_iterator& o) const noexcept { return ptr_ <  o.ptr_; } ///< Less-than.
        bool operator<=(const const_iterator& o) const noexcept { return ptr_ <= o.ptr_; } ///< Less-or-equal.
        bool operator> (const const_iterator& o) const noexcept { return ptr_ >  o.ptr_; } ///< Greater-than.
        bool operator>=(const const_iterator& o) const noexcept { return ptr_ >= o.ptr_; } ///< Greater-or-equal.

        /// Returns the underlying raw pointer.
        const T* base() const noexcept { return ptr_; }
    private:
        const T* ptr_;
    };

    using reverse_iterator       = std::reverse_iterator<iterator>;       ///< Reverse mutable iterator.
    using const_reverse_iterator = std::reverse_iterator<const_iterator>; ///< Reverse read-only iterator.

    // ── Private helpers ───────────────────────────────────────────────────────
private:
    T*        data_;      ///< Pointer to raw storage.
    size_type size_;      ///< Number of live elements.
    size_type capacity_;  ///< Allocated slots.

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

    template <typename F>
    iterator insert_impl(size_type idx, size_type n, F&& fill) {
        if (n == 0) return iterator(data_ + idx);
        Vector tmp;
        tmp.data_     = mem_alloc(size_ + n);
        tmp.capacity_ = size_ + n;
        for (size_type i = 0; i < idx; ++i)
            new(tmp.data_ + tmp.size_++) T(std::move(data_[i]));
        fill(tmp);
        for (size_type i = idx; i < size_; ++i)
            new(tmp.data_ + tmp.size_++) T(std::move(data_[i]));
        swap(tmp);
        return iterator(data_ + idx);
    }

public:
    // ── Constructors ──────────────────────────────────────────────────────────

    /**
     * @brief Default constructor.
     *
     * Creates an empty vector with no heap allocation.
     */
    Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief Value-initialisation constructor.
     * @param n Number of elements to create.
     *
     * Each element is value-initialised (zero for scalar types).
     */
    explicit Vector(size_type n) : data_(nullptr), size_(0), capacity_(0) {
        if (n == 0) return;
        data_     = mem_alloc(n);
        capacity_ = n;
        for (; size_ < n; ++size_)
            new(data_ + size_) T();
    }

    /**
     * @brief Fill constructor.
     * @param n   Number of elements.
     * @param val Value to copy into every element.
     */
    Vector(size_type n, const T& val) : data_(nullptr), size_(0), capacity_(0) {
        if (n == 0) return;
        data_     = mem_alloc(n);
        capacity_ = n;
        for (; size_ < n; ++size_)
            new(data_ + size_) T(val);
    }

    /**
     * @brief Range constructor.
     * @tparam InputIt Iterator type (must not be integral).
     * @param first Iterator to the first element of the source range.
     * @param last  Past-the-end iterator of the source range.
     *
     * Copies all elements from [@p first, @p last) into the new vector.
     */
    template <typename InputIt,
              typename = typename std::enable_if<
                  !std::is_integral<InputIt>::value>::type>
    Vector(InputIt first, InputIt last) : data_(nullptr), size_(0), capacity_(0) {
        for (auto it = first; it != last; ++it)
            push_back(*it);
    }

    /**
     * @brief Initialiser-list constructor.
     * @param il Brace-enclosed element list.
     */
    Vector(std::initializer_list<T> il) : data_(nullptr), size_(0), capacity_(0) {
        reserve(il.size());
        for (const auto& v : il)
            new(data_ + size_++) T(v);
    }

    /**
     * @brief Copy constructor.
     * @param o Source vector.  @p o is unchanged.
     */
    Vector(const Vector& o) : data_(nullptr), size_(0), capacity_(0) {
        if (o.size_ == 0) return;
        data_     = mem_alloc(o.size_);
        capacity_ = o.size_;
        for (; size_ < o.size_; ++size_)
            new(data_ + size_) T(o.data_[size_]);
    }

    /**
     * @brief Move constructor.
     * @param o Source vector.  Left in a valid empty state after the move.
     */
    Vector(Vector&& o) noexcept
        : data_(o.data_), size_(o.size_), capacity_(o.capacity_) {
        o.data_ = nullptr; o.size_ = 0; o.capacity_ = 0;
    }

    /**
     * @brief Destructor.
     *
     * Destroys all live elements and releases heap memory.
     */
    ~Vector() {
        destroy_range(0, size_);
        mem_free(data_);
    }

    // ── Assignment ────────────────────────────────────────────────────────────

    /**
     * @brief Copy assignment.
     * @param o Source vector.
     * @return Reference to @c *this.
     *
     * Implemented via copy-and-swap to provide strong exception safety.
     */
    Vector& operator=(const Vector& o) {
        if (this != &o) { Vector tmp(o); swap(tmp); }
        return *this;
    }

    /**
     * @brief Move assignment.
     * @param o Source vector.  Left empty after the move.
     * @return Reference to @c *this.
     */
    Vector& operator=(Vector&& o) noexcept {
        if (this != &o) {
            destroy_range(0, size_);
            mem_free(data_);
            data_ = o.data_; size_ = o.size_; capacity_ = o.capacity_;
            o.data_ = nullptr; o.size_ = 0; o.capacity_ = 0;
        }
        return *this;
    }

    /**
     * @brief Initialiser-list assignment.
     * @param il New element list.
     * @return Reference to @c *this.
     */
    Vector& operator=(std::initializer_list<T> il) {
        assign(il); return *this;
    }

    /**
     * @brief Replaces contents with @p n copies of @p val.
     * @param n   New element count.
     * @param val Value to fill with.
     */
    void assign(size_type n, const T& val) {
        clear();
        reserve(n);
        for (size_type i = 0; i < n; ++i)
            new(data_ + size_++) T(val);
    }

    /**
     * @brief Replaces contents with the range [@p first, @p last).
     * @tparam InputIt Iterator type.
     * @param first Beginning of source range.
     * @param last  End of source range.
     */
    template <typename InputIt,
              typename = typename std::enable_if<
                  !std::is_integral<InputIt>::value>::type>
    void assign(InputIt first, InputIt last) {
        clear();
        for (auto it = first; it != last; ++it)
            push_back(*it);
    }

    /**
     * @brief Replaces contents with an initialiser list.
     * @param il New element list.
     */
    void assign(std::initializer_list<T> il) {
        clear();
        reserve(il.size());
        for (const auto& v : il)
            new(data_ + size_++) T(v);
    }

    // ── Element access ────────────────────────────────────────────────────────

    /**
     * @brief Bounds-checked element access.
     * @param pos Zero-based index.
     * @return Mutable reference to the element.
     * @throws std::out_of_range if @p pos >= size().
     */
    reference at(size_type pos) {
        if (pos >= size_) throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    /**
     * @brief Bounds-checked element access (const overload).
     * @param pos Zero-based index.
     * @return Immutable reference to the element.
     * @throws std::out_of_range if @p pos >= size().
     */
    const_reference at(size_type pos) const {
        if (pos >= size_) throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    /**
     * @brief Unchecked element access.
     * @param pos Zero-based index.  Behaviour is undefined if out of range.
     * @return Mutable reference to the element.
     */
    reference       operator[](size_type pos)       noexcept { return data_[pos]; }

    /**
     * @brief Unchecked element access (const overload).
     * @param pos Zero-based index.
     * @return Immutable reference to the element.
     */
    const_reference operator[](size_type pos) const noexcept { return data_[pos]; }

    /**
     * @brief Access the first element.
     * @return Mutable reference.  Undefined if empty.
     */
    reference       front()       noexcept { return data_[0]; }
    /** @brief Access the first element (const overload). */
    const_reference front() const noexcept { return data_[0]; }

    /**
     * @brief Access the last element.
     * @return Mutable reference.  Undefined if empty.
     */
    reference       back()        noexcept { return data_[size_ - 1]; }
    /** @brief Access the last element (const overload). */
    const_reference back()  const noexcept { return data_[size_ - 1]; }

    /**
     * @brief Direct access to the underlying contiguous storage.
     * @return Pointer to the first element, or @c nullptr if empty.
     */
    T*       data()       noexcept { return data_; }
    /** @brief Direct access to the underlying storage (const overload). */
    const T* data() const noexcept { return data_; }

    // ── Iterators ─────────────────────────────────────────────────────────────

    iterator       begin()        noexcept { return iterator(data_); }             ///< Iterator to first element.
    iterator       end()          noexcept { return iterator(data_ + size_); }     ///< Past-the-end iterator.
    const_iterator begin()  const noexcept { return const_iterator(data_); }       ///< Const iterator to first element.
    const_iterator end()    const noexcept { return const_iterator(data_ + size_); }///< Const past-the-end iterator.
    const_iterator cbegin() const noexcept { return const_iterator(data_); }       ///< Explicit const iterator to first element.
    const_iterator cend()   const noexcept { return const_iterator(data_ + size_); }///< Explicit const past-the-end iterator.

    reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }             ///< Reverse iterator to last element.
    reverse_iterator       rend()          noexcept { return reverse_iterator(begin()); }           ///< Reverse past-the-end iterator.
    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }      ///< Const reverse iterator to last element.
    const_reverse_iterator rend()    const noexcept { return const_reverse_iterator(begin()); }    ///< Const reverse past-the-end iterator.
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }     ///< Explicit const reverse iterator.
    const_reverse_iterator crend()   const noexcept { return const_reverse_iterator(cbegin()); }   ///< Explicit const reverse past-the-end.

    // ── Capacity ──────────────────────────────────────────────────────────────

    /// @brief Returns @c true if the vector contains no elements.
    bool      empty()    const noexcept { return size_ == 0; }

    /// @brief Returns the number of live elements.
    size_type size()     const noexcept { return size_; }

    /// @brief Returns the theoretical maximum number of elements.
    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    /// @brief Returns the number of elements that fit in the current allocation.
    size_type capacity() const noexcept { return capacity_; }

    /**
     * @brief Ensures capacity is at least @p new_cap.
     * @param new_cap Minimum required capacity.
     *
     * No-op if current capacity already satisfies the requirement.
     * Invalidates iterators if a reallocation occurs.
     */
    void reserve(size_type new_cap) {
        if (new_cap > capacity_) reallocate(new_cap);
    }

    /**
     * @brief Requests that capacity be reduced to match size.
     *
     * This is a non-binding hint per the standard; this implementation
     * always honours it.  Frees the buffer entirely when empty.
     */
    void shrink_to_fit() {
        if (size_ == capacity_) return;
        if (size_ == 0) {
            mem_free(data_); data_ = nullptr; capacity_ = 0; return;
        }
        reallocate(size_);
    }

    // ── Modifiers ─────────────────────────────────────────────────────────────

    /**
     * @brief Destroys all elements.
     *
     * Sets size to zero; capacity and the allocated buffer are retained.
     */
    void clear() noexcept {
        destroy_range(0, size_);
        size_ = 0;
    }

    /**
     * @brief Appends a copy of @p val to the end.
     * @param val Value to copy.
     *
     * Reallocates (doubling capacity) if the buffer is full.
     */
    void push_back(const T& val) {
        if (size_ == capacity_) reallocate(next_cap());
        new(data_ + size_++) T(val);
    }

    /**
     * @brief Appends @p val to the end by move.
     * @param val Value to move from.
     */
    void push_back(T&& val) {
        if (size_ == capacity_) reallocate(next_cap());
        new(data_ + size_++) T(std::move(val));
    }

    /**
     * @brief Constructs an element in-place at the end.
     * @tparam Args Constructor argument types.
     * @param args Arguments forwarded to T's constructor.
     * @return Reference to the newly constructed element.
     */
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (size_ == capacity_) reallocate(next_cap());
        new(data_ + size_) T(std::forward<Args>(args)...);
        return data_[size_++];
    }

    /**
     * @brief Removes the last element.
     *
     * Undefined behaviour if the vector is empty.
     */
    void pop_back() noexcept { data_[--size_].~T(); }

    /**
     * @brief Resizes the vector to @p n elements.
     * @param n Target size.
     *
     * If @p n < size(), the excess elements are destroyed.
     * If @p n > size(), new elements are value-initialised.
     */
    void resize(size_type n) {
        if (n < size_) { destroy_range(n, size_); size_ = n; }
        else if (n > size_) {
            if (n > capacity_) reallocate(n);
            for (; size_ < n; ++size_) new(data_ + size_) T();
        }
    }

    /**
     * @brief Resizes the vector to @p n elements, filling new slots with @p val.
     * @param n   Target size.
     * @param val Value assigned to any new elements.
     */
    void resize(size_type n, const T& val) {
        if (n < size_) { destroy_range(n, size_); size_ = n; }
        else if (n > size_) {
            if (n > capacity_) reallocate(n);
            for (; size_ < n; ++size_) new(data_ + size_) T(val);
        }
    }

    /**
     * @brief Exchanges contents with @p o in O(1).
     * @param o Vector to swap with.
     *
     * Iterators remain valid but now refer to the other container.
     */
    void swap(Vector& o) noexcept {
        std::swap(data_,     o.data_);
        std::swap(size_,     o.size_);
        std::swap(capacity_, o.capacity_);
    }

    // ── insert ────────────────────────────────────────────────────────────────

    /**
     * @brief Inserts a copy of @p val before @p pos.
     * @param pos Iterator before which to insert.
     * @param val Value to insert.
     * @return Iterator to the inserted element.
     */
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

    /**
     * @brief Inserts @p val (by move) before @p pos.
     * @param pos Iterator before which to insert.
     * @param val Value to move from.
     * @return Iterator to the inserted element.
     */
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

    /**
     * @brief Inserts @p n copies of @p val before @p pos.
     * @param pos Iterator before which to insert.
     * @param n   Number of copies.
     * @param val Value to copy.
     * @return Iterator to the first inserted element, or @p pos if n == 0.
     */
    iterator insert(const_iterator pos, size_type n, const T& val) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        return insert_impl(idx, n, [&](Vector& tmp) {
            for (size_type i = 0; i < n; ++i)
                new(tmp.data_ + tmp.size_++) T(val);
        });
    }

    /**
     * @brief Inserts elements from range [@p first, @p last) before @p pos.
     * @tparam InputIt Source iterator type.
     * @param pos   Iterator before which to insert.
     * @param first Beginning of the source range.
     * @param last  End of the source range.
     * @return Iterator to the first inserted element.
     */
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

    /**
     * @brief Inserts elements from an initialiser list before @p pos.
     * @param pos Iterator before which to insert.
     * @param il  Elements to insert.
     * @return Iterator to the first inserted element.
     */
    iterator insert(const_iterator pos, std::initializer_list<T> il) {
        return insert(pos, il.begin(), il.end());
    }

    /**
     * @brief Constructs an element in-place before @p pos.
     * @tparam Args Constructor argument types.
     * @param pos  Iterator before which to emplace.
     * @param args Arguments forwarded to T's constructor.
     * @return Iterator to the emplaced element.
     */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        T val(std::forward<Args>(args)...);
        return insert(pos, std::move(val));
    }

    // ── erase ─────────────────────────────────────────────────────────────────

    /**
     * @brief Removes the element at @p pos.
     * @param pos Iterator to the element to remove.
     * @return Iterator to the element that followed @p pos, or end().
     */
    iterator erase(const_iterator pos) {
        size_type idx = static_cast<size_type>(pos.base() - data_);
        for (size_type i = idx + 1; i < size_; ++i)
            data_[i - 1] = std::move(data_[i]);
        data_[--size_].~T();
        return iterator(data_ + idx);
    }

    /**
     * @brief Removes elements in the range [@p first, @p last).
     * @param first Iterator to the first element to remove.
     * @param last  Past-the-end iterator of the range to remove.
     * @return Iterator to the element that followed the last removed element.
     */
    iterator erase(const_iterator first, const_iterator last) {
        size_type f = static_cast<size_type>(first.base() - data_);
        size_type l = static_cast<size_type>(last.base()  - data_);
        size_type n = l - f;
        if (n == 0) return iterator(data_ + f);
        for (size_type i = l; i < size_; ++i)
            data_[i - n] = std::move(data_[i]);
        destroy_range(size_ - n, size_);
        size_ -= n;
        return iterator(data_ + f);
    }
};

// ── Non-member functions ───────────────────────────────────────────────────────

/**
 * @relates Vector
 * @brief Lexicographic equality comparison.
 * @return @c true if both vectors have the same size and all elements compare equal.
 */
template <typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (typename Vector<T>::size_type i = 0; i < a.size(); ++i)
        if (!(a[i] == b[i])) return false;
    return true;
}

/** @relates Vector @brief Inequality — negation of operator==. */
template <typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b) { return !(a == b); }

/**
 * @relates Vector
 * @brief Lexicographic less-than comparison.
 */
template <typename T>
bool operator<(const Vector<T>& a, const Vector<T>& b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

/** @relates Vector @brief Lexicographic less-than-or-equal. */
template <typename T>
bool operator<=(const Vector<T>& a, const Vector<T>& b) { return !(b < a); }

/** @relates Vector @brief Lexicographic greater-than. */
template <typename T>
bool operator>(const Vector<T>& a, const Vector<T>& b) { return b < a; }

/** @relates Vector @brief Lexicographic greater-than-or-equal. */
template <typename T>
bool operator>=(const Vector<T>& a, const Vector<T>& b) { return !(a < b); }

/**
 * @relates Vector
 * @brief Specialisation of std::swap for Vector — calls a.swap(b).
 */
template <typename T>
void swap(Vector<T>& a, Vector<T>& b) noexcept { a.swap(b); }

#endif // VECTOR_H
