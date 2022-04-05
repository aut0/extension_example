#include "Initiator.h"
#include "Target.h"
#include <systemc>

int sc_main(int argc, char* argv[]) {
    Initiator initiator("Initiator", 1);
    Target target("target");

    initiator.socket_.bind(target.socket_);

    sc_core::sc_start(1, sc_core::SC_MS);

    return 0;
}