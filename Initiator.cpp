#include "common_extension.h"
#include "Initiator.h"

Initiator::Initiator(const sc_core::sc_module_name &nm, uint16_t id) :
    sc_core::sc_module(nm),
    socket_("socket"),
    id_(id) {
    // nothing to do
    SC_HAS_PROCESS(Initiator);
    SC_THREAD(simulate);
}

void Initiator::simulate() {
    tlm::tlm_generic_payload trans;
    sc_core::sc_time t;

    tlm_sbi sbi = sbi_cpuid(id_) ;
    tx_set_sbi(trans, sbi);

    socket_->b_transport(trans, t);

    sbi |= SBI_EXCL;
    tx_set_sbi(trans, sbi);
    socket_->b_transport(trans, t);

    sbi |= SBI_LOCK;
    tx_set_sbi(trans, sbi);
    socket_->b_transport(trans, t);

    sbi.level = 3;
    tx_set_sbi(trans, sbi);
    socket_->b_transport(trans, t);
}