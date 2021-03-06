#include <complex>
#include <mkl_types.h>
#define MKL_Complex16 std::complex<double>
#include <mkl_lapack.h>
#include <libtensor/not_implemented.h>
#include "../lapack_mkl.h"

namespace libtensor {


int lapack_dgesv(size_t n, size_t nrhs, double *a, size_t lda,
    int *ipiv, double *b, size_t ldb) {

    int mkl_n = n;
    int mkl_nrhs = nrhs;
    int mkl_lda = lda;
    int mkl_ldb = ldb;
    int mkl_info = 0;
    dgesv(&mkl_n, &mkl_nrhs, a, &mkl_lda, ipiv, b, &mkl_ldb, &mkl_info);
    return mkl_info;
}


int lapack_dgesvd(char jobu, char jobvt, size_t m, size_t n, double *a,
    size_t lda, double *s, double *u, size_t ldu, double *vt, size_t ldvt,
    double *work, size_t lwork) {

    int mkl_m = m;
    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_ldu = ldu;
    int mkl_ldvt = ldvt;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    dgesvd(&jobu, &jobvt, &mkl_m, &mkl_n, a, &mkl_lda, s, u, &mkl_ldu,
        vt, &mkl_ldvt, work, &mkl_lwork, &mkl_info);
    return mkl_info;
}


int lapack_zgesvd(char jobu, char jobvt, size_t m, size_t n,
    std::complex <double> *a, size_t lda, double *s, std::complex <double> *u,
    size_t ldu, std::complex <double> *vt, size_t ldvt,
    std::complex <double> *work, size_t lwork, double *rwork) {

    int mkl_m = m;        
    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_ldu = ldu;
    int mkl_ldvt = ldvt;
    int mkl_lwork = lwork;
    int mkl_info = 0;

    zgesvd(&jobu, &jobvt, &mkl_m, &mkl_n, a, &mkl_lda, s, u, &mkl_ldu,
        vt, &mkl_ldvt, work, &mkl_lwork, rwork, &mkl_info);
    return mkl_info;
}


int lapack_dsyev(char jobz, char uplo, size_t n, double *a, size_t lda,
    double *w, double *work, size_t lwork) {

    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    dsyev(&jobz, &uplo, &mkl_n, a, &mkl_lda, w, work, &mkl_lwork, &mkl_info);
    return mkl_info;
}


int lapack_dgeev(char jobvl, char jobvr, size_t n, double *a, size_t lda,
    double *wr, double *wi, double *vl, size_t ldvl, double *vr, size_t ldvr,
    double *work, size_t lwork) {

    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_ldvl = ldvl;
    int mkl_ldvr = ldvr;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    dgeev(&jobvl, &jobvr, &mkl_n, a, &mkl_lda, wr, wi, vl, &mkl_ldvl,
        vr, &mkl_ldvr, work, &mkl_lwork, &mkl_info);
    return mkl_info;
}

int lapack_dggev(char jobvl, char jobvr, size_t n, double *a,
    size_t lda, double * b, size_t ldb, double *alphar, double *alphai, double * beta, double *vl, size_t ldvl, double *vr,
    size_t ldvr, double *work, size_t lwork) {

    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_ldb = ldb;
    int mkl_ldvl = ldvl;
    int mkl_ldvr = ldvr;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    dggev(&jobvl, &jobvr, &mkl_n, a, &mkl_lda, b, &mkl_ldb, alphar, alphai, beta, vl, &mkl_ldvl, vr, &mkl_ldvr, work, &mkl_lwork, &mkl_info);
    return mkl_info;
}

int lapack_zgeev(char jobvl, char jobvr, size_t n,
    std::complex <double> *a, size_t lda, std::complex <double> *w,
    std::complex <double> *vl, size_t ldvl, std::complex <double> *vr,
    size_t ldvr, std::complex <double> *work, size_t lwork, double *rwork) {

    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_ldvl = ldvl;
    int mkl_ldvr = ldvr;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    zgeev(&jobvl, &jobvr, &mkl_n, a, &mkl_lda, w, vl, &mkl_ldvl, vr, &mkl_ldvr,
        work, &mkl_lwork, rwork, &mkl_info);
    return mkl_info;
}


int lapack_dgelss(size_t m, size_t n, size_t nrhs, double *B, size_t lda,
    double *rhs, size_t ldb, double *S, double rcond, int *rank, double *work,
    size_t lwork) {

    int mkl_m = m;
    int mkl_n = n;
    int mkl_nrhs = nrhs;
    int mkl_lda = lda;
    int mkl_ldb = ldb;
    double mkl_rcond = rcond;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    dgelss(&mkl_m, &mkl_n, &mkl_nrhs, B, &mkl_lda, rhs, &mkl_ldb, S, &mkl_rcond,
        rank, work, &mkl_lwork, &mkl_info);
    return mkl_info;
}


int lapack_dgelsd(size_t m, size_t n, size_t nrhs, double *B, size_t lda,
    double *rhs, size_t ldb, double *S, double rcond, int *rank, double *work,
    size_t lwork, int * iwork) {

    int mkl_m = m;
    int mkl_n = n;
    int mkl_nrhs = nrhs;
    int mkl_lda = lda;
    int mkl_ldb = ldb;
    double mkl_rcond = rcond;
    int mkl_lwork = lwork;
    int mkl_info = 0;
    dgelsd(&mkl_m, &mkl_n, &mkl_nrhs, B, &mkl_lda, rhs, &mkl_ldb, S, &mkl_rcond,
        rank, work, &mkl_lwork, iwork ,&mkl_info);
    return mkl_info;
}


int lapack_dpotrf(char uplo, size_t n, double *a, size_t lda) {

    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_info = 0;
    dpotrf(&uplo, &mkl_n, a, &mkl_lda, &mkl_info);
    return mkl_info;
}


int lapack_dpotri(char uplo, size_t n, double *a, size_t lda) {

    int mkl_n = n;
    int mkl_lda = lda;
    int mkl_info = 0;
    dpotri(&uplo, &mkl_n, a, &mkl_lda, &mkl_info);
    return mkl_info;
}


int lapack_dlarnv(size_t idist, int * iseed, size_t n, double *x) {

    int mkl_idist = idist;
    int mkl_n = n;

    dlarnv(&mkl_idist, iseed, &mkl_n, x);

    return 0;
}


int lapack_dpstrf(char uplo, size_t n, double *a, size_t lda, int *p, int *rank,
    double tol, double *work) {

    int mkl_info = 0;
//#ifdef HAVE_LAPACK_DPSTRF
    int mkl_n = n;
    int mkl_lda = lda;
    double mkl_tol = tol;
    dpotrf(&uplo, &mkl_n, a, &mkl_lda, &mkl_info);
    //dpstrf(&uplo, &mkl_n, a, &mkl_lda, p, rank, &mkl_tol, work, &mkl_info);
//#else // HAVE_LAPACK_DPSTRF
//    throw not_implemented(g_ns, 0, "lapack_dpstrf", __FILE__, __LINE__);
//#endif // HAVE_LAPACK_DPSTRF

    return mkl_info;
}


int lapack_dpteqr(char compz, size_t n, double *d, double *e, double *z,
    size_t ldz, double *work) {

    int mkl_info = 0;
    int mkl_n = n;
    int mkl_ldz = ldz;
    dpteqr(&compz, &mkl_n, d, e, z, &mkl_ldz, work, &mkl_info);

    return mkl_info;
}


int lapack_dsteqr(char compz, size_t n, double *d, double *e, double *z,
    size_t ldz, double *work) {

    int mkl_info = 0;
    int mkl_n = n;
    int mkl_ldz = ldz;
    dsteqr(&compz, &mkl_n, d, e, z, &mkl_ldz, work, &mkl_info);

    return mkl_info;
}


} // namespace libtensor
