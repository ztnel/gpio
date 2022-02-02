/**
 * @file pwm_mock.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */
#include <gmock/gmock.h>
#include "static/errors.h"

class PwmInterface {
  public:
    virtual ~PwmInterface() {}
    virtual pwm_code ioctl(const char* path, const void* buf, size_t buf_size) = 0;
};

class MockPwm : public PwmInterface {
  public:
    virtual ~MockPwm() {}
    MOCK_METHOD(pwm_code, ioctl, (const char* path, const void* buf, size_t buf_size));
};