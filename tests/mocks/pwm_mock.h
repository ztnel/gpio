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

#include <memory>
#include <gmock/gmock.h>
#include "static/errors.h"

class MockPwm : public PwmInterface {
  public:
    virtual ~MockPwm() {}
    MOCK_METHOD(pwm_code, ioctl, (const char* path, const void* buf, size_t buf_size));
};

class TestFixture: public ::testing::Test{
  public:
    TestFixture() {
      mock_pwm.reset(new ::testing::NiceMock<MockPwm>());
    }
    ~TestFixture() {
      mock_pwm.reset();
    }
    virtual void SetUp(){}
    virtual void TearDown(){}
    // pointer for accessing mocked library
    static std::unique_ptr<MockPwm> mock_pwm;
};

class PwmInterface {
  public:
    virtual ~PwmInterface() {};
    virtual pwm_code ioctl(const char* path, const void* buf, size_t buf_size) = 0;
};

