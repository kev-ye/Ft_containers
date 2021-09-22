/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:04:12 by kaye              #+#    #+#             */
/*   Updated: 2021/09/22 15:47:43 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {
/**
 * @class template: stack
 */

	/**
	 * @brief stack
	 * @note stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out),
	 * where elements are inserted and extracted only from one end of the containers.
	 * 
	 * @param T: type of the elements.
	 * @param Container: type of the internal underlying container object where the elements are stored.
	 */
	template < class T, class Container = ft::vector<T> >
	class stack {
		public:
		/* member types */

			/** @note type of the elements */
			typedef T				value_type;
			/** @note type of the underlying container */
			typedef Container		container_type;
			/** @note usually the same as size_t */
			typedef size_t			size_type;

		public:
		/* member functions: constructor / destructor */

			/**
			 * @brief constructor
			 * @note constructs a stack container adaptor object.
			 * 
			 * @param ctnr: container object.
			 * @param alloc: allocator object.
			 * @param x: A stack of the ame type.
			 */
			explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}

			/**
			 * @brief destructor
			 */
			~stack(void) {}

		/* member functions: capacity */

			/**
			 * @brief test whether container is empty
			 * @note returns whether the stack is empty: whether its size is zero.
			 * 
			 * @return true if the underlying container's size if 0, false otherwise.
			 */
			bool empty(void) const { return _c.empty(); }

			/**
			 * @brief return size
			 * @note returns the number of elements in the stack.
			 * 
			 * @return the number of elements in the underlying container.
			 */
			size_type size(void) const { return _c.size(); }

		/* member functions: element access */

			/**
			 * @brief access next element
			 * @note returns a reference to the top element in the stack.
			 * 
			 * @return a reference to the top element in the stack.
			 */
			value_type& top(void) { return _c.back(); }
			const value_type& top(void) const { return _c.back(); }

		/* member functions: modifiers */

			/**
			 * @brief insert element
			 * @note inserts a new element at the top of the stack, above its current top element.
			 * the content of this element is initialized to a copy of val.
			 * 
			 * @param val: value to which the inserted element is initialized.
			 */
			void push (const value_type& val) { _c.push_back(val); }

			/**
			 * @brief remove top element
			 * @note removes the element on top of the stack, effectively reducing its size by one.
			 */
			void pop(void) { _c.pop_back(); }

		/* non-member function: stack */

			/**
			 * @brief relational operators for stack
			 * @note Performs the appropriate comparison operation between lhs and rhs.
			 * Each of these operator overloads calls the same operator on the underlying container objects.
			 * 
			 * @param lhs, rhs: stack objects.
			 * @return true, if the condition holds, and false otherwise.
			 */
			template < class _T, class _Container >
			friend bool operator== (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) { return lhs._c == rhs._c; }

			template < class _T, class _Container >
			friend bool operator!= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) { return lhs._c != rhs._c; }

			template < class _T, class _Container >
			friend bool operator<  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) { return lhs._c < rhs._c; }

			template < class _T, class _Container >
			friend bool operator<= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) { return lhs._c <= rhs._c; }

			template < class _T, class _Container >
			friend bool operator>  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) { return lhs._c > rhs._c; }
			
			template < class _T, class _Container >
			friend bool operator>= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) { return lhs._c >= rhs._c; }

		protected:
		/* attributes */

			container_type _c;
	};
}

#endif