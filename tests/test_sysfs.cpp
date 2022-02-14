/**
 * @file test_sysfs.cpp
 * @author your name (you@domain.com)
 * @brief unittests for sysfs module
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */



#include <gtest/gtest.h>
#include <fff.h>

extern "C" {
  #include <merase.h>
  #include "sysfs.h"
}

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC1(int, close, int);
FAKE_VALUE_FUNC3(ssize_t, write, int, const void*, size_t);
FAKE_VALUE_FUNC_VARARG(int, open, const char *, int, ...);
FAKE_VOID_FUNC1(logger_set_level, Level);
FAKE_VOID_FUNC_VARARG(_trace, const char*, ...);
FAKE_VOID_FUNC_VARARG(_error, const char*, ...);
FAKE_VOID_FUNC_VARARG(_warning, const char*, ...);
FAKE_VOID_FUNC_VARARG(_critical, const char*, ...);
FAKE_VOID_FUNC_VARARG(_info, const char*, ...);

class TestSysfs : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(write);
      RESET_FAKE(close);
      RESET_FAKE(open);
      FFF_RESET_HISTORY();
    }
};

TEST_F(TestSysfs, IoctlBadArgs) {
  int ret_code;
  ret_code = ioctl(NULL, "1", 2);
  ASSERT_EQ(ret_code, 1);
  ret_code = ioctl("/", NULL, 2);
  ASSERT_EQ(ret_code, 1);
  ret_code = ioctl("/", "1", 0);
  ASSERT_EQ(ret_code, 1);
}

TEST_F(TestSysfs, IoctlSuccess) {
  int ret_code;
  int mock_open_ret = 1;
  open_fake.return_val = mock_open_ret;
  ret_code = ioctl("/", "1", 2);
  ASSERT_EQ(ret_code, 0);
}

TEST_F(TestSysfs, IoctlCloseFailure) {
  int ret_code;
  close_fake.return_val = -1;
  ret_code = ioctl("/", "1", 2);
  ASSERT_EQ(ret_code, 1);
}

TEST_F(TestSysfs, Int64toStr) {
  size_t size;
  uint64_t value = 64;
  char *buf = int64_to_str(value, &size);
  ASSERT_EQ(strcmp(buf, "64"), 0);
  free_buffer(buf);
}