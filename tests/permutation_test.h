#ifndef __LIBTENSOR_PERMUTATION_TEST_H
#define __LIBTENSOR_PERMUTATION_TEST_H

#include <libtest.h>

namespace libtensor {

template<class Perm>
class permutation_test : public libtest::unit_test {
public:
	virtual void perform() throw(libtest::test_exception);

private:
	//! Tests the constructors
	void test_ctor() throw(libtest::test_exception);

	//! Tests the permute method
	void test_permute() throw(libtest::test_exception);

	//! Tests the invert method
	void test_invert() throw(libtest::test_exception);

	//! Tests exceptions in the apply method
	void test_apply() throw(libtest::test_exception);
};

template<class Perm>
void permutation_test<Perm>::perform() throw(libtest::test_exception) {
	test_ctor();
	test_permute();
	test_apply();
}

template<class Perm>
void permutation_test<Perm>::test_ctor() throw(libtest::test_exception) {
	char sc[8];
	int si[8];

	// Order = 2

	Perm p2(2);
	if(!p2.is_identity()) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "!p2.is_identity()");
	}
	strcpy(sc, "ij");
	p2.apply(2, sc);
	if(strncmp(sc, "ij", 2)) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "New permutation is not identity (char, 2)");
	}
	for(int i=0; i<8; i++) si[i]=i;
	p2.apply(2, si);
	if(si[0]!=0 || si[1]!=1) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "New permutation is not identity (int, 2)");
	}

	Perm p2a(p2);
	if(!p2a.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p2a.is_identity()");
	if(!p2a.equals(p2)) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p2a.equals(p2)");
	strcpy(sc, "ij");
	p2a.apply(2, sc);
	if(strncmp(sc, "ij", 2))
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
		__LINE__, "Permutation copy is not identity (char, 2)");
	for(int i=0; i<8; i++) si[i]=i;
	p2a.apply(2, si);
	if(si[0]!=0 || si[1]!=1)
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
		__LINE__, "Permutation copy is not identity (int, 2)");

	// Order = 3

	Perm p3(3);
	if(!p3.is_identity()) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "!p3.is_identity()");
	}
	strcpy(sc, "ijk");
	p3.apply(3, sc);
	if(strncmp(sc, "ijk", 3)) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "New permutation is not identity (char, 3)");
	}
	for(int i=0; i<8; i++) si[i]=i;
	p3.apply(3, si);
	if(si[0]!=0 || si[1]!=1 || si[2]!=2) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "New permutation is not identity (int, 3)");
	}

	Perm p3a(p3);
	if(!p3a.is_identity()) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "!p3a.is_identity()");
	}
	if(!p3a.equals(p3)) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "!p3a.equals(p3)");
	}
	strcpy(sc, "ijk");
	p3a.apply(3, sc);
	if(strncmp(sc, "ijk", 3)) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "Permutation copy is not identity (char, 3)");
	}
	for(int i=0; i<8; i++) si[i]=i;
	p3a.apply(3, si);
	if(si[0]!=0 || si[1]!=1 || si[2]!=2) {
		fail_test("permutation_test<Perm>::test_ctor()", __FILE__,
			__LINE__, "Permutation copy is not identity (int, 3)");
	}

	// Order = 4

	Perm p4(4);
	if(!p4.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p4.is_identity()");

	Perm p4a(p4);
	if(!p4a.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p4a.is_identity()");
	if(!p4a.equals(p4)) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p4a.equals(p4)");

	Perm p5(5);
	if(!p5.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p5.is_identity()");

	Perm p5a(p5);
	if(!p5a.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p5a.is_identity()");
	if(!p5a.equals(p5)) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p5a.equals(p5)");

	Perm p6(6);
	if(!p6.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p6.is_identity()");
	Perm p6a(p6);
	if(!p6a.is_identity()) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p6a.is_identity()");
	if(!p6a.equals(p6)) fail_test("permutation_test<Perm>::test_ctor()",
		__FILE__, __LINE__, "!p6a.equals(p6)");
}

template<class Perm>
void permutation_test<Perm>::test_permute() throw(libtest::test_exception) {
	Perm p2(2);

	char s2[8]; strcpy(s2, "ij");
	int i2[8]; i2[0] = 100; i2[1] = 200;

	p2.permute(0,1);
	p2.apply(2, s2);
	if(strncmp(s2, "ji", 2)) {
		fail_test("permutation_test<Perm>::test_permute()",
			__FILE__, __LINE__, "[0,1] permutation failed in char");
	}
	p2.apply(2, i2);
	if(i2[0]!=200  || i2[1]!=100) {
		fail_test("permutation_test<Perm>::test_permute()",
			__FILE__, __LINE__, "[0,1] permutation failed in int");
	}
	p2.permute(0,1);
	if(!p2.is_identity()) {
		fail_test("permutation_test<Perm>::test_permute()", __FILE__,
			__LINE__, "Double permutation not recognized");
	}
	strcpy(s2, "ij");
	i2[0] = 100; i2[1] = 200;
	p2.apply(2, s2);
	if(strncmp(s2, "ij", 2)) {
		fail_test("permutation_test<Perm>::test_permute()", __FILE__,
			__LINE__, "[0,1] double permutation failed in char");
	}
	p2.apply(2, i2);
	if(i2[0]!=100 || i2[1]!=200) {
		fail_test("permutation_test<Perm>::test_permute()", __FILE__,
			__LINE__, "[0,1] double permutation failed in int");
	}

	Perm p4(4);
	char s4[8];

	p4.permute(0,1).permute(2,3);
	strcpy(s4, "ijkl");
	p4.apply(4, s4);
	if(strncmp(s4, "jilk", 4)) {
		fail_test("permutation_test<Perm>::test_permute()", __FILE__,
			__LINE__, "[0,1]+[2,3] permutation failed in char");
	}

	bool ok = false;
	try {
		p4.permute(1,5);
	} catch(exception e) {
		ok = true;
	} catch(...) {
		fail_test("permutation_test<Perm>::test_permute()",
			__FILE__, __LINE__, "Incorrect exception type");
	}
	if(!ok) {
		fail_test("permutation_test<Perm>::test_permute()", __FILE__,
			__LINE__, "Expected an exception, it was missing");
	}

}

template<class Perm>
void permutation_test<Perm>::test_invert() throw(libtest::test_exception) {
}

template<class Perm>
void permutation_test<Perm>::test_apply() throw(libtest::test_exception) {
	bool ok = false;
	Perm p2(2), p4(4);
	char s2[8], s4[8];
	strcpy(s2, "ijkl"); strcpy(s4, "ijkl");

	ok = false;
	try {
		p2.apply(2, s2);
		ok = true;
	} catch(...) {
	}
	if(!ok) fail_test("permutation_test<Perm>::test_apply()",
		__FILE__, __LINE__, "Unexpected exception");

	ok = false;
	try {
		p2.apply(4, s2);
	} catch(exception e) {
		ok = true;
	} catch(...) {
		fail_test("permutation_test<Perm>::test_apply()",
			__FILE__, __LINE__, "Incorrect exception type");
	}
	if(!ok) fail_test("permutation_test<Perm>::test_apply()",
		__FILE__, __LINE__, "Expected an exception, it was missing");

	ok = false;
	try {
		p4.apply(4, s4);
		ok = true;
	} catch(...) {
	}
	if(!ok) fail_test("permutation_test<Perm>::test_apply()",
		__FILE__, __LINE__, "Unexpected exception");

	ok = false;
	try {
		p4.apply(2, s4);
	} catch(exception e) {
		ok = true;
	} catch(...) {
		fail_test("permutation_test<Perm>::test_apply()",
			__FILE__, __LINE__, "Incorrect exception type");
	}
	if(!ok) fail_test("permutation_test<Perm>::test_apply()",
		__FILE__, __LINE__, "Expected an exception, it was missing");
}

}

#endif // __LIBTENSOR_PERMUTATION_TEST_H

