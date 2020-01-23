#ifndef TLE_DRIVERS_H_	// Evitamos que se añada dos veces el mismo código
#define TLE_DRIVERS_H_

// Defines ( constantes )
	#define MAX_LINES       3
	#define MAX_BUFFER_SIZE 69

// Definición de pines y otras partes del HW
	#define PIN_EMISOR_LASER 		6
	//#define PIN_RECEPTOR_LASER	x // usar pin con IRQ por HW (pin 2?)


// Clases
	class TLE_DRIVER
	{
		public:
			char TLE_buffer[MAX_LINES][MAX_BUFFER_SIZE];
		
			void init();
			void write( char *texto_write, int num_linea );
			void read( char *texto_read, int num_linea ); // No devolver el string con un return, suele dar problemas con el stack
		
		private:

	};

#endif
