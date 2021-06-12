#include <cstdio>
#include <cstdlib>
#include "lept.h"

static int mainRet = 0;
static int testCount = 0;
static int testPass = 0;

//通过时计数，不通过时输出提示信息
#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        testCount++;\
        if (equality)\
            testPass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            mainRet = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")

static void testParseNull() {
    LeptValue val(LeptType::LEPT_DEFAULT);
    Lept test("null", val);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_OK, test.parse());
    EXPECT_EQ_INT(LeptType::LEPT_NULL, test.getType());
}

static void testParseTrue() {
    LeptValue val(LeptType::LEPT_DEFAULT);
    Lept test("true", val);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_OK, test.parse());
    EXPECT_EQ_INT(LeptType::LEPT_TRUE, test.getType());
}

static void testParseFalse() {
    LeptValue val(LeptType::LEPT_DEFAULT);
    Lept test("false", val);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_OK, test.parse());
    EXPECT_EQ_INT(LeptType::LEPT_FALSE, test.getType());
}

#define TEST_NUMBER(expect, json)\
    do {\
        LeptValue val(LeptType::LEPT_DEFAULT);\
        Lept test(json, val);\
        EXPECT_EQ_INT(LeptState::LEPT_PARSE_OK, test.parse());\
        EXPECT_EQ_INT(LeptType::LEPT_NUMBER, test.getType());\
        EXPECT_EQ_DOUBLE(expect, test.getNumber());\
    } while(0)

static void test_parse_number() {
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    TEST_NUMBER(0.0, "1e-10000"); /* must underflow */

    TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); /* the smallest number > 1 */
    TEST_NUMBER(4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
    TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    TEST_NUMBER(2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
    TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    TEST_NUMBER(2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
    TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    TEST_NUMBER(1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
    TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

#define TEST_ERROR(error, json)\
    do {\
        LeptValue val(LeptType::LEPT_DEFAULT);\
        Lept test(json, val);\
        EXPECT_EQ_INT(error, test.parse());\
        EXPECT_EQ_INT(LeptType::LEPT_NULL, test.getType());\
    } while(0)

static void testParseExpectValue() {
    TEST_ERROR(LeptState::LEPT_PARSE_EXPECT_VALUE, "");
    TEST_ERROR(LeptState::LEPT_PARSE_EXPECT_VALUE, " ");
}

static void testParseInvalidValue() {
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "nul");
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "?");

    /* invalid number */
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "+0");
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "+1");
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "INF");
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "inf");
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "NAN");
    TEST_ERROR(LeptState::LEPT_PARSE_INVALID_VALUE, "nan");
}

static void testParseRootNotSingular() {
    TEST_ERROR(LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR, "null x");

    /* invalid number */
    TEST_ERROR(LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR, "0123"); /* after zero should be '.' or nothing */
    TEST_ERROR(LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0");
    TEST_ERROR(LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123");
}

static void testParseNumberTooBig() {
    TEST_ERROR(LeptState::LEPT_PARSE_NUMBER_TOO_BIG, "1e309");
    TEST_ERROR(LeptState::LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
}

static void testParse() {
    testParseNull();
    testParseTrue();
    testParseFalse();
    testParseExpectValue();
    testParseInvalidValue();
    testParseRootNotSingular();
    testParseNumberTooBig();
}

int main(){
    testParse();
    printf("%d/%d (%3.2f%%) passed\n", testPass, testCount, testPass * 100.0 / testCount);

    return 0;
}