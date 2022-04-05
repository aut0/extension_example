#include "common_extension.h"
#include "Target.h"
#include <iostream>

Target::Target(const sc_core::sc_module_name& nm)
    : sc_core::sc_module(nm)
    , socket_("target") {
    socket_.register_b_transport(this, &Target::b_transport);
}

void Target::b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t) {
    int cpuid = tx_cpuid(trans);
    int lvl = tx_level(trans);
    bool is_excl = tx_is_excl(trans);
    bool is_lock = tx_is_lock(trans);

    std::cout << "Received trans.: CPU ID " << cpuid
              << " LEVEL " << lvl
              << " EXCL " << (is_excl ? "true" : "false")
              << " LOCK " << (is_lock ? "true" : "false")
              << std::endl;
}