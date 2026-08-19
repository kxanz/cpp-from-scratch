# Address Translation 1

**Topic:** Computer Architecture / Operating Systems (Virtualization)

## Background

In modern operating systems, programs reference memory using **virtual addresses**. Before the CPU can fetch data from RAM, each virtual address must be translated to a **physical address**. The **Translation Lookaside Buffer (TLB)** is a small, fully-associative hardware cache that stores recent virtual-to-physical page mappings, making this translation cheap.

## How It Works

A 32-bit virtual address is split into two fields, determined by a configurable `vpn_bits` parameter:

```
 31                          (32 - vpn_bits)                    0
 ┌───────────────────────────┬──────────────────────────────────┐
 │  VPN  (vpn_bits wide)      │  Page Offset                      │
 └───────────────────────────┴──────────────────────────────────┘
```

- **VPN (Virtual Page Number)** — the upper `vpn_bits` bits. Used as the TLB lookup key.
- **Page Offset** — the lower `offset_bits = 32 - vpn_bits` bits. Copied unchanged into the physical address.

On a **TLB hit**, the corresponding **PFN (Physical Frame Number)** is retrieved and the physical address is assembled:

```cpp
Physical Address = (PFN << offset_bits) | offset
```

On a **TLB miss**, no mapping exists and an error is signalled.

## Task

Implement `TLBTranslator` with the following interface:

```cpp
TLBTranslator(int vpn_bits);
```

Constructs the translator. All addresses are 32-bit unsigned. The upper `vpn_bits` bits of any virtual address are the VPN; the lower `32 - vpn_bits` bits are the page offset.

```cpp
void add_entry(uint32_t vpn, uint32_t pfn);
```

Inserts a TLB entry mapping `vpn → pfn`. You may assume no duplicate VPNs are added.

```cpp
uint32_t translate(uint32_t virtual_addr) const;
```

Returns the physical address corresponding to `virtual_addr`. Throws `std::out_of_range` on a TLB miss.

## Example

With `vpn_bits = 20` (12-bit offset → 4 KB pages) and entries `{VPN 1 → PFN 5, VPN 2 → PFN 10}`:

| Virtual Address | VPN   | Offset | PFN | Physical Address |
|-----------------|-------|--------|-----|------------------|
| `0x00001ABC`    | `0x001` | `0xABC` | 5   | `0x00005ABC`     |
| `0x00002FFF`    | `0x002` | `0xFFF` | 10  | `0x0000AFFF`     |

## Constraints

- `1 ≤ vpn_bits ≤ 31`
- Up to 10,000 `add_entry` calls
- Up to 1,000,000 `translate` calls