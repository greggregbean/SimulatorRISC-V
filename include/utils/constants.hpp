#pragma once

#include <iostream>

static int BYTE_SIZE  = sizeof(uint8_t);
static int HWORD_SIZE = sizeof(uint16_t);
static int WORD_SIZE  = sizeof(uint32_t);
static int DWORD_SIZE = sizeof(uint64_t);


static int VPAGE_SIZE        = 1 << 12;
static int VPAGE_OFFSET_MASK = VPAGE_SIZE - 1;
static int DEFAULT_MEM_SIZE  = 1 << 25;