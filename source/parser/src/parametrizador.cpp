// Descriptor ESF con downsampling + diff. Alto y Ancho -->


#include <iostream>
#include "../../utils/include/utils.hpp"

#include "../include/parametrizador.hpp"

Parametro::Parametro(){

}

std::string
Parametro::getNombre()
{
  return nombre;
}

void
Parametro::setNombre(std::string valor)
{
  nombre = valor;
}

void
Parametro::setEsOpcional(bool b)
{
  es_opcional = b;
}

void
Parametro::setValorEsperado(std::string valor)
{
  valor_esperado = valor;
}

Parametrizador::Parametrizador(){
}

void
Parametrizador::agregar(Parametro p)
{
  parametros.push_back(p);
}

std::vector<Parametro>
Parametrizador::getParametros()
{
  return parametros;
}
