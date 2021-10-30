#pragma once

#include <stddef.h>
#include <stdint.h>

int tap_alloc(char *dev);

int tap_read(uint8_t *buf, size_t buf_size);