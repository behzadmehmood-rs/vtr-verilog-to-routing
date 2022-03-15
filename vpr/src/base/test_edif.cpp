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
#include "test_edif.h"
#include "netlist.h"

AtomNetlist test() {
    t_model* blk_model; //Initialize the block model appropriately
    blk_model = new t_model;

    AtomNetlist netlist("my_netlist"); //Initialize the netlist with name 'my_netlist'

    //Create the first block
    AtomBlockId blk1 = netlist.create_block("block_1", blk_model);
    char* out_port = (char*)"B";
    t_model_ports* outputs;
    outputs = new t_model_ports;
    blk_model->outputs = outputs;
    outputs->name = out_port;
    blk_model->outputs->dir = OUT_PORT;
    blk_model->outputs->size = 2;
    blk_model->outputs->min_size = 0;

    //Create the first block's output port
    //  Note that the input/output/clock type of the port is determined
    //  automatically from the block model
    AtomPortId blk1_out = netlist.create_port(blk1, blk_model->outputs);

    //Create the net
    AtomNetId net1 = netlist.create_net("net1");

    //Associate the net with blk1
    netlist.create_pin(blk1_out, 0, net1, PinType::DRIVER);
    const std::string& out_blk = netlist.block_name(blk1);
    const std::string& output_port = netlist.port_name(blk1_out);
    const std::string& net = netlist.net_name(net1);
    printf(" block created is given as::%s\n", out_blk.c_str());
    printf(" port created is given as::%s\n", output_port.c_str());
    printf("NET is given as::%s\n", net.c_str());
    t_model_ports* inputs;
    inputs = new t_model_ports;
    char* in_port = (char*)"A";
    blk_model->inputs = inputs;
    inputs->name = in_port;
    blk_model->inputs->dir = IN_PORT;
    blk_model->inputs->size = 2;
    blk_model->inputs->min_size = 0;

    //Create block 2 and hook it up to net1
    AtomBlockId blk2 = netlist.create_block("block_2", blk_model);
    AtomPortId blk2_in = netlist.create_port(blk2, blk_model->inputs);
    netlist.create_pin(blk2_in, 0, net1, PinType::SINK);
    const std::string& in_blk = netlist.block_name(blk2);
    const std::string& input_port = netlist.port_name(blk2_in);
    printf(" block created is given::%s\n", in_blk.c_str());
    printf(" port created is given as::%s\n", input_port.c_str());

    //Create block 3 and hook it up to net1
    AtomBlockId blk3 = netlist.create_block("block_3", blk_model);
    AtomPortId blk3_in = netlist.create_port(blk3, blk_model->inputs);
    netlist.create_pin(blk3_in, 0, net1, PinType::SINK);
    const std::string& in2_blk = netlist.block_name(blk3);
    const std::string& input2_port = netlist.port_name(blk3_in);
    printf(" block created is given::%s\n", in2_blk.c_str());
    printf(" port created is given as::%s\n", input2_port.c_str());

    return netlist;
}
