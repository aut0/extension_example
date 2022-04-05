#ifndef EXTENSION_EXAMPLE_TARGET_H
#define EXTENSION_EXAMPLE_TARGET_H

#include <systemc>
#include <tlm_utils/simple_target_socket.h>

class Target : public sc_core::sc_module {
public:
    Target(const sc_core::sc_module_name&);
    Target() = delete;
    Target(const Target&) = delete;

    tlm_utils::simple_target_socket<Target> socket_;

private:
    void b_transport(tlm::tlm_generic_payload&, sc_core::sc_time&);
};


#endif //EXTENSION_EXAMPLE_TARGET_H
