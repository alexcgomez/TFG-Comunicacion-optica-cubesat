#ifndef TLE_PROTOCOL_HPP_	// Evitamos que se añada dos veces el mismo código
#define TLE_PROTOCOL_HPP_

// Defines ( constantes )
	#define MAX_LINES       3
	#define MAX_BUFFER_SIZE 69
	
class TLE
{
  public:
	  char TLE_buffer[MAX_LINES][MAX_BUFFER_SIZE];
	  
	  void init();
	  
// Title
	void set_title( char* _title);
	void get_title( char* _title); // No devolver el string con un return, suele dar problemas con el stack

// Line 1 & Line 2

// Line 1

// Line 2

  private:

};


#endif
