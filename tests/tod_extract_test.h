#ifndef LIBTENSOR_TOD_EXTRACT_TEST_H
#define LIBTENSOR_TOD_EXTRACT_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/**	\brief Tests the libtensor::tod_extract class

	\ingroup libtensor_tests
**/
class tod_extract_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	void test_1() throw(libtest::test_exception);
	void test_2() throw(libtest::test_exception);
	void test_3() throw(libtest::test_exception);
	void test_4() throw(libtest::test_exception);
	void test_5() throw(libtest::test_exception);
};

} // namespace libtensor

#endif // LIBTENSOR_TOD_EXTRACT_TEST_H
