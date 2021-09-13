/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:04:16 by kaye              #+#    #+#             */
/*   Updated: 2021/09/13 19:21:56 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <exception>

namespace ft {
	
	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
		/*
		 * member types
		 */
		
			/** @brief the first template parameter (T) */
			typedef 			T								value_type;

			/**
			 * @brief the second template parameter (Alloc)
			 * @note defauls to: allocator<value_type> 
			 */
			typedef 			Alloc							allocator_type;

			/**
			 * @brief allocator_type::reference
			 * @note for the default allocator: value_type&
			 */
			typedef typename	allocator_type::reference		reference;

			/**
			 * @brief allocator_type::const_reference
			 * @note for the default allocator: const value_type&
			 */
			typedef typename	allocator_type::const_reference	const_reference;

			/**
			 * @brief allocator_type::pointer
			 * @note for the default allocator: value_type*
			 */
			typedef typename	allocator_type::pointer			pointer;

			/**
			 * @brief allocator_type::cosnt_pointer
			 * @note for the default allocator: const value_type*
			 */
			typedef typename	allocator_type::const_pointer	const_pointer;

			/**
			 * @brief a signed integral type, identical to: iterator_traits<iterator>::difference_type
			 * @note usually the same as ptrdiff_t
			 */
			typedef typename	allocator_type::difference_type	difference_type;

			/**
			 * @brief an unsigned integral type that can reprensent any non-negative value of difference_type
			 * @note usually the same as size_t
			 */
			typedef typename	allocator_type::size_type		size_type;

			// coming soon ...
			// typedef ? iterator;
			// typedef ? const_iterator;
			// typedef ? reverse_iterator;
			// typedef ? const_reverse_iterator;

		public:
		/*
		 *member functions
		 */
	
		/* constructor / destructor / operator= */

			/**
			 * @brief constructor: default
			 * @note constructs an empty container, with no elements.
			 * @param alloc: allocator object.
			 */
			explicit vector(const allocator_type & alloc = allocator_type()) :
				_alloc(alloc),
				_start(NULL),
				_end(NULL),
				_capacity(NULL) {}

			/**
			 * @brief constructor: fill
			 * @note constructs a container with n elements. Each element is a copy of val.
			 * @param n: initial container size.
			 * @param val: value to fill the container with.
			 * @param alloc: allocator object.
			 */
			explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()) :
				_alloc(alloc),
				_start(NULL),
				_end(NULL),
				_capacity(NULL) {
					_start = _alloc.allocate(n);
					_end = _start;
					_capacity = _start + n;

					for (; n != 0; n--)
						_alloc.construct(_end++, val);
			}

			/**
			 * @brief constructor: range
			 * @note constructs a container with as many elements as the range [first, last], with each element constructed from its corresponding element in that range, in the same order.
			 * @param first: input iterators to the initial positions in a range.
			 * @param last: input iterator to the final positions in a range.
			 * @param alloc: allocator object.
			 */
			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last, const aloocator_type & alloc = allocator_type());

			/**
			 * @brief constructor: copy
			 * @note constructs a container with a copy of each of the elements in x, in the same order.
			 * @param x: another vector object of the same type, whose contents are either copied or acquired.
			 */
			vector(const vector & x) {
				*this = x;
			}
			
			/**
			 * @brief destructor
			 * @note this destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
			 */
			~vector(void) {
				clear();
				_alloc.deallocate(_start, capacity());
			}

			/**
			 * @brief operator: copy
			 * @note copies all the elements from x into the container.
			 * @param x: a vector object of the same type.
			 */
			vector &	operator=(vector const & x) {
				if (this == &x) return *this;

				_alloc.clear();
				_alloc = x._alloc;
				_start = x._start;
				_end = x._end;
				_capacity = x._capacity; // capacity no change when assign
				// need insert
				return *this;
			}

		/* iterators */

			// begin
			// end
			// rbegin
			// rend

		/* capacity */

			/**
			 * @brief returns the number of elements in the vector.
			 * @return the number of elements in the container. 
			 */
			size_type	size(void) const { return _end - _start; }

			/**
			 * @brief return the maximum number of elements that the vector can hold.
			 * @return the maximum number of elements a vector container can hold as content.
			 */
			size_type	max_size(void) const { return allocator_type().max_size(); }

			/**
			 * @brief resizes the container so that it contains n elements
			 * @param n: new container size, expressed in number of elements.
			 * @param val: object whose content is copied to the added elements in case that n is greater than the current container size. If not specified, the default constructor is used instead.
			 */
			void		resize(size_type n, value_type val = value_type()) {
				if (n > max_size())
					throw std::length_error("vector");

				if (n < size()) {
					while (size() > n)
						_alloc.destroy(--_end);
				}
				else {
					
				}
			}

			/**
			 * @brief returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
			 * @return the size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
			 */
			size_type	capacity(void) const { return _capacity - _start; }

			/**
			 * @brief return whether the vector is empty.
			 * @return true if the container size is 0, false otherwise.
			 */
			bool		empty(void) const;

			/**
			 * @brief requests that the vector capacity be at least enough to contain n elements.
			 * @param n: minimum capacity fot the vector.
			 */
			void		reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector");

				if (n > capacity()) {
					pointer oldStart = _start;
					pointer oldEnd = _end;

					_start = _alloc.
				}
			}
			
		/* element access */

			reference			operator[](size_type n);
			const_reference		operator[](size_type n) const;
			reference			at(size_type n);
			const_reference		at(size_type n) const;
			reference			front(void);
			const_reference		front(void) const;
			reference			back(void);
			const_reference		back(void) const;

		/* modifiers */

			/** @brief removes all elements from the vector, leaving the container with a size of 0. */
			void	clear(void) {
				size_type len = size();

				for (size_type i = 0; i < len; i++)
					_alloc.destroy(--_end);
			}
		
		private:
		/**
		 * attributes
		 */

			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_capacity;
	};
}

#endif