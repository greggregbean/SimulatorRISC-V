#include "memory.hpp"
    
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

uint64_t create_page_table_lvl (uint64_t lvl, uint64_t vpn, Memory &memory) {
    uint64_t pte;
    memory.mem_load (lvl * VPAGE_SIZE + vpn, &pte, sizeof(uint64_t));

    if (!(pte & VALID_MASK)) {
        uint64_t clean_page = memory.get_clean_page();
        pte = (pte & ~PPN_MASK) | (clean_page << 10) | 1;
        return pte;
    }
    else {
        return (pte & PPN_MASK) >> 10;
    }
}