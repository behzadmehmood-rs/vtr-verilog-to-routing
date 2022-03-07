#ifndef EDIFPARSE_H
#define EDIFPARSE_H
/*
 * libedifparse - Kevin E. Murray 2016
 *
 * Released under MIT License see LICENSE.txt for details.
 *
 * OVERVIEW
 * --------------------------
 * This library provides support for parsing Berkely Logic Interchange Format (edif)
 * files. It supporst the features required to handle basic netlists (e.g. .model,
 * .inputs, .outputs, .subckt, .names, .latch)
 *
 * USAGE
 * --------------------------
 * Define a callback derived from the edifparse::Callback interface, and pass it
 * to one of the edifparse::edif_parse_*() functions.
 *
 * The parser will then call the various callback methods as it encouters the
 * appropriate parts of the netlist.
 *
 * See main.cpp and edif_pretty_print.hpp for example usage.
 *
 */
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <functional>
enum SNodeType {
  LIST,
  STRING,
  SYMBOL,
  INTEGER,
  FLOAT
};

struct SNode {
  struct SNode *next;
  enum SNodeType type;
  union {
    struct SNode *list;
    char *value;
  };
};

namespace edifparse {


class Callback {
    public:
        virtual ~Callback() {}

        //Start of parsing
        virtual void start_parse() = 0;


        //Sets current filename
        virtual void filename(std::string fname) = 0;

        //Sets current line number
        virtual void lineno(int line_num) = 0;

        //Start of a .model
        virtual void begin_model(std::string model_name) = 0;


        //End of parsing
        virtual void finish_parse() = 0;

        //Error during parsing
      //  virtual void parse_error(const int curr_lineno, const std::string& near_text, const std::string& msg) = 0;
};


/*
 * External functions for loading an SDC file
 */
void edif_parse_filename(std::string filename, Callback& callback);
void edif_parse_filename(const char* filename, Callback& callback);

//Loads from 'edif'. 'filename' only used to pass a filename to callback and can be left unspecified
void edif_parse_file(FILE* edif, Callback& callback, const char* filename="");
struct SNode *snode_parse(FILE *filename, Callback& callback);
void snode_free(struct SNode *node);

} //namespace

#endif
