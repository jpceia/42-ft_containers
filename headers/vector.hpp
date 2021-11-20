/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:50:27 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/20 03:20:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
    template <class T, class Alloc = std::allocator<T>>
    class vector
    {
        public:
            typedef typename T                                      value_type;
            typedef typename Alloc                                  allocator_type;
            typedef typename allocator_type::reference              reference;
            typedef typename allocator_type::const_reference        const_reference;
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename allocator_type::pointer                iterator;
            typedef typename allocator_type::const_pointer          const_iterator;
            typedef typename allocator_type::pointer                reverse_iterator;
            typedef typename allocator_type::const_pointer          const_reverse_iterator;
            typedef typename allocator_type::difference_type        difference_type;
            typedef typename allocator_type::size_type              size_type;

            // Constructors
            vector() : _begin(nullptr), _end(nullptr), _end_of_storage(nullptr) {}
            vector(size_type n) : _begin(nullptr), _end(nullptr), _end_of_storage(nullptr) { _begin = _end = _end_of_storage = _alloc.allocate(n); }
            
            vector(size_type n, const value_type& value) : _begin(nullptr), _end(nullptr), _end_of_storage(nullptr) { _begin = _end = _end_of_storage = _alloc.allocate(n); std::uninitialized_fill(_begin, _end, value); }	
            vector(const vector& v) : _begin(nullptr), _end(nullptr), _end_of_storage(nullptr) { _begin = _end = _end_of_storage = _alloc.allocate(v.size()); std::uninitialized_copy(v.begin(), v.end(), _begin); }
            vector(vector&& v) : _begin(v._begin), _end(v._end), _end_of_storage(v._end_of_storage) { v._begin = v._end = v._end_of_storage = nullptr; }
            
            // Destructor
            ~vector() { _alloc.deallocate(_begin, _end_of_storage - _begin); }
            
            // Assignment operator overload
            vector& operator=(const vector& v) { if (this != &v) { _alloc.deallocate(_begin, _end_of_storage - _begin); _begin = _end = _end_of_storage = _alloc.allocate(v.size()); std::uninitialized_copy(v.begin(), v.end(), _begin); } return *this; }

            // Iterators
            iterator begin() { return _begin; }
            const_iterator begin() const { return _begin; }

            iterator end() { return _end; }
            const_iterator end() const { return _end; }

            reverse_iterator rbegin() { return reverse_iterator(_end); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(_end); }

            reverse_iterator rend() { return reverse_iterator(_begin); }
            const_reverse_iterator rend() const { return const_reverse_iterator(_begin); }

            // Capacity
            size_type size() const { return _end - _begin; }
            size_type max_size() const { return _alloc.max_size(); }
            
            void resize(size_type n, value_type value = value_type()) { if (n < size()) { _end = _begin + n; } else { _end = _begin + n; std::uninitialized_fill(_end, _end_of_storage, value); } }
            void resize(size_type n) { if (n < size()) { _alloc.destroy(_begin + n, _end); _end = _begin + n; } else if (n > size()) { _reallocate(n); } }
            void resize(size_type n, const value_type& value) { if (n < size()) { _alloc.destroy(_begin + n, _end); _end = _begin + n; } else if (n > size()) { _reallocate(n); std::uninitialized_fill(_end, _end + n - size(), value); _end += n - size(); } }

            size_type capacity() const { return _end_of_storage - _begin; }           
            bool empty() const { return _begin == _end; }

            void reserve(size_type n) { if (n > capacity()) { _reallocate(n); } }

            // Element access
            reference operator[](size_type n) { return *(_begin + n); }
            const_reference operator[](size_type n) const { return *(_begin + n); }
            reference at(size_type n) { if (n >= size()) throw std::out_of_range(""); return *(_begin + n); }
            const_reference at(size_type n) const { if (n >= size()) throw std::out_of_range(""); return *(_begin + n); }

            reference front() { return *_begin; }
            const_reference front() const { return *_begin; }

            reference back() { return *(_end - 1); }
            const_reference back() const { return *(_end - 1); }

            // Modifiers
            void assign(size_type n, const value_type& value) { _alloc.destroy(_begin, _end); _end = _begin; _reallocate(n); std::uninitialized_fill(_begin, _end, value); }
            void assign(const_iterator first, const_iterator last) { _alloc.destroy(_begin, _end); _end = _begin; _reallocate(last - first); std::uninitialized_copy(first, last, _begin); }
            void assign(std::initializer_list<value_type> il) { _alloc.destroy(_begin, _end); _end = _begin; _reallocate(il.size()); std::uninitialized_copy(il.begin(), il.end(), _begin); }

            void push_back(const value_type& value) { if (_end == _end_of_storage) { _reallocate(); } _alloc.construct(_end, value); ++_end; }
            void pop_back() { if (_end != _begin) { --_end; _alloc.destroy(_end); } }
            iterator insert(const_iterator position, const value_type& value) { if (_end == _end_of_storage) { _reallocate(); } std::uninitialized_copy(position, _end, _end + 1); _alloc.construct(_end, value); ++_end; return _end - 1; }
            void insert(const_iterator position, size_type n, const value_type& value) { if (_end + n > _end_of_storage) { _reallocate(n); } std::uninitialized_copy(position, _end, _end + n); std::uninitialized_fill(_end, _end + n, value); _end += n; }
            template <class InputIterator> void insert(const_iterator position, InputIterator first, InputIterator last) { if (_end + (last - first) > _end_of_storage) { _reallocate(last - first); } std::uninitialized_copy(position, _end, _end + (last - first)); std::uninitialized_copy(first, last, _end); _end += (last - first); }
            
            iterator erase(const_iterator position) { std::copy(position + 1, _end, position); _alloc.destroy(_end - 1); --_end; return position; }
            iterator erase(const_iterator first, const_iterator last) { std::copy(last, _end, first); _alloc.destroy(_end - (last - first)); _end -= (last - first); return first; }
            
            void swap(vector& v) { std::swap(_begin, v._begin); std::swap(_end, v._end); std::swap(_end_of_storage, v._end_of_storage); }
            
            void clear() { _alloc.destroy(_begin, _end); _end = _begin; }
            
        private:
            iterator _begin;
            iterator _end;
            iterator _end_of_storage;
            allocator_type _alloc;

            void _reallocate(size_type n = 0) {
                size_type new_size = (n == 0) ? size() * 2 : n;
                iterator new_begin = _alloc.allocate(new_size);
                std::uninitialized_copy(_begin, _end, new_begin);
                _alloc.deallocate(_begin, _end_of_storage - _begin);
                _begin = new_begin;
                _end = _begin + size();
                _end_of_storage = _begin + new_size;
            }

            void shrink_to_fit() { _reallocate(size()); }
            
        };
    }
} // namespace ft

#endif
