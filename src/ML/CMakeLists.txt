
# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (estrategiaClasificacion estrategiaClasificacion.cpp)

# Se agregan los directorios de PCL y se linkean las librerias de PCL a la libreria actual
#target_include_directories (estrategiaClasificacion PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PCL_INCLUDE_DIRS})
#target_link_libraries(estrategiaClasificacion ${PCL_LIBRARY_DIRS})
