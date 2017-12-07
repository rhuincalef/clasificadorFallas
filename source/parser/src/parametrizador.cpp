// Descriptor ESF con downsampling + diff. Alto y Ancho -->


#include <iostream>
#include "../../utils/include/utils.hpp"

#include "../include/parametrizador.hpp"

Parametro::Parametro(){

}

std::string
Parametro::getNombre()
{
  return this->nombre;
}

void
Parametro::setNombre(std::string valor)
{
  this->nombre = valor;
}

void
Parametro::setEsOpcional(bool b)
{
  this->es_opcional = b;
}

void
Parametro::setValorEsperado(std::string valor)
{
  this->valor_esperado = valor;
}

Parametrizador::~Parametrizador()
{
  this->parametros.clear();
}

Parametrizador::Parametrizador()
{
  this->parametros.clear();
}

void
Parametrizador::agregar(Parametro p)
{
  this->parametros.push_back(p);
}

std::vector<Parametro>
Parametrizador::getParametros()
{
  return this->parametros;
}

std::string
Parametrizador::getNombre()
{
  return this->nombre_;
}

void
Parametrizador::setNombre(std::string nombre)
{
  this->nombre_ = nombre;
}
