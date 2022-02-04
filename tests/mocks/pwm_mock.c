#include "static/pwm.h"
#include "pwm_mock.h"

int ioctl(const char* path, const void* buf, size_t buf_size) {
    return mock_pwm.ioctl(const char* path, const void* buf, size_t buf_size);
}