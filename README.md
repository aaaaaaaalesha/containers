# Containers

## Unordered Map (Hashmap)

![hashmap_img](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Hash_table_5_0_1_1_1_1_1_LL.svg/1920px-Hash_table_5_0_1_1_1_1_1_LL.svg.png)

### Сигнатура класса `UnorderedMap`:

```c++
template <class Key, class T, class Hash = std::hash<Key>, class EqualKey = std::equal_to<Key>>
class UnorderedMap {
public:
using iterator = Iterator<Key, T>;

UnorderedMap();

UnorderedMap(
std::initializer_list<ValueType> iList,
SizeType bucketCount = um_details::defaultBucketCount,
const Hash &hash = Hash(),
const EqualKey &equal = EqualKey()
);

UnorderedMap(
const std::vector<ValueType> &vec,
SizeType bucketCount = um_details::defaultBucketCount,
const Hash &hash = Hash(),
const EqualKey &equal = EqualKey()
);

UnorderedMap(const UnorderedMap &oth);

UnorderedMap(UnorderedMap &&oth) noexcept;

UnorderedMap &operator=(const UnorderedMap &rhs) = default;

UnorderedMap &operator=(UnorderedMap &&rhs) noexcept;

SizeType size() const;

SizeType bucketCount() const;

LocalIterator begin(SizeType n);

ConstLocalIterator begin(SizeType n) const;

LocalIterator end(SizeType n);

ConstLocalIterator end(SizeType n) const;

iterator begin() const;

iterator end() const;

bool empty();

T &operator[](const Key &key);

T &at(const Key &key);

std::pair<iterator, bool> insert(const ValueType &value);

SizeType erase(const Key &key);

void swap(UnorderedMap &oth);

void clear() noexcept;

iterator find(const Key &key);

void rehash(SizeType n);

float loadFactor() const noexcept;

float maxLoadFactor() const noexcept;
};
```

### Сигнатура класса `Iterator`:

```c++
template <class KeyIt, class TIt>
class Iterator:
public std::iterator<std::forward_iterator_tag, std::pair<KeyIt, TIt>> {
public:
Iterator();

Iterator(const Iterator &it) = default;

Iterator(const Table *table, size_t bucketIndex, LocalIterator localIterator);

Iterator &operator=(const Iterator rhs);

// Preincrement.
Iterator &operator++();

// Post-increment.
Iterator operator++(int);

ValueType operator*() const;

ValueType &operator*();

const ValueType *operator->() const;

ValueType *operator->();

bool operator==(const Iterator rhs);

bool operator!=(const Iterator rhs) const;
};
```

### Структура узлов в списке `Node`:

```c++
struct Node {
using Bucket = Array<T>;

// Count of elements in node.
size_t size_ = 0u;
// Block of elements.
Bucket bucket_ = Bucket(BucketCapacity);
// Pointer to the next node in list.
Node* next_ = nullptr;
};
```

### Сигнатура класса `Array`:

```c++
template <class T>
class Array {
public:
Array();

~Array();

Array(size_t size, const T &value);

Array(const Array &oth);

Array &operator=(const Array &rhs);

T &operator[](size_t index) const;

T &operator[](size_t index);

const T *data() const;

T *data() noexcept;

size_t size() const noexcept;
};
```

## Unrolled Linked List

![unrolled_linked_list](https://upload.wikimedia.org/wikipedia/commons/1/16/Unrolled_linked_lists_%281-8%29.PNG)

### Сигнатура класса `unrolled_linked_list`:

```c++
template <class T, size_t BucketCapacity>
class unrolled_linked_list {
private:
using ValueType = T;
using SizeType = size_t;

using iterator = Iterator<ValueType, BucketCapacity>;
using const_iterator = const iterator;
using reference = ValueType&;
using const_reference = const ValueType&;

Node<ValueType, BucketCapacity>* head_ = nullptr;

friend std::ostream& operator <<<T, BucketCapacity>(
std::ostream& out, const unrolled_linked_list& ull);

public:
/// Default constructor.
unrolled_linked_list() = default;

/// Destructor.
~unrolled_linked_list();

/// Copy constructor.
unrolled_linked_list(const unrolled_linked_list& oth);

/// Move constructor.
unrolled_linked_list(unrolled_linked_list&& oth) noexcept;

/// std::initializer_list constructor.
unrolled_linked_list(std::initializer_list<ValueType> init_list);

/// Copy assignment operator.
unrolled_linked_list& operator=(const unrolled_linked_list& oth);

/// Move assignment operator.
unrolled_linked_list& operator=(unrolled_linked_list&& oth) noexcept;

const_reference operator[](size_t pos) const;

reference operator[](size_t pos);

const_reference at(size_t pos) const;

reference at(size_t pos);

iterator begin();

const_iterator begin() const;

iterator end();

const_iterator end() const;

SizeType size() const;

void swap(unrolled_linked_list& oth);

void clear();

SizeType bucket_capacity() const;

SizeType empty() const;

const_reference front() const;

reference front();

const_reference back() const;

reference back();

void push_back(const T& value);

T pop_back();

iterator insert(const_iterator pos, const ValueType& value);

iterator erase(const_iterator pos);
};
```

### Сигнатура класса `Iterator`:

```c++
template <class T, size_t BucketCapacity = unrolled_details::default_capacity>
class Iterator :
public std::iterator<std::forward_iterator_tag, T> {
private:
using ValueType = T;

ValueType* ptr_ = nullptr;
size_t index_ = 0u;

Node<T, BucketCapacity>* node_ptr_ = nullptr;

friend class unrolled_linked_list<ValueType, BucketCapacity>;

public:
Iterator() = default;

Iterator(const Iterator<ValueType, BucketCapacity>& it) = default;

Iterator(T* ptr, size_t index, Node<T, BucketCapacity>* node_ptr);

Iterator& operator=(const Iterator oth);

Iterator& operator++();

Iterator operator++(int);

ValueType operator*() const;

ValueType& operator*();

const ValueType* operator->() const;

ValueType* operator->();

bool operator==(const Iterator rhs) const;

bool operator!=(const Iterator rhs) const;
};
```

### Структура узлов в списке `Node`:

```c++
struct Node {
using Bucket = Array<T>;

// Count of elements in node.
size_t size_ = 0u;
// Block of elements.
Bucket bucket_ = Bucket(BucketCapacity);
// Pointer to the next node in list.
Node* next_ = nullptr;
};
```

### Сигнатура класса `Array`:

```c++
class Array {
private:
size_t size_;
size_t capacity_;
T *arr_;

public:
Array();

~Array();

explicit Array(size_t capacity);

Array(size_t size, const T &value);

Array(const Array &oth);

Array &operator=(const Array &rhs);

const T &operator[](size_t index) const;

T &operator[](size_t index);

const T *data() const;

T *data() noexcept;

void push_back(const T &value);

T pop_back();

void resize(size_t size);

size_t size() const noexcept;

void clear();

bool empty() const;
};
```

### Used sources:

1. [Microsoft Docs](https://blogs.msdn.microsoft.com/devdev/2005/08/22/unrolled-linked-lists/)
2. [Wikipedia](https://en.wikipedia.org/wiki/Unrolled_linked_list)

```shell
Copyright 2021 aaaaaaaalesha
```