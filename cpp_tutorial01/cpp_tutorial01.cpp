#include <cstdio>
#include <cstdlib>
#include "lept.h"

static int mainRet = 0;
static int testCount = 0;
static int testPass = 0;

//通过时计数，不通过是输出提示信息
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

//传入两个值，调用 EXEXPECT_EQ_BASE()
//第一个参数为两个值是否相等，第二个参数为 EXPECT_EQ_INT 的第一个参数
//第三个参数为 EXPECT_EQ_INT 的第二个参数，第四个参数为输出的类型
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

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

static void testParseExpectValue() {
    LeptValue val1(LeptType::LEPT_DEFAULT);
    Lept test1("", val1);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_EXPECT_VALUE, test1.parse());
    EXPECT_EQ_INT(LeptType::LEPT_NULL, test1.getType());

    LeptValue val2(LeptType::LEPT_DEFAULT);
    Lept test2(" ", val2);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_EXPECT_VALUE, test2.parse());
    EXPECT_EQ_INT(LeptType::LEPT_NULL, test2.getType());
}

static void testParseInvalidValue() {
    LeptValue val1(LeptType::LEPT_DEFAULT);
    Lept test1("nul", val1);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_INVALID_VALUE, test1.parse());
    EXPECT_EQ_INT(LeptType::LEPT_NULL, test1.getType());

    LeptValue val2(LeptType::LEPT_DEFAULT);
    Lept test2("?", val2);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_INVALID_VALUE, test2.parse());
    EXPECT_EQ_INT(LeptType::LEPT_NULL, test2.getType());
}

static void testParseRootNotSingular() {
    LeptValue val(LeptType::LEPT_DEFAULT);
    Lept test("null x", val);

    EXPECT_EQ_INT(LeptState::LEPT_PARSE_ROOT_NOT_SINGULAR, test.parse());
    EXPECT_EQ_INT(LeptType::LEPT_NULL, test.getType());
}

static void testParse() {
    testParseNull();
    testParseTrue();
    testParseFalse();
    testParseExpectValue();
    testParseInvalidValue();
    testParseRootNotSingular();
}

int main(){
    testParse();
    printf("%d/%d (%3.2f%%) passed\n", testPass, testCount, testPass * 100.0 / testCount);

    return 0;
}