#ifndef LIBTENSOR_SO_ADD_IMPL_LABEL_TEST_H
#define LIBTENSOR_SO_ADD_IMPL_LABEL_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {


/**	\brief Tests the libtensor::so_add_impl_label class

	\ingroup libtensor_tests_sym
 **/
class so_add_impl_label_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	static const char *k_table_id;

	void test_1() throw(libtest::test_exception);
	void test_2a() throw(libtest::test_exception);
	void test_2b() throw(libtest::test_exception);
	void test_3a() throw(libtest::test_exception);
	void test_3b() throw(libtest::test_exception);
	void test_3c() throw(libtest::test_exception);
	void test_4() throw(libtest::test_exception);
	void test_5a() throw(libtest::test_exception);
	void test_5b() throw(libtest::test_exception);
	void test_5c() throw(libtest::test_exception);

};


} // namespace libtensor

#endif // LIBTENSOR_SO_ADD_IMPL_LABEL_TEST_H

