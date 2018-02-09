// Clases: DBManager

#include <iostream>
#include <vector>
#include <string.h>
#include <sqlite3.h>

#include "../../utils/include/utils.hpp"

#ifndef TRowFalla_DEF
#define TRowFalla_DEF
typedef struct RowFalla
{
	int id_base;
	int id_falla;
	std::string nombre_falla;
} TRowFalla;
#endif

#ifndef DBManager_DEF
#define DBManager_DEF

class DBManager
{

public:
  //Constructor
  DBManager();

  bool
  abrirConexion(std::string file_name);

  bool
  cerrarConexion();

  bool
  estaProcesada(int id_falla, std::string nombre_falla);

private:
  sqlite3 *db;

  std::vector<RowFalla>
  execQueryByIdFalla(int id_falla);
  
};
#endif
