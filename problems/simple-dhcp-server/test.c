#include "test.h"

#include "solution.c"

static void expectRequest(DHCPServerSys *sys, const char *mac,
                          const char *expected)
{
    char *actual = DHCPServerSysRequest(sys, mac);
    EXPECT_STRING_EQ(expected, actual);
    free(actual);
}

static void testExampleOne(void)
{
    DHCPServerSys *sys = DHCPServerSysCreate();

    expectRequest(sys, "AABBCCDDEEF1", "192.168.0.0");
    EXPECT_TRUE(DHCPServerSysRelease(sys, "AABBCCDDEEF1"));

    DHCPServerSysFree(sys);
}

static void testExampleTwo(void)
{
    DHCPServerSys *sys = DHCPServerSysCreate();

    expectRequest(sys, "AABBCCDDEEF1", "192.168.0.0");
    expectRequest(sys, "F2FBBCCDDEEF", "192.168.0.1");
    EXPECT_TRUE(DHCPServerSysRelease(sys, "AABBCCDDEEF1"));
    EXPECT_TRUE(DHCPServerSysRelease(sys, "F2FBBCCDDEEF"));
    expectRequest(sys, "333333333333", "192.168.0.2");
    expectRequest(sys, "F2FBBCCDDEEF", "192.168.0.1");

    DHCPServerSysFree(sys);
}

static void testRepeatedRequestAndInvalidRelease(void)
{
    DHCPServerSys *sys = DHCPServerSysCreate();

    expectRequest(sys, "000000000000", "192.168.0.0");
    expectRequest(sys, "000000000000", "192.168.0.0");
    EXPECT_TRUE(!DHCPServerSysRelease(sys, "111111111111"));
    EXPECT_TRUE(DHCPServerSysRelease(sys, "000000000000"));
    EXPECT_TRUE(!DHCPServerSysRelease(sys, "000000000000"));

    DHCPServerSysFree(sys);
}

static void testExhaustionAndReleasedAddressFallback(void)
{
    DHCPServerSys *sys = DHCPServerSysCreate();
    char mac[13];

    for (int i = 0; i < 256; ++i) {
        (void)snprintf(mac, sizeof(mac), "MAC%09d", i);
        char *actual = DHCPServerSysRequest(sys, mac);

        if (i == 0) {
            EXPECT_STRING_EQ("192.168.0.0", actual);
        } else if (i == 255) {
            EXPECT_STRING_EQ("192.168.0.255", actual);
        } else {
            EXPECT_TRUE(actual != NULL);
        }
        free(actual);
    }

    expectRequest(sys, "FULLPOOL0000", "NA");
    EXPECT_TRUE(DHCPServerSysRelease(sys, "MAC000000007"));
    expectRequest(sys, "NEWCLIENT001", "192.168.0.7");

    DHCPServerSysFree(sys);
}

static void testPreviousAddressPriority(void)
{
    DHCPServerSys *sys = DHCPServerSysCreate();

    expectRequest(sys, "AAAAAAAAAAAA", "192.168.0.0");
    expectRequest(sys, "BBBBBBBBBBBB", "192.168.0.1");
    EXPECT_TRUE(DHCPServerSysRelease(sys, "AAAAAAAAAAAA"));
    expectRequest(sys, "AAAAAAAAAAAA", "192.168.0.0");

    DHCPServerSysFree(sys);
}

int main(void)
{
    testExampleOne();
    testExampleTwo();
    testRepeatedRequestAndInvalidRelease();
    testExhaustionAndReleasedAddressFallback();
    testPreviousAddressPriority();
    return finishTests();
}
