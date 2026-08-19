#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <cstdint>

namespace mem {

class TLBTranslator {
public:

    TLBTranslator(int vpn_bits)
        : offset_bits_(32 - vpn_bits)
        , offset_mask_((1u << (32 - vpn_bits)) - 1)
    { }

    void add_entry(uint32_t vpn, uint32_t pfn)
    {
        map_[vpn] = pfn;
    }

    uint32_t translate(uint32_t virtual_addr) const
    {
        uint32_t vpn = virtual_addr >> offset_bits_;
        uint32_t offset = virtual_addr & offset_mask_;
        auto it = map_.find(vpn);
        if (it == map_.end())
        {
            throw std::out_of_range("TLB miss");
        }
        return (it->second << offset_bits_) | offset;
    }

private:
    int offset_bits_;
    uint32_t offset_mask_;
    std::unordered_map<uint32_t, uint32_t> map_;
};

} // namespace mem

int main()
{
    // vpn_bits = 20  ->  12-bit offset (4 KB pages)
    mem::TLBTranslator tlb(20);

    tlb.add_entry(1, 5);    // VPN 1 -> PFN 5
    tlb.add_entry(2, 10);   // VPN 2 -> PFN 10

    std::cout << std::hex << std::uppercase;
    std::cout << "0x" << tlb.translate(0x00001ABC) << "\n";  // expect 0x5ABC
    std::cout << "0x" << tlb.translate(0x00002FFF) << "\n";  // expect 0xAFFF

    try {
        tlb.translate(0x00003000);   // VPN 3 not mapped -> miss
    } catch (const std::out_of_range& e) {
        std::cout << "TLB miss caught: " << e.what() << "\n";
    }

    return 0;
}