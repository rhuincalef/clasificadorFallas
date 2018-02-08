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
  setEsRequerido(bool b);

  bool
  esRequerido() const;
  
  void
  setValorEsperado(std::vector<std::string> valor);

  std::vector<std::string>
  getValorEsperado() const;

  void
  setTipoValorEsperado(std::string valor);

  std::string
  getTipoValorEsperado() const;

private:
  std::string nombre;
  bool es_requerido = true;
  std::vector<std::string> valor_esperado;
  std::string tipo_valor_esperado;

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

  int
  getCantParametros();

  std::string
  getNombre();

  void
  setNombre(std::string nombre);

private:
  std::vector<Parametro> parametros;
  std::string nombre_;

};
#endif
