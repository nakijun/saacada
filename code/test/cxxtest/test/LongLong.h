#include <cxxtest/TestSuite.h>

//
// This tests CxxTest's handling of "long long"
//

class LongLong : public CxxTest::TestSuite
{
public:
    void testLongLong()
    {
        TS_ASSERT_EQUALS( (long long)1, (long long)2 );
        TS_ASSERT_DIFFERS( (long long)3, (long long)3 );
        TS_ASSERT_LESS_THAN( (long long)5, (long long)4 );
    }
};

//
// Local Variables:
// compile-command: "perl test.pl"
// End:
//
