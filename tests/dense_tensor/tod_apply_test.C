#include <sstream>
#include <libtensor/core/allocator.h>
#include <libtensor/dense_tensor/dense_tensor.h>
#include <libtensor/dense_tensor/tod_apply.h>
#include <libtensor/dense_tensor/impl/tod_apply_impl.h>
#include "../compare_ref.h"
#include "../test_utils.h"

using namespace libtensor;

namespace {

struct sin_functor {
    double operator()(const double &x) { return sin(x); }
};

} // unnamed namespace


template<size_t N, typename Functor>
int test_plain(Functor &fn, const dimensions<N> &dims) {

    static const char testname[] = "tod_apply_test::test_plain()";

    typedef allocator<double> allocator;

    try {

    dense_tensor<N, double, allocator> ta(dims), tb(dims), tb_ref(dims);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dims);
    do {
        size_t i = aida.get_abs_index();
        dta[i] = drand48();
        dtb2[i] = fn(dta[i]);
        dtb1[i] = drand48();
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    tod_apply<N, Functor> cp(ta, fn);
    cp.perform(true, tb);

    // Compare against the reference

    compare_ref<N>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}

template<size_t N, typename Functor>
int test_plain_additive(Functor &fn, const dimensions<N> &dims, double d) {

    static const char testname[] = "tod_apply_test::test_plain_additive()";

    typedef allocator<double> allocator;

    try {

    dense_tensor<N, double, allocator> ta(dims), tb(dims), tb_ref(dims);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dims);
    do {
        size_t i = aida.get_abs_index();
        dta[i] = drand48();
        dtb1[i] = drand48();
        dtb2[i] = dtb1[i] + d * fn(dta[i]);
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    permutation<N> p;
    tensor_transf<N, double> tr2(p, scalar_transf<double>(d));
    tod_apply<N, Functor> cp(ta, fn, scalar_transf<double>(), tr2);
    cp.perform(false, tb);

    // Compare against the reference

    std::ostringstream ss;
    ss << "tod_apply_test::test_plain_additive(" << d << ")";
    compare_ref<N>::compare(ss.str().c_str(), tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}

template<size_t N, typename Functor>
int test_scaled(Functor &fn, const dimensions<N> &dims, double c) {

    static const char testname[] = "tod_apply_test::test_scaled()";

    typedef allocator<double> allocator;

    try {

    dense_tensor<N, double, allocator> ta(dims), tb(dims), tb_ref(dims);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dims);
    do {
        size_t i = aida.get_abs_index();
        dta[i] = drand48();
        dtb2[i] = fn(c * dta[i]);
        dtb1[i] = drand48();
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    tod_apply<N, Functor> cp(ta, fn, c);
    cp.perform(true, tb);

    // Compare against the reference

    std::ostringstream ss; ss << "tod_apply_test::test_scaled(" << c << ")";
    compare_ref<N>::compare(ss.str().c_str(), tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}


template<size_t N, typename Functor>
int test_scaled_additive(Functor &fn, const dimensions<N> &dims, double c,
    double d) {

    static const char testname[] = "tod_apply_test::test_scaled_additive()";

    typedef allocator<double> allocator;

    try {

    dense_tensor<N, double, allocator> ta(dims), tb(dims), tb_ref(dims);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dims);
    do {
        size_t i = aida.get_abs_index();
        dta[i] = drand48();
        dtb1[i] = drand48();
        dtb2[i] = dtb1[i] + d * fn(c * dta[i]);
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    permutation<N> p;
    tensor_transf<N, double> tr2(p, scalar_transf<double>(d));
    tod_apply<N, Functor> cp(ta, fn, scalar_transf<double>(c), tr2);
    cp.perform(false, tb);

    // Compare against the reference

    std::ostringstream ss; ss << "tod_apply_test::test_scaled_additive("
        << c << ")";
    compare_ref<N>::compare(ss.str().c_str(), tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}


template<size_t N, typename Functor>
int test_perm(Functor &fn, const dimensions<N> &dims,
    const permutation<N> &perm) {

    static const char testname[] = "tod_apply_test::test_perm()";

    typedef allocator<double> allocator;

    try {

    dimensions<N> dimsa(dims), dimsb(dims);
    dimsb.permute(perm);

    dense_tensor<N, double, allocator> ta(dimsa), tb(dimsb), tb_ref(dimsb);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dimsa);
    do {
        index<N> idb(aida.get_index());
        idb.permute(perm);
        abs_index<N> aidb(idb, dimsb);
        size_t i, j;
        i = aida.get_abs_index();
        j = aidb.get_abs_index();
        dta[i] = drand48();
        dtb1[i] = drand48();
        dtb2[j] = fn(dta[i]);
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    tod_apply<N, Functor> cp(ta, fn, perm);
    cp.perform(true, tb);

    // Compare against the reference

    compare_ref<N>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}


template<size_t N, typename Functor>
int test_perm_additive(Functor &fn, const dimensions<N> &dims,
    const permutation<N> &perm, double d) {

    static const char testname[] = "tod_apply_test::test_perm_additive()";

    typedef allocator<double> allocator;

    try {

    dimensions<N> dimsa(dims), dimsb(dims);
    dimsb.permute(perm);

    dense_tensor<N, double, allocator> ta(dimsa), tb(dimsb), tb_ref(dimsb);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dimsa);
    do {
        index<N> idb(aida.get_index());
        idb.permute(perm);
        abs_index<N> aidb(idb, dimsb);
        size_t i, j;
        i = aida.get_abs_index();
        j = aidb.get_abs_index();
        dta[i] = drand48();
        dtb1[j] = drand48();
        dtb2[j] = dtb1[j] + d * fn(dta[i]);
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    tensor_transf<N, double> tr2(perm, scalar_transf<double>(d));
    tod_apply<N, Functor> cp(ta, fn, scalar_transf<double>(), tr2);
    cp.perform(false, tb);

    // Compare against the reference

    compare_ref<N>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}


template<size_t N, typename Functor>
int test_perm_scaled(Functor &fn, const dimensions<N> &dims,
    const permutation<N> &perm, double c) {

    static const char testname[] = "tod_apply_test::test_perm_scaled()";

    typedef allocator<double> allocator;

    try {

    dimensions<N> dimsa(dims), dimsb(dims);
    dimsb.permute(perm);

    dense_tensor<N, double, allocator> ta(dimsa), tb(dimsb), tb_ref(dimsb);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dimsa);
    do {
        index<N> idb(aida.get_index());
        idb.permute(perm);
        abs_index<N> aidb(idb, dimsb);
        size_t i, j;
        i = aida.get_abs_index();
        j = aidb.get_abs_index();
        dta[i] = drand48();
        dtb1[j] = drand48();
        dtb2[j] = fn(c * dta[i]);
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    tod_apply<N, Functor> cp(ta, fn, perm, c);
    cp.perform(true, tb);

    // Compare against the reference

    compare_ref<N>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}


template<size_t N, typename Functor>
int test_perm_scaled_additive(Functor &fn, const dimensions<N> &dims,
    const permutation<N> &perm, double c, double d) {

    static const char testname[] =
        "tod_apply_test::test_perm_scaled_additive()";

    typedef allocator<double> allocator;

    try {

    dimensions<N> dimsa(dims), dimsb(dims);
    dimsb.permute(perm);

    dense_tensor<N, double, allocator> ta(dimsa), tb(dimsb), tb_ref(dimsb);

    {
    dense_tensor_ctrl<N, double> tca(ta), tcb(tb), tcb_ref(tb_ref);

    double *dta = tca.req_dataptr();
    double *dtb1 = tcb.req_dataptr();
    double *dtb2 = tcb_ref.req_dataptr();

    // Fill in random data

    abs_index<N> aida(dimsa);
    do {
        index<N> idb(aida.get_index());
        idb.permute(perm);
        abs_index<N> aidb(idb, dimsb);
        size_t i, j;
        i = aida.get_abs_index();
        j = aidb.get_abs_index();
        dta[i] = drand48();
        dtb1[j] = drand48();
        dtb2[j] = dtb1[j] + d * fn(c * dta[i]);
    } while(aida.inc());

    tca.ret_dataptr(dta); dta = NULL;
    tcb.ret_dataptr(dtb1); dtb1 = NULL;
    tcb_ref.ret_dataptr(dtb2); dtb2 = NULL;
    ta.set_immutable(); tb_ref.set_immutable();
    }

    // Invoke the operation

    tensor_transf<N, double> tr2(perm, scalar_transf<double>(d));
    tod_apply<N, Functor> cp(ta, fn, scalar_transf<double>(c), tr2);
    cp.perform(false, tb);

    // Compare against the reference

    compare_ref<N>::compare(testname, tb, tb_ref, 1e-15);

    } catch(exception &exc) {
        return fail_test(testname, __FILE__, __LINE__, exc.what());
    }

    return 0;
}


int test_exc() {

    typedef allocator<double> allocator;

    index<4> i1, i2, i3;
    i2[0]=2; i2[1]=2; i2[2]=2; i2[3]=2;
    i3[0]=3; i3[1]=3; i3[2]=3; i3[3]=3;
    index_range<4> ir1(i1,i2), ir2(i1,i3);
    dimensions<4> dim1(ir1), dim2(ir2);
    dense_tensor<4, double, allocator> t1(dim1), t2(dim2);

    bool ok = false;
    try {
        sin_functor sin;
        tod_apply<4, sin_functor> tc(t1, sin);
        tc.perform(true, t2);
    } catch(exception &e) {
        ok = true;
    }

    if(!ok) {
        return fail_test("tod_apply_test::test_exc()", __FILE__, __LINE__,
        "Expected an exception with heterogeneous arguments");
    }

    return 0;
}


int main() {

    sin_functor sin;
    index<2> i2a, i2b; i2b[0]=10; i2b[1]=12;
    index_range<2> ir2(i2a, i2b); dimensions<2> dims2(ir2);
    permutation<2> perm2, perm2t;
    perm2t.permute(0, 1);

    index<4> i4a, i4b;
    i4b[0] = 4; i4b[1] = 5; i4b[2] = 6; i4b[3] = 7;
    dimensions<4> dims4(index_range<4>(i4a, i4b));
    permutation<4> perm4, perm4c;
    perm4c.permute(0, 1).permute(1, 2).permute(2, 3);

    return

    test_exc() |

    test_plain(sin, dims2) |
    test_plain_additive(sin, dims2, 1.0) |
    test_plain_additive(sin, dims2, -1.0) |
    test_plain_additive(sin, dims2, 2.5) |

    test_scaled(sin, dims2, 1.0) |
    test_scaled(sin, dims2, 0.5) |
    test_scaled(sin, dims2, -3.14) |
    test_scaled_additive(sin, dims2, 1.0, 1.0) |
    test_scaled_additive(sin, dims2, 0.5, 1.0) |
    test_scaled_additive(sin, dims2, -3.14, 1.0) |
    test_scaled_additive(sin, dims2, 1.0, -1.0) |
    test_scaled_additive(sin, dims2, 0.5, -1.0) |
    test_scaled_additive(sin, dims2, -3.14, -1.0) |
    test_scaled_additive(sin, dims2, 1.0, 2.5) |
    test_scaled_additive(sin, dims2, 0.5, 2.5) |
    test_scaled_additive(sin, dims2, -3.14, 2.5) |

    test_perm(sin, dims2, perm2) |
    test_perm(sin, dims2, perm2t) |
    test_perm_additive(sin, dims2, perm2, 1.0) |
    test_perm_additive(sin, dims2, perm2, -1.0) |
    test_perm_additive(sin, dims2, perm2, 2.5) |
    test_perm_additive(sin, dims2, perm2t, 1.0) |
    test_perm_additive(sin, dims2, perm2t, -1.0) |
    test_perm_additive(sin, dims2, perm2t, 2.5) |

    test_perm_scaled(sin, dims2, perm2, 1.0) |
    test_perm_scaled(sin, dims2, perm2t, 1.0) |
    test_perm_scaled(sin, dims2, perm2, 0.5) |
    test_perm_scaled(sin, dims2, perm2t, 0.5) |
    test_perm_scaled(sin, dims2, perm2, -3.14) |
    test_perm_scaled(sin, dims2, perm2t, -3.14) |
    test_perm_scaled_additive(sin, dims2, perm2, 1.0, 1.0) |
    test_perm_scaled_additive(sin, dims2, perm2t, 1.0, 1.0) |
    test_perm_scaled_additive(sin, dims2, perm2, 0.5, 1.0) |
    test_perm_scaled_additive(sin, dims2, perm2t, 0.5, 1.0) |
    test_perm_scaled_additive(sin, dims2, perm2, -3.14, 1.0) |
    test_perm_scaled_additive(sin, dims2, perm2t, -3.14, 1.0) |
    test_perm_scaled_additive(sin, dims2, perm2, 1.0, -1.0) |
    test_perm_scaled_additive(sin, dims2, perm2t, 1.0, -1.0) |
    test_perm_scaled_additive(sin, dims2, perm2, 0.5, -1.0) |
    test_perm_scaled_additive(sin, dims2, perm2t, 0.5, -1.0) |
    test_perm_scaled_additive(sin, dims2, perm2, -3.14, -1.0) |
    test_perm_scaled_additive(sin, dims2, perm2t, -3.14, -1.0) |
    test_perm_scaled_additive(sin, dims2, perm2, 1.0, 2.5) |
    test_perm_scaled_additive(sin, dims2, perm2t, 1.0, 2.5) |
    test_perm_scaled_additive(sin, dims2, perm2, 0.5, 2.5) |
    test_perm_scaled_additive(sin, dims2, perm2t, 0.5, 2.5) |
    test_perm_scaled_additive(sin, dims2, perm2, -3.14, 2.5) |
    test_perm_scaled_additive(sin, dims2, perm2t, -3.14, 2.5) |

    test_perm(sin, dims4, perm4) |
    test_perm(sin, dims4, perm4c) |

    0;
}

