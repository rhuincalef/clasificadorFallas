// Descriptor ESF con downsampling + diff. Alto y Ancho -->
#include "../../utils/include/utils.hpp"

#include "../include/parseador.hpp"

Parseador::Parseador()
{
}

int
Parseador::find_argument (int argc, char** argv, const char* argument_name)
{
  for (int i = 1; i < argc; ++i)
  {
    // Search for the string
    if (strcmp (argv[i], argument_name) == 0)
    {
      return (i);
    }
  }
  return (-1);
}

std::vector<int>
Parseador::parse_file_extension_argument (int argc, char** argv, const std::string &extension)
{
  std::vector<int> indices;
  for (int i = 1; i < argc; ++i)
  {
    std::string fname = std::string (argv[i]);
    std::string ext = extension;

    // Needs to be at least 4: .ext
    if (fname.size () <= 4)
      continue;

    // For being case insensitive
    std::transform (fname.begin (), fname.end (), fname.begin (), tolower);
    std::transform (ext.begin (), ext.end (), ext.begin (), tolower);

    // Check if found
    std::string::size_type it;
    if ((it = fname.rfind (ext)) != std::string::npos)
    {
      // Additional check: we want to be able to differentiate between .p and .png
      if ((ext.size () - (fname.size () - it)) == 0)
        indices.push_back (i);
    }
  }
  return (indices);
}

ParseadorJSON::ParseadorJSON()
{
}

ParseadorJSON::~ParseadorJSON()
{
}

bool
ParseadorJSON::open(char *filename)
{
  bool ok = false;
  try {
    file.open(filename);
  }
  catch (const std::ifstream::failure& e) {
    return ok;
  }
  ok = Json::parseFromStream(reader, file, &root, &errs);
  return ok;
}

Json::Value
ParseadorJSON::get_element(char *key)
{
  return root.get(key, "defValue");
}
std::string
ParseadorJSON::get_element_rapid(char *key)
{
  rapidjson::Value::MemberIterator hello = d.FindMember(key);
  return hello->value.GetString();
}

bool
ParseadorJSON::openRapid(char *filename)
{
  bool ok = false;
  try {
    file.open(filename);
  }
  catch (const std::ifstream::failure& e) {
    return ok;
  }
  rapidjson::IStreamWrapper isw(file);
  d.ParseStream(isw);
  ok = !d.HasParseError();
  file.close();
  return ok;
}

bool
ParseadorJSON::parser_rapid(Parametrizador *p, std::unordered_map<std::string, std::string>& values)
{
  static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
  // test Member root : {} from JSON
  if (not this->d.HasMember(p->getNombre().c_str()))
    return false;
  const rapidjson::Value &root = this->d[p->getNombre().c_str()];
  // testing cada valor del miembro root
  for (int i = 0; i < p->getCantParametros(); ++i)
  {
    Parametro param = p->getParametros()[i];
    char *nombre = (char *)malloc((sizeof param.getNombre().c_str() / sizeof param.getNombre().c_str()[0]) * sizeof(char));
    std::strcpy(nombre, param.getNombre().c_str());
    bool ok = root.HasMember(nombre);
    if (not ok && param.esRequerido())
      return false;
    if (not ok && not param.esRequerido())
      continue;
    switch (root[nombre].GetType())
    {
      case 6: // Number is a JSON type, but C++ needs more specific type.
        if (param.getValorEsperado().compare("float") == 0)
        {
          if (root[nombre].IsDouble())
            values.emplace(param.getNombre(), std::to_string(root[nombre].GetDouble()));
          else
            return false;
        }
        if (param.getValorEsperado().compare("int") == 0)
        {
          if (root[nombre].IsInt()) // In this case, IsUint()/IsInt64()/IsUInt64() also return true.
            values.emplace(param.getNombre(), std::to_string(root[nombre].GetInt()));
          else
            return false;
        }
        break;
      case 5:
        values.emplace(param.getNombre(), root[nombre].GetString());
        break;
      default:
        return false;
        break;
    }
  }
  return true;
}
