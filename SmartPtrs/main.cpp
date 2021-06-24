#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MyUnique_ptr.h"
#include "CObject.h"
#include "MyShared_ptr.h"

#include <memory>

TEST_CASE("testing MyUnique_ptr") {
	{
		MyUnique_ptr p1;
		CHECK(!p1);
		CHECK(p1.get() == nullptr);
		p1.release();
		CHECK(!p1);
		CHECK(p1.get() == nullptr);
		p1.reset();
		CHECK(!p1);
		CHECK(p1.get() == nullptr);
	}
	{
		auto d = new DerivedObject;
		MyUnique_ptr empty, from_reset, from_ctor(d);
		from_reset.reset(d);
		CHECK(from_reset);
		CHECK(from_ctor);
		CHECK(from_reset.get() == from_ctor.get());

		CHECK(from_reset.get() == from_ctor.get());
		CHECK(from_reset.get() != empty.get());
		empty = MyUnique_ptr(new DerivedObject);
		CHECK(from_reset.get() == from_ctor.get());
		CHECK(from_reset.get() != empty.get());
		from_ctor.release();
		CHECK(!from_ctor);
	}
	{
		MyUnique_ptr p1(new CObject);
		auto cObjectPtr = p1.get();
		MyUnique_ptr p2(std::move(p1));
		CHECK(p2.get() == cObjectPtr);
		CHECK(!p1);
		p1 = std::move(p2);
		CHECK(p1.get() == cObjectPtr);
		CHECK(!p2);

		p2 = MyUnique_ptr(new DerivedObject);
		auto cObjectPtr2 = p2.get();
		CHECK(p1.get() == cObjectPtr);
		CHECK(p2.get() == cObjectPtr2);
		p1.swap(p2);
		CHECK(p1.get() == cObjectPtr2);
		CHECK(p2.get() == cObjectPtr);
	}
	{
		MyUnique_ptr p1(new CObject);
		MyUnique_ptr p2(new DerivedObject);
		CHECK(p1->foo() == "foo");
		CHECK((*p2).foo() == "derived foo");
	}
}

TEST_CASE("testing MyShared_ptr") {
	{
		auto obj = new CObject;
		MyShared_ptr ptr(obj);
		CHECK(ptr.get() == obj);
		MyShared_ptr ptr2(std::move(ptr));
		CHECK(ptr2.get() == obj);
		CHECK(ptr.get() == nullptr);
		MyShared_ptr ptr3;
		CHECK(ptr3.get() == nullptr);
		ptr3 = std::move(ptr2);
		CHECK(ptr3.get() == obj);
	}
	{
		MyShared_ptr ptr;
		CHECK(ptr.use_count() == 0);
		ptr.reset();
		CHECK(ptr.use_count() == 0);
		ptr.reset(new DerivedObject);
		CHECK(ptr.use_count() == 1);
		{
			MyShared_ptr ptr2(ptr);
			CHECK(ptr.use_count() == 2);
		}
		CHECK(ptr.use_count() == 1);
		{
			MyShared_ptr ptr2 = ptr;
			CHECK(ptr.use_count() == 2);
		}
		CHECK(ptr.use_count() == 1);
		MyShared_ptr base_ptr(new CObject);
		CHECK(ptr.use_count() == 1);
		CHECK(base_ptr.use_count() == 1);
	}
}