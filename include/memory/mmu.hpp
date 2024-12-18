#pragma once

#include "memory.hpp"
#include "hart.hpp"

uint64_t GetVPN0 (uint64_t vaddr)  { 
    return (vaddr & VPAGE_VPN_0_MASK) >> 12; 
}
uint64_t GetVPN1 (uint64_t vaddr)  { 
    return (vaddr & VPAGE_VPN_1_MASK) >> 21; 
}
uint64_t GetVPN2 (uint64_t vaddr)  { 
    return (vaddr & VPAGE_VPN_2_MASK) >> 30; 
}
uint64_t GetVPN3 (uint64_t vaddr)  { 
    return (vaddr & VPAGE_VPN_3_MASK) >> 39; 
}

enum class SATP_MODE: int64_t {
    SV39 = int64_t(3) << 60,
    SV48 = int64_t(4) << 60,
    SV57 = int64_t(5) << 60,
};
uint64_t get_mode(size_t bit_ad) {
    if(bit_ad == 39) return static_cast<int64_t>(SATP_MODE::SV39);
    if(bit_ad == 48) return static_cast<int64_t>(SATP_MODE::SV48);
    if(bit_ad == 57) return static_cast<int64_t>(SATP_MODE::SV57);
}

uint64_t* create_page_table_lvl(int lvl, uint64_t vpn, uint64_t* current_page_table, int nested_transitions, Hart &hart) {
    uint64_t VPN_i = (vpn >> 9 * (nested_transitions - lvl)) & ((1 << 9) - 1);
        //if(i == 2) std::cout << (VPN >> 9 * (nested_ransitions - i)) << " = " << (VPN >> 9) << " * " << (nested_transitions - i) << " " << ((1 << 9) - 1) << "\n";
        if (current_page_table[VPN_i] == 0) {
            current_page_table[VPN_i] = hart.get_clean_pages_from_memory(1);
        }
        //std::cout << current_page_table[VPN_i] << "\n";
        return reinterpret_cast<uint64_t *>(hart.get_mem_host_addr(current_page_table[VPN_i]));
}

void prepare_page_table(Hart &hart, uint64_t root_page_addr) {
    hart.set_satr_val(get_mode(39));
    uint64_t prep_mem = hart.get_clean_pages_from_memory(0x900);
    for (uint64_t i = 0; i < 0x900; ++i) {
        uint64_t vaddr = i << 12;
        uint64_t paddr = prep_mem + DEFAULT_ALLOC_PAGES_SIZE * i;

        static int nested_transitions = (static_cast<int64_t>(hart.get_satr_val() & (uint64_t(0xFFFF) << 60)) >> 60) - 1;
        uint64_t* current_page_table = 
            reinterpret_cast<uint64_t *>(hart.get_mem_host_addr((hart.get_satr_val() & (int64_t(1) << 44) - 1) << 12));
        uint64_t* ppn_0 = create_page_table_lvl(0, GetVPN0(vaddr), current_page_table, nested_transitions, hart);
        uint64_t* ppn_1 = create_page_table_lvl(1, GetVPN0(vaddr), ppn_0, nested_transitions, hart);
        
        ppn_1[GetVPN0(vaddr) & ((1 << 9) - 1)] = paddr + (F_X | F_R | F_W);

        //if(i == 0x8FF) {
        //    hart->setReg(2, vaddr - 4);
        //}
    }
}