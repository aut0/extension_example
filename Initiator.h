#ifndef EXTENSION_EXAMPLE_INITIATOR_H
#define EXTENSION_EXAMPLE_INITIATOR_H

#include <systemc>
#include <tlm_utils/simple_initiator_socket.h>

class Initiator : public sc_core::sc_module {
public:
    Initiator(const sc_core::sc_module_name& nm, uint16_t id);
    Initiator() = delete;
    Initiator(const Initiator&) = delete;

    tlm_utils::simple_initiator_socket<Initiator> socket_;

private:
    void simulate();

    uint16_t id_;
};


#endif //EXTENSION_EXAMPLE_INITIATOR_H
