#ifndef LIBTENSOR_KERN_MUL2_IJ_PJ_IP_IMPL_H
#define LIBTENSOR_KERN_MUL2_IJ_PJ_IP_IMPL_H

#include "kern_mul2_ij_pj_ip.h"

namespace libtensor {


template<typename LA, typename T>
const char *kern_mul2_ij_pj_ip<LA, T>::k_clazz = "kern_mul2_ij_pj_ip";


template<typename LA, typename T>
void kern_mul2_ij_pj_ip<LA, T>::run(
    device_context_ref ctx,
    const loop_registers_x<2, 1, T> &r) {

    LA::mul2_ij_ip_pj_x(ctx, m_ni, m_nj, m_np, r.m_ptra[1], m_sib,
        r.m_ptra[0], m_spa, r.m_ptrb[0], m_sic, m_d);
}


template<typename LA, typename T>
kernel_base<LA, 2, 1, T> *kern_mul2_ij_pj_ip<LA, T>::match(
    const kern_mul2_i_pi_p<LA, T> &z, list_t &in, list_t &out) {

    if(in.empty()) return 0;
    if(z.m_spb != 1 || z.m_sic != 1) return 0;

    //  Rename i->j

    //  1. Minimize sib > 0:
    //  -----------------
    //  w   a    b    c
    //  nj  1    0    1
    //  np  spa  1    0
    //  ni  0    sib  sic  --> c_j#i = a_p$i b_j%p
    //  -----------------      sz(i) = w1, sz(j) = w3,
    //                         sz(p) = w2
    //                         sz(#) = k6, sz($) = k2,
    //                         sz(%) = k5
    //                         [ij_pj_ip]

    iterator_t ii = in.end();
    size_t sib_min = 0;
    for(iterator_t i = in.begin(); i != in.end(); i++) {
        if(i->stepa(0) == 0 && i->stepa(1) > 0 && i->stepb(0) > 0) {
            if(i->stepa(1) % z.m_np) continue;
            if(i->stepb(0) % z.m_ni) continue;
            if(sib_min == 0 || sib_min > i->stepa(1)) {
                ii = i; sib_min = i->stepa(1);
            }
        }
    }
    if(ii == in.end()) return 0;

    kern_mul2_ij_pj_ip zz;
    zz.m_d = z.m_d;
    zz.m_ni = ii->weight();
    zz.m_nj = z.m_ni;
    zz.m_np = z.m_np;
    zz.m_spa = z.m_spa;
    zz.m_sib = ii->stepa(1);
    zz.m_sic = ii->stepb(0);
    in.splice(out.begin(), out, ii);

    return new kern_mul2_ij_pj_ip(zz);
}


} // namespace libtensor

#endif // LIBTENSOR_KERN_MUL2_IJ_PJ_IP_IMPL_H
