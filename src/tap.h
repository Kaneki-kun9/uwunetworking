#pragma once

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

int tap_alloc(char *dev);

ssize_t tap_read(int fd, uint8_t *buf, size_t buf_size);