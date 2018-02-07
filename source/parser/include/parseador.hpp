// Clases: 
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string.h>
#include <boost/algorithm/string.hpp>
#include <json/json.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"

#include "../../utils/include/utils.hpp"
#include "../../parser/include/parametrizador.hpp"

#ifndef Parseador_DEF
#define Parseador_DEF
class Parseador
{

public:
  //Constructor
  Parseador();

  int
  find_argument (int argc, char** argv, const char* argument_name);

  std::vector<int>
  parse_file_extension_argument (int argc, char** argv, const std::string &extension);
  //parse (int argc, char** argv, const char* argument_name, Type& value);
//private:

};
#endif

#ifndef ParseadorConsole_DEF
#define ParseadorConsole_DEF
class ParseadorConsole
{
public:
  //Constructor
  ParseadorConsole();

  ~ParseadorConsole();

  int
  find_argument (int argc, char** argv, const char* argument_name);
  /*
  Parameters from console:
  - program name
    - json file
  */

};
#endif

#ifndef ParseadorJSON_DEF
#define ParseadorJSON_DEF
class ParseadorJSON : public Parseador
{
public:
  //Constructor
  ParseadorJSON();

  ~ParseadorJSON();
  /* Var utilizadas por API JSON */
  Json::CharReaderBuilder reader;
  Json::Value root;
  std::string errs;
  std::ifstream file;
  /* Fin var utilizadas por API JSON */
  /* Var utilizadas por RAPIDJSON */
  rapidjson::Document d;
  /* Fin var utilizadas por RAPIDJSON */

  bool
  open(char *filename);
  
  bool
  openRapid(char *filename);
  
  Json::Value
  get_element(char *filename);
  
  std::string
  get_element_rapid(char *filename);
  
  bool
  parser_rapid(Parametrizador *p, std::unordered_map<std::string, std::string>& values);

};
#endif
