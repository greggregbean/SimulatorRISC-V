#pragma once

static const int BYTE_SIZE  = sizeof(uint8_t);
static const int HWORD_SIZE = sizeof(uint16_t);
static const int WORD_SIZE  = sizeof(uint32_t);
static const int DWORD_SIZE = sizeof(uint64_t);

static const int DEFAULT_MEM_SIZE           = 1 << 25;
static const int DEFAULT_STACK_SIZE         = 1 << 5;
static const int DEFAULT_CACHE_SIZE         = 1 << 6;
static const int DEFAULT_ALLOC_PAGES_SIZE   = 0x1000;

static const uint64_t F_X = (1 << 0); // Executable flag
static const uint64_t F_W = (1 << 1); // Writable flag
static const uint64_t F_R = (1 << 2); // Readable flag

//--------------------FOR VADDR--------------------
static const uint64_t VPAGE_SIZE        = 1 << 12;
static const uint64_t VPAGE_OFFSET_MASK = VPAGE_SIZE - 1;
static const uint64_t VPAGE_VPN_0_MASK  = (1 << 21) - 1 - VPAGE_OFFSET_MASK;
static const uint64_t VPAGE_VPN_1_MASK  = (1 << 30) - 1 - VPAGE_VPN_0_MASK;
static const uint64_t VPAGE_VPN_2_MASK  = (1 << 39) - 1 - VPAGE_VPN_1_MASK;
static const uint64_t VPAGE_VPN_3_MASK  = (1 << 48) - 1 - VPAGE_VPN_2_MASK;

//--------------------FOR PTE--------------------
static const uint64_t VALID_MASK = 1 << 0;
static const uint64_t XZ_MASK    = (1 << 10) - 1 - VALID_MASK;   //я пока не нашла приминение
static const uint64_t PPN_MASK   = (1 << 54) - 1 - XZ_MASK;
