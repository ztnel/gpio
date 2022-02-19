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
  #include <stdio.h>
  #include <fcntl.h>
  #include <merase.h>
  #include <pthread.h>
  #include "sysfs.h"
}

DEFINE_FFF_GLOBALS;
// FAKE_VALUE_FUNC1(int, close, int);
// FAKE_VALUE_FUNC3(ssize_t, write, int, const void *, size_t);
// FAKE_VALUE_FUNC_VARARG(int, open, const char *, int, ...);
// FAKE_VOID_FUNC_VARARG(merase_log, enum Level, const char *, int, const char *, ...);
// FAKE_VALUE_FUNC1(int, pthread_mutex_lock, pthread_mutex_t *);
// FAKE_VALUE_FUNC1(int, pthread_mutex_unlock, pthread_mutex_t *);


class TestSysfs : public testing::Test {
  public:
    void SetUp() {
      // RESET_FAKE(write);
      // RESET_FAKE(close);
      // RESET_FAKE(open);
      // RESET_FAKE(pthread_mutex_lock);
      // RESET_FAKE(pthread_mutex_unlock);
      FFF_RESET_HISTORY();
    }
};

// TEST_F(TestSysfs, wctl_bad_args) {
//   int ret_code;
//   ret_code = wctl(NULL, "1", 2);
//   ASSERT_EQ(ret_code, EXIT_FAILURE);
//   ret_code = wctl("/", NULL, 2);
//   ASSERT_EQ(ret_code, EXIT_FAILURE);
//   ret_code = wctl("/", "1", 0);
//   ASSERT_EQ(ret_code, EXIT_FAILURE);
// }

// TEST_F(TestSysfs, wctl_success) {
//   open_fake.return_val = 1;
//   close_fake.return_val = 0;
//   int ret_code = wctl("/", "1", 2);
//   ASSERT_EQ(ret_code, EXIT_SUCCESS);
//   ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
//   ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
// }

// TEST_F(TestSysfs, wctl_open_failure) {
//   open_fake.return_val = -1;
//   int ret_code = wctl("/", "1", 2);
//   ASSERT_EQ(ret_code, EXIT_FAILURE);
//   ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
//   ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
// }

// TEST_F(TestSysfs, wctl_close_failure) {
//   close_fake.return_val = -1;
//   int ret_code = wctl("/", "1", 2);
//   ASSERT_EQ(ret_code, 1);
//   ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
//   ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
// }

// TEST_F(TestSysfs, Int64toStr) {
//   size_t size;
//   uint64_t value = 64;
//   char *buf = int64_to_str(value, &size);
//   ASSERT_EQ(strcmp(buf, "64"), 0);
//   free_buffer(buf);
// }
