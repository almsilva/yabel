/*
 * Following the offical Boost.Test documentation, the following two lines must
 * only befined once per project. Even if you opt to not use this sample file,
 * keep this requirement in mind.
 *
 * Source: https://www.boost.org/doc/libs/1_67_0/libs/test/doc/html/boost_test/usage_variants.html
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Sandbox

#include <boost/test/unit_test.hpp>
#include "sample.hpp"

BOOST_AUTO_TEST_SUITE(Sandbox_Sample)

BOOST_AUTO_TEST_CASE(return_true)
{
	Sandbox::Sample sample;
	BOOST_CHECK(sample.return_true());
}
BOOST_AUTO_TEST_SUITE_END()
