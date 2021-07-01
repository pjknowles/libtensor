#ifndef LIBTENSOR_TOD_COPY_H
#define LIBTENSOR_TOD_COPY_H

#include <libtensor/block_tensor/bto_traits.h>
#include <libtensor/core/scalar_transf_double.h>
#include <libtensor/gen_block_tensor/additive_gen_bto.h>
#include <libtensor/gen_block_tensor/gen_bto_copy.h>

namespace libtensor {


/** \brief Copies a block tensor with an optional transformation
    \tparam N Tensor order.

    \sa gen_bto_copy

    \ingroup libtensor_block_tensor_btod
 **/
template<size_t N, typename T>
class bto_copy :
    public additive_gen_bto<N, typename bto_traits<T>::bti_traits>,
    public noncopyable {

public:
    static const char k_clazz[]; //!< Class name

public:
    typedef typename bto_traits<T>::bti_traits bti_traits;

private:
    gen_bto_copy< N, bto_traits<T>, bto_copy<N, T> > m_gbto;

public:
    /** \brief Initializes the operation
        \param bta Source block tensor (A).
        \param c Scaling coefficient.
     **/
    bto_copy(block_tensor_rd_i<N, T> &bta, T c = 1.0) :

        m_gbto(bta, tensor_transf<N, T>(
            permutation<N>(), scalar_transf<T>(c))) {

    }

    /** \brief Initializes the operation
        \param bta Source block tensor (A).
        \param perma Permutation of A.
        \param c Scaling coefficient.
     **/
    bto_copy(
            block_tensor_rd_i<N, T> &bta,
            const permutation<N> &perma,
            T c = 1.0) :

        m_gbto(bta, tensor_transf<N, T>(perma, scalar_transf<T>(c))) {

    }

    virtual ~bto_copy() { }

    //! \name Implementation of libtensor::direct_gen_bto<N, bti_traits>
    //@{

    virtual const block_index_space<N> &get_bis() const {

        return m_gbto.get_bis();
    }

    virtual const symmetry<N, T> &get_symmetry() const {

        return m_gbto.get_symmetry();
    }

    virtual const assignment_schedule<N, T> &get_schedule() const {

        return m_gbto.get_schedule();
    }

    //@}


    //! \name Implementation of libtensor::additive_gen_bto<N, bti_traits>
    //@{

    virtual void perform(gen_block_stream_i<N, bti_traits> &out) {

        m_gbto.perform(out);
    }

    virtual void perform(gen_block_tensor_i<N, bti_traits> &btb);

    virtual void perform(gen_block_tensor_i<N, bti_traits> &btb,
            const scalar_transf<T> &c);

    virtual void compute_block(
            bool zero,
            const index<N> &ib,
            const tensor_transf<N, T> &trb,
            dense_tensor_wr_i<N, T> &blkb);

    virtual void compute_block(
            const index<N> &ib,
            dense_tensor_wr_i<N, T> &blkb) {

        compute_block(true, ib, tensor_transf<N, T>(), blkb);
    }

    //@}

    /** \brief Convenience wrapper to function 
            \c perform(gen_block_tensor_i<N, bti_traits> &, const scalar_transf<T>&)
        \param btb Result vlock tensor
        \param c Factor
     **/
    void perform(block_tensor_i<N, T> &btb, T c);

};


} // namespace libtensor

#endif // LIBTENSOR_TOD_COPY_H