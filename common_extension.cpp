#include "common_extension.h"

tlm::tlm_extension_base* sbiext::clone() const {
    return new sbiext(*this);
}

void sbiext::copy_from(const tlm_extension_base& ext) {
    if (typeid(this) != typeid(ext)) {
        std::perror("cannot copy extension");
        return;
    }
    const sbiext& other = (const sbiext&)ext;
    code                = other.code;
}

void tx_set_sbi(tlm::tlm_generic_payload& tx, const tlm_sbi& info) {
    if (!tx_has_sbi(tx) && info == SBI_NONE)
        return;
    if (!tx_has_sbi(tx))
        tx.set_extension<sbiext>(new sbiext());
    sbiext* ext = tx.get_extension<sbiext>();
    ext->code   = info.code;
}

void tx_set_cpuid(tlm::tlm_generic_payload& tx, int id) {
    tlm_sbi info;
    info.cpuid = id;
    if (info.cpuid != id) {
        std::perror("coreid too large");
        return;
    }
    tx_set_sbi(tx, SBI_NONE | info);
}

void tx_set_level(tlm::tlm_generic_payload& tx, int lvl) {
    tlm_sbi info;
    info.level = lvl;
    if (info.level != lvl) {
        std::perror("privlvl too large");
        return;
    }
    tx_set_sbi(tx, SBI_NONE | info);
}