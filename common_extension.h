#ifndef EXTENSION_EXAMPLE_COMMON_EXTENSION_H
#define EXTENSION_EXAMPLE_COMMON_EXTENSION_H

#include <tlm>

struct tlm_sbi {
    union {
        uint64_t code;
        struct {
            bool is_excl : 1;
            bool is_lock : 1;

            int cpuid : 20;
            int level : 20;
        };
    };

    tlm_sbi()               = default;
    tlm_sbi(const tlm_sbi&) = default;
    tlm_sbi(tlm_sbi&&)      = default;

    tlm_sbi(bool excl, bool lock, int cpu = 0, int lvl = 0) :
        is_excl(excl),
        is_lock(lock),
        cpuid(cpu),
        level(lvl) {}

    tlm_sbi& operator=(const tlm_sbi& other);
    tlm_sbi& operator&=(const tlm_sbi& other);
    tlm_sbi& operator|=(const tlm_sbi& other);

    tlm_sbi operator&(const tlm_sbi& other) const;
    tlm_sbi operator|(const tlm_sbi& other) const;

    bool operator==(const tlm_sbi& other) const;
    bool operator!=(const tlm_sbi& other) const;
};

// Fit extension payload into one register
static_assert(sizeof(tlm_sbi) == sizeof(uint64_t), "tlm_sbi size too large");

inline tlm_sbi& tlm_sbi::operator=(const tlm_sbi& other) {
    code = other.code;
    return *this;
}

inline tlm_sbi& tlm_sbi::operator&=(const tlm_sbi& other) {
    code &= other.code;
    return *this;
}

inline tlm_sbi& tlm_sbi::operator|=(const tlm_sbi& other) {
    code |= other.code;
    return *this;
}

inline tlm_sbi tlm_sbi::operator&(const tlm_sbi& other) const {
    tlm_sbi result(*this);
    return result &= other;
}

inline tlm_sbi tlm_sbi::operator|(const tlm_sbi& other) const {
    tlm_sbi result(*this);
    return result |= other;
}

inline bool tlm_sbi::operator==(const tlm_sbi& other) const {
    return code == other.code;
}

inline bool tlm_sbi::operator!=(const tlm_sbi& other) const {
    return code != other.code;
}

const tlm_sbi SBI_NONE  = {false, false};
const tlm_sbi SBI_EXCL  = {true, false};
const tlm_sbi SBI_LOCK  = {false, true};

inline tlm_sbi sbi_cpuid(int cpu) {
    return tlm_sbi(false, false, cpu, 0);
}

inline tlm_sbi sbi_level(int lvl) {
    return tlm_sbi(false, false, 0, lvl);
}

class sbiext : public tlm::tlm_extension<sbiext>, public tlm_sbi
{
public:
    sbiext() = default;

    virtual tlm_extension_base* clone() const override;
    virtual void copy_from(const tlm_extension_base& ext) override;
};

inline bool tx_has_sbi(const tlm::tlm_generic_payload& tx) {
    return tx.get_extension<sbiext>() != nullptr;
}

inline const tlm_sbi& tx_get_sbi(const tlm::tlm_generic_payload& tx) {
    return tx_has_sbi(tx) ? *tx.get_extension<sbiext>() : SBI_NONE;
}

inline bool tx_is_excl(const tlm::tlm_generic_payload& tx) {
    return tx_get_sbi(tx).is_excl;
}

inline bool tx_is_lock(const tlm::tlm_generic_payload& tx) {
    return tx_get_sbi(tx).is_lock;
}

inline int tx_cpuid(const tlm::tlm_generic_payload& tx) {
    return tx_get_sbi(tx).cpuid;
}

inline int tx_level(const tlm::tlm_generic_payload& tx) {
    return tx_get_sbi(tx).level;
}

void tx_set_sbi(tlm::tlm_generic_payload& tx, const tlm_sbi& info);
void tx_set_cpuid(tlm::tlm_generic_payload& tx, int id);
void tx_set_level(tlm::tlm_generic_payload& tx, int lvl);

#endif //EXTENSION_EXAMPLE_COMMON_EXTENSION_H
