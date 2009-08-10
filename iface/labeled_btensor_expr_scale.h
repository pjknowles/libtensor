#ifndef LIBTENSOR_LABELED_BTENSOR_EXPR_SCALE_H
#define LIBTENSOR_LABELED_BTENSOR_EXPR_SCALE_H

#include "defs.h"
#include "exception.h"
#include "labeled_btensor_expr.h"
#include "labeled_btensor_expr_arg.h"
#include "letter_expr.h"

namespace libtensor {

template<size_t N, typename T, typename Expr>
class labeled_btensor_eval_scale;

/**	\brief Expression core that scales an underlying expression
	\tparam N Tensor order.
	\tparam T Tensor element type.
	\tparam Expr Underlying expression type (labeled_btensor_expr).

	\ingroup libtensor_btensor_expr
 **/
template<size_t N, typename T, typename Expr>
class labeled_btensor_expr_scale {
public:
	//!	Evaluating container type
	typedef labeled_btensor_eval_scale<N, T, Expr> eval_container_t;

private:
	Expr m_expr; //!< Unscaled expression
	T m_coeff; //!< Scaling coefficient

public:
	/**	\brief Constructs the scaling expression using a coefficient
			and the underlying unscaled expression
	 **/
	labeled_btensor_expr_scale(T coeff, const Expr &expr)
		: m_coeff(coeff), m_expr(expr) { }

	/**	\brief Returns the unscaled expression
	 **/
	Expr &get_unscaled_expr() { return m_expr; }

	/**	\brief Returns the scaling coefficient
	 **/
	T get_coeff() { return m_coeff; }

	/**	\brief Returns whether the %tensor's label contains a %letter
	 **/
	bool contains(const letter &let) const;

	/**	\brief Returns the %index of a %letter in the %tensor's label
	 **/
	size_t index_of(const letter &let) const throw(exception);

	/**	\brief Returns the %letter at a given position in
			the %tensor's label
	 **/
	const letter &letter_at(size_t i) const throw(exception);

};

/**	\brief Evaluates a scaled expression
	\tparam N Tensor order.
	\tparam T Tensor element type.
	\tparam Expr Underlying expression type.

	\ingroup libtensor_btensor_expr
 **/
template<size_t N, typename T, typename Expr>
class labeled_btensor_eval_scale {
public:
	//!	Scaling expression core type
	typedef labeled_btensor_expr_scale<N, T, Expr> core_t;

	//!	Scaled expression type
	typedef labeled_btensor_expr<N, T, core_t> expression_t;

	//!	Unscaled expression evaluating container type
	typedef typename Expr::eval_container_t unscaled_eval_container_t;

	//!	Number of %tensor arguments in the expression
	static const size_t k_narg_tensor =
		unscaled_eval_container_t::k_narg_tensor;

	//!	Number of %tensor operation arguments in the expression
	static const size_t k_narg_oper =
		unscaled_eval_container_t::k_narg_oper;

private:
	expression_t &m_expr; //!< Scaled expression

	//!	Unscaled expression evaluating container
	unscaled_eval_container_t m_unscaled_cont;

public:
	//!	\name Construction
	//@{

	/**	\brief Constructs the evaluating container
	 **/
	template<typename LabelLhs>
	labeled_btensor_eval_scale(expression_t &expr,
		labeled_btensor<N, T, true, LabelLhs> &result) throw(exception);

	//@}

	//!	\name Evaluation
	//@{

	labeled_btensor_expr_arg_tensor<N, T> get_arg_tensor(size_t i) const
		throw(exception);

	labeled_btensor_expr_arg_oper<N, T> get_arg_oper(size_t i) const
		throw(exception);

	//@}
};

template<size_t N, typename T, typename Expr>
inline bool labeled_btensor_expr_scale<N, T, Expr>::contains(
	const letter &let) const {

	return m_expr.contains(let);
}

template<size_t N, typename T, typename Expr>
inline size_t labeled_btensor_expr_scale<N, T, Expr>::index_of(
	const letter &let) const throw(exception) {

	return m_expr.index_of(let);
}

template<size_t N, typename T, typename Expr>
inline const letter &labeled_btensor_expr_scale<N, T, Expr>::letter_at(
	size_t i) const throw(exception) {

	return m_expr.letter_at(i);
}

template<size_t N, typename T, typename Expr> template<typename LabelLhs>
labeled_btensor_eval_scale<N, T, Expr>::labeled_btensor_eval_scale(
	expression_t &expr, labeled_btensor<N, T, true, LabelLhs> &result)
	throw(exception) : m_expr(expr),
	m_unscaled_cont(expr.get_core().get_unscaled_expr(), result) {

}

template<size_t N, typename T, typename Expr>
inline labeled_btensor_expr_arg_tensor<N, T>
labeled_btensor_eval_scale<N, T, Expr>::get_arg_tensor(size_t i) const
	throw(exception) {

	labeled_btensor_expr_arg_tensor<N, T> arg =
		m_unscaled_cont.get_arg_tensor(i);
	arg.scale(m_expr.get_core().get_coeff());
	return arg;
}

template<size_t N, typename T, typename Expr>
inline labeled_btensor_expr_arg_oper<N, T>
labeled_btensor_eval_scale<N, T, Expr>::get_arg_oper(size_t i) const
	throw(exception) {

	labeled_btensor_expr_arg_oper<N, T> arg =
		m_unscaled_cont.get_arg_oper(i);
	arg.scale(m_expr.get_core().get_coeff());
	return arg;
}

} // namespace libtensor

#endif // LIBTENSOR_LABELED_BTENSOR_EXPR_SCALE_H