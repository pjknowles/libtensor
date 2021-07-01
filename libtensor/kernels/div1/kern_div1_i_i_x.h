#ifndef LIBTENSOR_KERN_DIV1_I_I_X_H
#define LIBTENSOR_KERN_DIV1_I_I_X_H

#include "../kern_div1.h"

namespace libtensor {


/** \brief Specialized kernel for \f$ b_i = d b_i / a_i \f$
    \tparam LA Linear algebra.

     \ingroup libtensor_kernels
 **/
template<typename LA, typename T>
class kern_div1_i_i_x : public kernel_base<LA, 1, 1, T> {
public:
    static const char *k_clazz; //!< Kernel name

public:
    typedef typename kernel_base<LA, 1, 1, T>::device_context_ref
        device_context_ref;
    typedef typename kernel_base<LA, 1, 1, T>::list_t list_t;
    typedef typename kernel_base<LA, 1, 1, T>::iterator_t iterator_t;

private:
    T m_d;
    size_t m_ni;
    size_t m_sia, m_sib;

public:
    virtual ~kern_div1_i_i_x() { }

    virtual const char *get_name() const {
        return k_clazz;
    }

    virtual void run(device_context_ref ctx, const loop_registers_x<1, 1, T> &r);

    static kernel_base<LA, 1, 1, T> *match(const kern_div1<LA, T> &z,
        list_t &in, list_t &out);

};


} // namespace libtensor

#endif // LIBTENSOR_KERN_DIV1_I_I_X_H