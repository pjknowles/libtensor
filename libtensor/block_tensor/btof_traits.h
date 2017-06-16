#ifndef LIBTENSOR_BTOF_TRAITS_H
#define LIBTENSOR_BTOF_TRAITS_H

#include <libtensor/core/allocator.h>
#include <libtensor/dense_tensor/dense_tensor_i.h>
#include <libtensor/dense_tensor/dense_tensor.h>
#include <libtensor/dense_tensor/tod.h>
#include <libtensor/block_tensor/btod_contract2_clst_optimize.h>
#include <libtensor/block_tensor/block_tensor.h>
#include <libtensor/block_tensor/block_tensor_ctrl.h>
#include <libtensor/block_tensor/block_tensor_i_traits.h>
#include <libtensor/block_tensor/bto_traits.h>

namespace libtensor {


//template<size_t N, size_t M, size_t K> class tod_contract2;
//template<size_t N> class tod_set;

template<>
struct bto_traits<float> {

    //! Element type
    typedef float element_type;

    //! Block tensor interface traits
    typedef block_tensor_i_traits<float> bti_traits;

    //! Type of temporary block tensor
    template<size_t N>
    struct temp_block_tensor_type {
        typedef block_tensor< N, float, allocator<float> > type;
    };

    template<size_t N>
    struct temp_block_type {
        typedef dense_tensor< N, float, allocator<float> > type;
    };

    template<size_t N>
    struct to_add_type {
        typedef to_add<N, float> type; 
    };

    template<size_t N>
    struct to_compare_type {
        typedef to_compare<N, float> type;
    };

/*    template<size_t N, size_t M, size_t K>
    struct to_contract2_type {
        typedef to_contract2<N, M, K, float> type;
        typedef btod_contract2_clst_optimize<N, M, K> clst_optimize_type;
    };*/

    template<size_t N>
    struct to_copy_type {
        typedef to_copy<N, float> type;
    };

/*    template<size_t N, size_t M>
    struct to_diag_type {
        typedef tod_diag<N, M> type;
    };

    template<size_t N, size_t M>
    struct to_dirsum_type {
        typedef tod_dirsum<N, M> type;
    };

    template<size_t N>
    struct to_dotprod_type {
        typedef tod_dotprod<N> type;
    };

    template<size_t N, size_t M, size_t K>
    struct to_ewmult2_type {
        typedef tod_ewmult2<N, M, K> type;
    };

    template<size_t N, size_t M>
    struct to_extract_type {
        typedef tod_extract<N, M> type;
    };
*/
    template<size_t N>
    struct to_mult_type {
        typedef to_mult<N, float> type;
    };

    template<size_t N>
    struct to_mult1_type {
        typedef to_mult1<N, float> type;
    };

    template<size_t N>
    struct to_random_type {
        typedef to_random<N, float> type;
    };
/*
    template<size_t N>
    struct to_scale_type {
        typedef tod_scale<N> type;
    };

    template<size_t N, size_t M>
    struct to_scatter_type {
        typedef tod_scatter<N, M> type;
    };

    template<size_t N, typename ComparePolicy>
    struct to_select_type {
        typedef tod_select<N, ComparePolicy> type;
    };

    template<size_t N>
    struct to_set_diag_type {
        typedef tod_set_diag<N> type;
    };

    template<size_t N>
    struct to_set_elem_type {
        typedef tod_set_elem<N> type;
    };
*/
    template<size_t N>
    struct to_set_type {
        typedef to_set<N, float> type;
    };

/*    template<size_t N>
    struct to_size_type {
        typedef tod_size<N> type;
    };

    template<size_t N>
    struct to_trace_type {
        typedef tod_trace<N> type;
    };

    template<size_t N>
    struct to_vmpriority_type {
        typedef tod_vmpriority<N> type;
    };*/

    static bool is_zero(float d) {
        return d == 0.0;
    }

    static bool is_zero(const scalar_transf<float> &d) {
        return is_zero(d.get_coeff());
    }

    static float zero() {
        return 0.0;
    }

    static float identity() {
        return 1.0;
    }

};


} // namespace libtensor

#endif // LIBTENSOR_BTOF_TRAITS_H
