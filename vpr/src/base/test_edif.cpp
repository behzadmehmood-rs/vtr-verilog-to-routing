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
/*const t_model* blk_model = .... //Initialize the block model appropriately

AtomNetlist& netlist("my_netlist"); //Initialize the netlist with name 'my_netlist'

 //Create the first block
 BlockId blk1 = netlist.create_block("block_1", blk_model);

 //Create the first block's output port
 //  Note that the input/output/clock type of the port is determined
 //  automatically from the block model
 PortId blk1_out = netlist.create_port(blk1, "B");

 //Create the net
 NetId net1 = netlist.create_net("net1");

 //Associate the net with blk1
 netlist.create_pin(blk1_out, 0, net1, PinType::DRIVER);

 //Create block 2 and hook it up to net1
 BlockId blk2 = netlist.create_block("block_2", blk_model);
 PortId blk2_in = netlist.create_port(blk2, "A");
 netlist.create_pin(blk2_in, 0, net1, PinType::SINK);

 //Create block 3 and hook it up to net1
 BlockId blk3 = netlist.create_block("block_3", blk_model);
 PortId blk3_in = netlist.create_port(blk3, "A");
 netlist.create_pin(blk3_in, 0, net1, PinType::SINK);*/

std::vector<AtomNetlist> test_models_;
const t_model* inpad_model_;
const t_model* outpad_model_;
AtomNetlist main_netlist_;
AtomNetlist& curr_model() {


        return test_models_[test_models_.size() - 1];
    }

    const t_model* find_model(std::string name) {
        const t_model* arch_model = nullptr;
        const t_model* user_arch_models_ = nullptr;
        const t_model* library_arch_models_ = nullptr;
        for (const t_model* arch_models : {user_arch_models_, library_arch_models_}) {
            arch_model = arch_models;
            while (arch_model) {
                if (name == arch_model->name) {
                    //Found it
                    break;
                }
                arch_model = arch_model->next;
            }
            if (arch_model) {
                //Found it
                break;
            }
        }
        return arch_model;
    }
    AtomNetlist test() {
	 //std::string  name="blo"
	 AtomNetlist netlist("my_netlist");

	 inpad_model_=find_model("block");
	 //outpad_model_ = find_model(MODEL_OUTPUT);
	 printf("\n\n\n entering the test function \n \n \n");
	 const t_model* blk_model = find_model(MODEL_INPUT);
	 const t_model_ports* model_port = blk_model->outputs;
	 VTR_ASSERT(model_port->name == std::string("B"));
	//std::string pin_name = blk_model->outputs->name;
	// blk_model->outputs->name="B";
	 AtomBlockId blk_id = netlist.create_block("block", blk_model);
	 AtomPortId out_port = netlist.create_port(blk_id, model_port);
	 AtomNetId net_id = netlist.create_net("net1");
	 //netlist.create_pin(port_id, 0, net_id, PinType::DRIVER);
	 const std::string&  block_name=netlist.block_name(blk_id);
	 printf("Associate block is given as: %s\n",block_name.c_str());
	 const std::string& net_name=netlist.net_name(net_id);
	 printf("Associate net is given as: %s\n",net_name.c_str());

	 	 /*	 std::string pin_name = blk_model->outputs->name;

	            AtomBlockId blk_id = curr_model().AtomNetlist(rhs)("block", blk_model);

	            netlist.block_type(blk_id);
	            AtomPortId  = curr_model().block_input_ports(blk_id)
	            AtomPortId
	            AtomNetId net_id = curr_model().create_net("net1");
	            curr_model().create_pin(port_id, 0, net_id, PinType::DRIVER);

     /*   VTR_ASSERT_MSG(!blk_model->inputs, "Inpad model has an input port");
        VTR_ASSERT_MSG(blk_model->outputs, "Inpad model has no output port");
        VTR_ASSERT_MSG(blk_model->outputs->size == 1, "Inpad model has non-single-bit output port");
        VTR_ASSERT_MSG(!blk_model->outputs->next, "Inpad model has multiple output ports");*/

     /*   std::string pin_name = blk_model->outputs->name;
        for (const auto& input : input_names) {
            AtomBlockId blk_id = netlist.create_block(input, blk_model);
            AtomPortId port_id = netlist.create_port(blk_id, blk_model->outputs);
            AtomNetId net_id = netlist.create_net(input);
            netlist.create_pin(port_id, 0, net_id, PinType::DRIVER);
        }*/
        //set_curr_block(AtomBlockId::INVALID()); //This statement doesn't define a block, so mark invalid*/
	 return netlist;
    }

