#ifndef LIBTENSOR_DIRECT_BLOCK_TENSOR_TEST_H
#define LIBTENSOR_DIRECT_BLOCK_TENSOR_TEST_H

#include <libtest.h>

namespace libtensor {

/**	\brief Tests the libtensor::direct_block_tensor class

	\ingroup libtensor_tests
**/
class direct_block_tensor_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	void test_op_1() throw(libtest::test_exception);

};

} // namespace libtensor

#endif // LIBTENSOR_DIRECT_BLOCK_TENSOR_TEST_H

