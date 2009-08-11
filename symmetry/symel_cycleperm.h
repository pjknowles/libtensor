#ifndef LIBTENSOR_SYMEL_CYCLEPERM_H
#define LIBTENSOR_SYMEL_CYCLEPERM_H

#include "defs.h"
#include "exception.h"
#include "core/dimensions.h"
#include "core/mask.h"
#include "core/permutation.h"
#include "symmetry_element_base.h"

namespace libtensor {

/**	\brief Symmetry element: cyclic permutation
	\tparam N Tensor order.
	\tparam T Tensor element type.

	\ingroup libtensor_symmetry
 **/
template<size_t N, typename T>
class symel_cycleperm :
	public symmetry_element_base< N, T, symel_cycleperm<N, T> > {

public:
	static const char *k_clazz; //!< Class name

private:
	class equals_functor :
		public symmetry_element_target< N, T, symel_cycleperm<N, T> > {
	private:
		const symel_cycleperm<N, T> &m_elem;
		bool m_eq;
	public:
		equals_functor(const symel_cycleperm<N, T> &elem)
			: m_elem(elem), m_eq(false) { };
		virtual ~equals_functor() { };
		virtual void accept_default(
			const symmetry_element_i<N, T> &elem) throw(exception) {
			m_eq = false;
		}
		virtual void accept(const symel_cycleperm<N, T> &elem)
			throw(exception) {
			m_eq = m_elem.equals(elem);
		}
		bool get_equals() { return m_eq; }
	};

private:
	mask<N> m_msk; //!< Mask of affected indexes
	dimensions<N> m_dims; //!< Dimensions
	permutation<N> m_perm; //!< Permutation

public:
	//!	\name Construction and destruction
	//@{
	symel_cycleperm(const mask<N> &msk, const dimensions<N> &dims);
	symel_cycleperm(const symel_cycleperm<N, T> &el);
	virtual ~symel_cycleperm();
	//@}

	//!	\name Implementation of symmetry_element_i<N, T>
	//@{
	virtual const mask<N> &get_mask() const;
	virtual bool is_allowed(const index<N> &idx) const;
	virtual void apply(index<N> &idx) const;
	virtual bool equals(const symmetry_element_i<N, T> &se) const;
	virtual symmetry_element_i<N, T> *clone() const;
	/*
	virtual symmetry_element_i<N + 1, T> *project_up(const mask<N + 1> &msk,
		const dimensions<N + 1> &dims) const throw(exception);
	virtual symmetry_element_i<N - 1, T> *project_down(const mask<N> &msk,
		const dimensions<N - 1> &dims) const throw(exception);
		*/
	//@}

	bool equals(const symel_cycleperm<N, T> &elem) const;
	const permutation<N> &get_perm() const;
};



template<size_t N, typename T>
const char *symel_cycleperm<N, T>::k_clazz = "symel_cycleperm<N, T>";


template<size_t N, typename T>
symel_cycleperm<N, T>::symel_cycleperm(
	const mask<N> &msk, const dimensions<N> &dims)
: m_msk(msk), m_dims(dims) {

	static const char *method = "symel_cycleperm(const mask<N>&)";

	size_t i1 = 0, i2, ntrans = 0;
	while(i1 < N && msk[i1] == false) i1++;
	while(i1 < N) {
		i2 = i1 + 1;
		while(i2 < N && msk[i2] == false) i2++;
		if(ntrans == 0 && i2 == N) {
			throw bad_parameter("libtensor", k_clazz, method,
				__FILE__, __LINE__,
				"Invalid mask.");
		}
		if(i2 < N) {
			m_perm.permute(i1, i2);
			ntrans++;
		}
		i1 = i2;
	}
}


template<size_t N, typename T>
symel_cycleperm<N, T>::symel_cycleperm(const symel_cycleperm<N, T> &el)
: m_msk(el.m_msk), m_dims(el.m_dims), m_perm(el.m_perm) {

}


template<size_t N, typename T>
symel_cycleperm<N, T>::~symel_cycleperm() {

}


template<size_t N, typename T>
const mask<N> &symel_cycleperm<N, T>::get_mask() const {

	return m_msk;
}


template<size_t N, typename T>
bool symel_cycleperm<N, T>::is_allowed(const index<N> &idx) const {

	return true;
}



template<size_t N, typename T>
void symel_cycleperm<N, T>::apply(index<N> &idx) const {

	idx.permute(m_perm);
}


template<size_t N, typename T>
bool symel_cycleperm<N, T>::equals(const symmetry_element_i<N, T> &se) const {

	equals_functor eq(*this);
	se.dispatch(eq);
	return eq.get_equals();
}


template<size_t N, typename T>
symmetry_element_i<N, T> *symel_cycleperm<N, T>::clone() const {

	return new symel_cycleperm<N, T>(*this);
}

/*
template<size_t N, typename T>
symmetry_element_i<N + 1, T> *symel_cycleperm<N, T>::project_up(
	const mask<N + 1> &msk, const dimensions<N + 1> &dims) const
	throw(exception) {

	static const char *method = "project_up(const mask<N + 1>&,"
		"const dimensions<N + 1>&)";

	mask<N + 1> newmask;
	size_t j = 0;
	for(size_t i = 0; i < N + 1; i++) {
		if(msk[i]) {
			newmask[i] = m_msk[j];
			j++;
		}
	}
	if(j + 1 < N) {
		throw bad_parameter("libtensor", k_clazz, method, __FILE__,
			__LINE__, "Invalid mask.");
	}
	return new symel_cycleperm<N + 1, T>(newmask, dims);
}


template<size_t N, typename T>
symmetry_element_i<N - 1, T> *symel_cycleperm<N, T>::project_down(
	const mask<N> &msk, const dimensions<N - 1> &dims) const
	throw(exception) {

	static const char *method = "project_down(const mask<N>&,"
		"const dimensions<N - 1>&)";

	mask<N - 1> newmask;
	size_t j = 0;
	for(size_t i = 0; i < N; i++) {
		if(msk[i]) {
			newmask[j] = m_msk[i];
			j++;
		}
	}
	if(j + 2 < N) {
		throw bad_parameter("libtensor", k_clazz, method, __FILE__,
			__LINE__, "Invalid mask.");
	}
	return new symel_cycleperm<N - 1, T>(newmask, dims);
}
*/

template<size_t N, typename T>
bool symel_cycleperm<N, T>::equals(const symel_cycleperm<N, T> &elem) const {

	if(this == &elem) return true;
	return m_msk.equals(elem.m_msk) && m_dims.equals(elem.m_dims) &&
		m_perm.equals(elem.m_perm);
}


template<size_t N, typename T>
inline const permutation<N> &symel_cycleperm<N, T>::get_perm() const {

	return m_perm;
}


} // namespace libtensor

#endif // LIBTENSOR_SYMEL_CYCLEPERM_H