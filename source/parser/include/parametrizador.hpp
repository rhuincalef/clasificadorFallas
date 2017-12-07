// Clases: EstrategiaClasificacionMLAbstract, EstrategiaClasificacionSVM
#include <iostream>
#include <vector>
#include "../../utils/include/utils.hpp"

#ifndef Parametro_DEF
#define Parametro_DEF
class Parametro
{

public:
  //Constructor 
  Parametro();

  std::string
  getNombre();
  
  void
  setNombre(std::string valor);
  
  void
  setEsOpcional(bool b);
  
  void
  setValorEsperado(std::string valor);

private:
  std::string nombre;
  bool es_opcional = true;
  std::string valor_esperado;

};
#endif

#ifndef Parametrizador_DEF
#define Parametrizador_DEF
class Parametrizador
{

public:
  //Constructor
  Parametrizador();

  ~Parametrizador();

  void
  agregar(Parametro p);

  std::vector<Parametro>
  getParametros();

  std::string
  getNombre();

  void
  setNombre(std::string nombre);

private:
  std::vector<Parametro> parametros;
  std::string nombre_;

};
#endif
