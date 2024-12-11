#pragma once

static const int BYTE_SIZE  = sizeof(uint8_t);
static const int HWORD_SIZE = sizeof(uint16_t);
static const int WORD_SIZE  = sizeof(uint32_t);
static const int DWORD_SIZE = sizeof(uint64_t);

static const int DEFAULT_MEM_SIZE   = 1 << 30;


//--------------------FOR VADDR--------------------
static const int VPAGE_SIZE         = 1 << 12;
static const int VPAGE_OFFSET_MASK  = VPAGE_SIZE - 1;


//--------------------FOR PTE--------------------
static constexpr dword_t mask_xz    = bitops::Ones<63, 54>(); // пока не реализовала для чего
static constexpr dword_t mask_ppn   = bitops::Ones<53, 10>(); // PPN = Physical page number
static constexpr dword_t mask_rsw   = bitops::Ones<9, 8>(); // is reserved for use by supervisor software
static constexpr dword_t mask_d     = bitops::Ones<7, 7>(); // dirty: not implemented yet
static constexpr dword_t mask_a     = bitops::Ones<6, 6>(); // accessed: not implemented yet
static constexpr dword_t mask_g     = bitops::Ones<5, 5>(); // global mapping: not implemented yet
static constexpr dword_t mask_u     = bitops::Ones<4, 4>(); // page is accessible to user mode: not implemented yet
static constexpr dword_t mask_x     = bitops::Ones<3, 3>(); // executable
static constexpr dword_t mask_w     = bitops::Ones<2, 2>(); // write
static constexpr dword_t mask_r     = bitops::Ones<1, 1>(); // read
static constexpr dword_t mask_v     = bitops::Ones<0, 0>(); // whether the PTE is valid