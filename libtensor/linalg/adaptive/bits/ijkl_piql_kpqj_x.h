#ifndef LIBTENSOR_LINALG_ADAPTIVE_IJKL_PIQL_KPQJ_X_H
#define LIBTENSOR_LINALG_ADAPTIVE_IJKL_PIQL_KPQJ_X_H

#include "trp_ijkl_ikjl.h"
#include "trp_ijkl_kijl.h"
#include "trp_ijkl_kjil.h"

namespace libtensor {


template<typename M, typename L1, typename L2, typename L3>
void linalg_base_level6_adaptive<M, L1, L2, L3>::ijkl_piql_kpqj_x(
	size_t ni, size_t nj, size_t nk, size_t nl, size_t np, size_t nq,
	const double *a, const double *b, double *c, double d) {

	size_t npq = np * nq;
	size_t nil = ni * nl;
	size_t nkj = nk * nj;
	size_t njkl = nkj * nl;
	size_t npq1 = (npq % 4 == 0) ? npq : npq + 4 - npq % 4;
	size_t nil1 = (nil % 4 == 0) ? nil : nil + 4 - nil % 4;
	size_t nkj1 = (nkj % 4 == 0) ? nkj : nkj + 4 - nkj % 4;

	double *a1 = M::allocate(npq * nil1);
	double *b1 = M::allocate(npq * nkj1);
	double *c1 = M::allocate(nkj * nil1);

	//	a1_pqil <- a_piql
	trp_ijkl_ikjl::transpose(np, nq, ni, nl, a, nq * nl, a1, nil1);

	//	b1_pqkj <- b_kpqj
	trp_ijkl_kijl::transpose(np, nq, nk, nj, b, nq * nj, b1, nkj1);

	//	c1_kjil <- c_ijkl
	trp_ijkl_kjil::transpose(nk, nj, ni, nl, c, nk * nl, c1, nil1);

	//	c1_kjil += d * b1_pqkj a1_pqil
	L3::ij_pi_pj_x(nkj, nil, npq, b1, nkj1, a1, nil1, c1, nil1, d);

	//	c_ijkl <- c1_kjil
	trp_ijkl_kjil::transpose(ni, nj, nk, nl, c1, nil1, c, nk * nl);

	M::deallocate(c1);
	M::deallocate(b1);
	M::deallocate(a1);
}


} // namespace libtensor

#endif // LIBTENSOR_LINALG_ADAPTIVE_IJKL_PIQL_KPQJ_X_H