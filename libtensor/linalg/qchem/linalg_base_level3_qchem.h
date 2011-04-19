#ifndef LIBTENSOR_LINALG_BASE_LEVEL3_QCHEM_H
#define LIBTENSOR_LINALG_BASE_LEVEL3_QCHEM_H

#include "../generic/linalg_base_level3_generic.h"

namespace libtensor {


/**	\brief Level-3 linear algebra operations (Q-Chem)

	\ingroup libtensor_linalg
 **/
struct linalg_base_level3_qchem : public linalg_base_level3_generic {


	static void ij_ip_jp_x(
		size_t ni, size_t nj, size_t np,
		const double *a, size_t sia,
		const double *b, size_t sjb,
		double *c, size_t sic,
		double d) {

		CL_DGEMM('T', 'N', nj, ni, np, d, (double*)b, sjb, (double*)a,
			sia, 1.0, c, sic);
	}


	static void ij_ip_pj_x(
		size_t ni, size_t nj, size_t np,
		const double *a, size_t sia,
		const double *b, size_t spb,
		double *c, size_t sic,
		double d) {

		CL_DGEMM('N', 'N', nj, ni, np, d, (double*)b, spb, (double*)a,
			sia, 1.0, c, sic);
	}


	static void ij_pi_jp_x(
		size_t ni, size_t nj, size_t np,
		const double *a, size_t spa,
		const double *b, size_t sjb,
		double *c, size_t sic,
		double d) {

		CL_DGEMM('T', 'T', nj, ni, np, d, (double*)b, sjb, (double*)a,
			spa, 1.0, c, sic);
	}


	static void ij_pi_pj_x(
		size_t ni, size_t nj, size_t np,
		const double *a, size_t spa,
		const double *b, size_t spb,
		double *c, size_t sic,
		double d) {

		CL_DGEMM('N', 'T', nj, ni, np, d, (double*)b, spb, (double*)a,
			spa, 1.0, c, sic);
	}


};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_BASE_LEVEL3_QCHEM_H
