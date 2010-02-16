#ifndef LIBTENSOR_TOD_DIAG_TEST_H
#define LIBTENSOR_TOD_DIAG_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/**	\brief Tests the libtensor::tod_diag class

	\ingroup libtensor_tests
**/
class tod_diag_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
};

} // namespace libtensor

#endif // LIBTENSOR_TOD_DIAG_TEST_H