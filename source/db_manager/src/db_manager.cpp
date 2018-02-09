#include "../include/db_manager.hpp"

DBManager::DBManager()
{
}

bool
DBManager::abrirConexion(std::string file_name)
{
	int rc;
	sqlite3_initialize();
	//rc = sqlite3_open_v2( file_name.c_str(), &this->db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );
	rc = sqlite3_open_v2( file_name.c_str(), &this->db, SQLITE_OPEN_READWRITE, NULL );
	if ( rc != SQLITE_OK) {
	    sqlite3_close( this->db );
	    return false;
	}
	return true;
}

bool
DBManager::cerrarConexion()
{
	if (sqlite3_close(this->db) == SQLITE_OK)
	{
		sqlite3_shutdown();
		return true;
	}
	return false;
}

bool
DBManager::estaProcesada(int id_falla, std::string nombre_falla)
{
	std::vector<TRowFalla> rows;
	rows = this->execQueryByIdFalla(id_falla);
	for (std::vector<TRowFalla>::iterator i = rows.begin(); i != rows.end(); ++i)
	{
		if (i->nombre_falla == nombre_falla)
			return true;
	}
	return false;
}

std::vector<TRowFalla>
DBManager::execQueryByIdFalla(int id_falla)
{
	int rc;
	int id_base;
	char *data = NULL;
	char *zErrMsg = 0;
	sqlite3_stmt    *stmt = NULL;
	std::vector<TRowFalla> rows;
	rc = sqlite3_prepare_v2( this->db, "select * from FALLA_PROCESADA where id_falla = ?", -1, &stmt, NULL);
    if ( rc != SQLITE_OK)
    	return rows;
    sqlite3_bind_int(stmt, 1, id_falla);
    while( sqlite3_step( stmt ) == SQLITE_ROW ) {
        TRowFalla tr;
        id_base = (int)sqlite3_column_int( stmt, 0);
        id_falla = (int)sqlite3_column_int( stmt, 2);
        data = (const char*)sqlite3_column_text( stmt, 1);
        tr.id_base = id_base;
        tr.id_falla = id_falla;
        tr.nombre_falla = data;
        rows.push_back(tr);
    }
    sqlite3_finalize( stmt );
    return rows;
}
