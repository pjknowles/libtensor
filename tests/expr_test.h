#ifndef LIBTENSOR_EXPR_TEST_H
#define LIBTENSOR_EXPR_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {

/**	\brief Tests various problematic expressions

	\ingroup libtensor_tests
 **/
class expr_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	void test_1() throw(libtest::test_exception);
	void test_2() throw(libtest::test_exception);

};

} // namespace libtensor

#endif // LIBTENSOR_EXPR_TEST_H
