/**
 * @file
 * @brief edif Netlist Loader
 *
 * This loader handles loading a post-technology mapping fully flattened (i.e not
 * hierarchical) netlist in Berkely Logic Interchange Format (edif) file, and
 * builds a netlist data structure (AtomNetlist) from it.
 *
 * edif text parsing is handled by the edifparse library, while this file is responsible
 * for creating the netlist data structure.
 *
 * The main object of interest is the edifAllocCallback struct, which implements the
 * edifparse callback interface.  The callback methods are then called when basic edif
 * primitives are encountered by the parser.  The callback methods then create the associated
 * netlist data structures.
 */
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sstream>
#include <unordered_set>
#include <cctype> //std::isdigit

#include "edifparse.h"
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
#include "read_edif.h"
#include "arch_types.h"
#include "echo_files.h"
#include "test_edif.h"
#include "hash.h"
struct EdifAllocCallback : public edifparse::Callback {
  public:
    EdifAllocCallback(e_circuit_format edif_format, AtomNetlist& main_netlist, const std::string netlist_id, const t_model* user_models, const t_model* library_models)
        : main_netlist_(main_netlist)
        , netlist_id_(netlist_id)
        , user_arch_models_(user_models)
        , library_arch_models_(library_models)
        , edif_format_(edif_format) {
        VTR_ASSERT(edif_format_ == e_circuit_format::EDIF);
       // inpad_model_ = find_model(MODEL_INPUT);
       // outpad_model_ = find_model(MODEL_OUTPUT);

        //main_netlist_.set_block_types(inpad_model_, outpad_model_);
    }
  public: //Callback interface
     void start_parse() override {}

     void finish_parse() override {
         //When parsing is finished we *move* the main netlist
         //into the user object. This ensures we never have two copies
         //(consuming twice the memory).
         //size_t main_netlist_idx = determine_main_netlist_index();
         //main_netlist_ = std::move(edif_models_[main_netlist_idx]);
     }

     void begin_model(std::string model_name) override {
         //Create a new model, and set it's name
    	// printf("EDIF FILE included===================== is %s",model_name);

         edif_models_.emplace_back(model_name, netlist_id_);
        // edif_models_.back().set_block_types(inpad_model_, outpad_model_);
         edif_models_black_box_.emplace_back(false);
         ended_ = false;
         //set_curr_block(AtomBlockId::INVALID()); //This statement doesn't define a block, so mark invalid
     }
     void filename(std::string fname) override { filename_ = fname; }

     void lineno(int line_num) override { lineno_ = line_num; }

  private:
     bool ended_ = true; //Initially no active .model
     std::string filename_ = "";
     int lineno_ = -1;

     std::vector<AtomNetlist> edif_models_;
     std::vector<bool> edif_models_black_box_;

     AtomNetlist& main_netlist_;    ///<User object we fill
     const std::string netlist_id_; ///<Unique identifier based on the contents of the edif file
     const t_model* user_arch_models_ = nullptr;
     const t_model* library_arch_models_ = nullptr;
     //const t_model* inpad_model_;
    // const t_model* outpad_model_;

     size_t unique_subckt_name_counter_ = 0;

     AtomBlockId curr_block_;
     std::vector<std::pair<AtomNetId, AtomNetId>> curr_nets_to_merge_;

     e_circuit_format edif_format_ = e_circuit_format::EDIF;
 };

void read_edif(e_circuit_format circuit_format,
                      const char* edif_file,
                      const t_model* user_models,
                      const t_model* library_models) {
    AtomNetlist netlist;
    //constexpr const char*  BLOCK1="BLOCK1";
    std::string netlist_id = vtr::secure_digest_file(edif_file);
    EdifAllocCallback alloc_callback(circuit_format, netlist, netlist_id, user_models, library_models);
    edifparse::edif_parse_filename(edif_file, alloc_callback);
    std::cout<<"Adding support for Edif\n";
    printf("EDIF FILE included is %s,",edif_file);

}
 
