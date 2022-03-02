/**
 * @file
 * @brief BLIF Netlist Loader
 *
 * This loader handles loading a post-technology mapping fully flattened (i.e not
 * hierarchical) netlist in Berkely Logic Interchange Format (BLIF) file, and
 * builds a netlist data structure (AtomNetlist) from it.
 *
 * BLIF text parsing is handled by the blifparse library, while this file is responsible
 * for creating the netlist data structure.
 *
 * The main object of interest is the BlifAllocCallback struct, which implements the
 * blifparse callback interface.  The callback methods are then called when basic blif
 * primitives are encountered by the parser.  The callback methods then create the associated
 * netlist data structures.
 */
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <unordered_set>
#include <cctype> //std::isdigit

#include "blifparse.hpp"
#include "atom_netlist.h"

#include "vtr_assert.h"
#include "vtr_util.h"
#include "vtr_log.h"
#include "vtr_logic.h"
#include "vtr_time.h"
#include "vtr_digest.h"

#include "vpr_types.h"
#include "vpr_error.h"
#include "globals.h"
#include "read_blif.h"
#include "arch_types.h"
#include "echo_files.h"
#include "hash.h"


void read_verilog() {
    std::cout<< "ADDING SUPPORT FOR VERILOG NETLISTS";
}
