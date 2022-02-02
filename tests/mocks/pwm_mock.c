#include "static/pwm.h"
#include "pwm_mock.h"

extern MockPwm mock_pwm;    /* This is just a declaration! The actual
                                   mock obj must be defined globally in your
                                   test file. */

int ioctl(const char* path, const void* buf, size_t buf_size)
{
    return mock_pwm.ioctl(const char* path, const void* buf, size_t buf_size);
}