/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:13:21 by kaye              #+#    #+#             */
/*   Updated: 2021/09/16 20:10:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {

	/* iterator */

	/**
	 * @class template: iterator
	 * @brief iterator base class.
	 * @param Category: category to which the iterator belons to. It must be one of the followng iterator tags:
	 * intput_iterator_tag:	input iterator
	 * output_iterator_tag: output iterator
	 * forward_iterator_tag: forward iterator
	 * bidirectional_iterator_tag: bidirectional iterator
	 * random_access_iterator_tage: random-access iterator
	 * @param T: type of elements pointer by the iterator.
	 * @param Distance: type to represent the difference between two iterators.
	 * @param Pointer: type to represent a pointer to an element pointed by the iterator.
	 * @param Reference: type to represent a reference to an element pointed by the iterator.
	 */
	template < class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator {
		/*
		 * member types
		 */

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/* category tags */

	/** 
	 * @brief input iterator category
	 * @note empty class to identify the category of an iterator as an input iterator.
	 */
	struct input_iterator_tag {};
	
	/** 
	 * @brief output iterator category
	 * @note empty class to identify the category of an iterator as an output iterator.
	 */
	struct output_iterator_tag {};

	/** 
	 * @brief forward iterator category
	 * @note empty class to identify the category of an iterator as a forward iterator.
	 */
	struct forward_iterator_tag : public input_iterator_tag {};

	/** 
	 * @brief bidirectional iterator category
	 * @note empty class to identify the category of an iterator as a bidirectional iterator.
	 */
	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	/** 
	 * @brief random-access iterator category
	 * @note empty class to identify the category of an iterator as a random-access iterator:.
	 */
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* iterator traits */

	/** 
	 * @class template: iterator_traits
	 * @brief Traits class defining properties of iterators.
	 */
	template < class Iterator >
	struct iterator_traits {
		/*
		 * member types
		 */

		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template < class T >
	struct iterator_traits<T*> {
		/*
		 * member types
		 */

		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template < class T >
	struct iterator_traits<const T*> {
		/*
		 * member types
		 */

		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	/* iterator operations */

	/**
	 * @brief advance iterator
	 * @note advances the iterator it by n element positions.
	 * 
	 * @param it: iterator to be advanced.
	 * @param n: number of element positions to advance.
	 */
	template <class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n) { it += n; }

	/**
	 * @brief return distance between iterators
	 * @note calculates the number of elements between first and last.
	 * 
	 * @param first: iterator pointing to the initial element.
	 * @param last: iterator pointing to the final element. This must be reachable from first.
	 */
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		typename iterator_traits<InputIterator>::difference_type count = 0;
		for (; first != last; ++first)
			++count;

		return count;
	}

	/* random access iterator */
	
	template < class T >
	class random_access_iterator : public iterator<random_access_iterator_tag, T> {
		public:
		/*
		 * member types
		 */

		typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
		typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
		typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		public:
		/*
		 * member functions
		 */

		/* constructor / destructor / operator= */

		random_access_iterator(void) : _val(NULL) {}
		random_access_iterator(pointer val) : _val(val) {}
		random_access_iterator(random_access_iterator const & src) : _val(src._val) {}
		virtual ~random_access_iterator(void) {}

		random_access_iterator & operator= (random_access_iterator const & rhs) {
			if (this == &rhs) return *this;

			this->_val = rhs._val;
			return *this;
		}

		//////////////
		pointer base() const
                { return (this->_val); }
		//////////////

		/* operator */
		
		/** @brief dereference iterator */
		reference	operator* (void) const { return *_val; }

		/** @brief derefence iterator */
		pointer	operator-> (void) const { return &operator*(); }

		/** @brief increment iterator position*/
		random_access_iterator &	operator++ (void) {
			++_val;
			return *this;
		}
		
		random_access_iterator	operator++ (int) {
			random_access_iterator tmp(*this);
			operator++();
			return tmp;
		}

		/** @brief decrease iterator position*/
		random_access_iterator &	operator-- (void) {
			--_val;
			return *this;
		}
		
		random_access_iterator	operator-- (int) {
			random_access_iterator tmp(*this);
			operator--();
			return tmp;
		}

		/** @brief addition iterator */
		random_access_iterator	operator+ (difference_type n) const {
			random_access_iterator tmp(*this);

			tmp._val += n;
			return tmp;
		}

		/** @brief subtraction iterator */
		random_access_iterator	operator- (difference_type n) const {
			random_access_iterator tmp(*this);

			tmp._val -= n;
			return tmp;
		}

		/** @brief advance iterator */
		random_access_iterator	operator+= (difference_type n) const {
			_val += n;
			return *this;
		}

		/** @brief retrocede iterator */
		random_access_iterator	operator-= (difference_type n) const {
			_val -= n;
			return *this;
		}

		/** @brief dereference iterator with offset  */
		reference	operator[] (difference_type n) const { return *(_val + n); }
		
		// bool operator== (const random_access_iterator & lhs, const random_access_iterator & rhs);
		// bool operator!= (const random_access_iterator & lhs, const random_access_iterator & rhs) {
		// 	return !(lhs._val == rhs._val);
		// }

		// friend bool operator!= (const random_access_iterator & lhs, const random_access_iterator & rhs) {
		// 	return !(lhs._val == rhs._val);
		// }

		friend bool operator!= (const random_access_iterator & lhs, const random_access_iterator & rhs);
		// bool operator< (const random_access_iterator & lhs, const random_access_iterator & rhs);
		// bool operator<= (const random_access_iterator & lhs, const random_access_iterator & rhs);
		// bool operator> (const random_access_iterator & lhs, const random_access_iterator & rhs);
		// bool operator>= (const random_access_iterator & lhs, const random_access_iterator & rhs);

		private:
			pointer _val;
	};

	/**
	 * non-member function
	 */

	// template <typename T>
    // typename ft::random_access_iterator<T>::difference_type
    // operator!=(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() != rhs.base());
    // }

    /* For iterator != const_iterator */
    // template<typename T_L, typename T_R>
    // typename ft::random_access_iterator<T_L>::difference_type
    // operator!=(const ft::random_access_iterator<T_L> lhs,
    //           const ft::random_access_iterator<T_R> rhs)
    // {
    //     return (lhs.base() != rhs.base());
    // }


	// template <class T>
	// bool operator== (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs) {
	// 	return lhs._val == rhs._val;
	// }

	template <class T>
	bool operator!= (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs) {
		return !(lhs.base() == rhs.base());
	}

	// template <class T>
	// bool operator< (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs) {
	// 	return lhs._val < lhs._val;
	// }

	// template <class T>
	// bool operator<= (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs) {
	// 	return lhs._val <= lhs._val;
	// }

	// template <class T>
	// bool operator> (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs) {
	// 	return lhs._val > lhs._val;
	// }

	// template <class T>
	// bool operator>= (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs) {
	// 	return lhs._val >= lhs._val;
	// }

	// template <class T>
	// random_access_iterator<T> operator+ (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> & it) {
	// 	random_access_iterator<T> tmp(it);

	// 	tmp._val += n;
	// 	return tmp;
	// }

	// template <class T>
	// random_access_iterator<T> operator- (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> & it) {
	// 	random_access_iterator<T> tmp(it);

	// 	tmp._val -= n;
	// 	return tmp;
	// }
};

#endif