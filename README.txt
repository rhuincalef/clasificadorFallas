Requisitos:

	Probado en Manjaro kernel 4.14.16-1-MANJARO con:
		CMAKE 3.10.2-2
		JSONCPP 1.8.4-2
		SQLITE 3.22.0-1
		BOOST 1.66.0-1
		VTK 8.0.1.4
		PCL 1.8.1

Compilación:
	Compilar con cmake
	$ mkdir build
	$ cd build
	$ cmake ..
	$ make

Ejecución:
	# editar archivo por defecto config_pipeline.json-default
	$ ./mainPipeLine -f archivo.json

Uso con crontab:
	
	Crear archivo de configuración de crontab /etc/crontab.miArchivo
		$ sudo crontab /etc/crontab.miArchivo
	
	Configurar una entrada que especifique la frecuencia de ejecución del script de Pipeline como se detalla a continuación:
		# Entrada cada 5 minutos
		*/5 * * * * root path/build/mainPipeLine -f path/config_pipeline.json >> /tmp/tesina_log.txt

	Reiniciar servicio de crontab:
	Ubuntu :
		$ sudo service cron restart
	Manjaro:
		$ sudo systemctl restart cronie
