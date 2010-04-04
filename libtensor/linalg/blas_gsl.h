#ifndef LIBTENSOR_BLAS_GSL_H
#define LIBTENSOR_BLAS_GSL_H

#include <gsl/gsl_cblas.h>

namespace libtensor {

/**	\brief BLAS function dcopy (GSL)

	\ingroup libtensor_linalg
 **/
inline void blas_dcopy(
	size_t n, const double *dx, size_t incx, double *dy, size_t incy) {
	cblas_dcopy(n, dx, incx, dy, incy);
}

/**	\brief BLAS function dscal (GSL)

	\ingroup libtensor_linalg
 **/
inline void blas_dscal(size_t n, double da, double *dx, size_t incx) {
	cblas_dscal(n, da, dx, incx);
}


/**	\brief BLAS function daxpy (GSL)

	\ingroup libtensor_linalg
 **/
inline void blas_daxpy(size_t n, double da, const double *dx, size_t incx,
	double *dy, size_t incy) {

	cblas_daxpy(n, da, dx, incx, dy, incy);
}


} // namespace libtensor

#endif // LIBTENSOR_BLAS_GSL_H