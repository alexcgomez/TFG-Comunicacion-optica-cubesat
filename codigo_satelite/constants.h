#ifndef CONSTANTS_H_	// Evitamos que se añada dos veces el mismo código
#define CONSTANTS_H_

// Otros defines
	#define TITLE						0
	#define LINE_1						1
	#define LINE_2						2

// Title
	#define MAX_TITLE_SIZE          	24 // Size 24. Field 1. Title.
		#define TITLE_INIT				0
		#define TITLE_END				(MAX_TITLE_SIZE-1)
		
// Line 1 & 2 ( posiciones )
	#define LINE_NUM                	0  // Field 1.  					Size 1. Line number.
	#define SAT_CATALOG_NUM         	2  // Field 2.  					Size 4. Satellite catalog number.
	#define CHECKSUM					68 // Field 14(line 1)  10(line 2). Size 1. Checksum (modulo 10).

// Line 1
	#define CLASS                   	7  // Field 3.  Size 1. Classification (U=Unclassified, C=Classified, S=Secret)
			CLASS_UNCLASSIFIED			'U'
			CLASS_CLASSIFIED			'C'
			CLASS_SECRET				'S'
			
	#define INTER_DES_LAUNCH_YEAR   	9  // Field 4.  Size 2.  International designator (last 2 digits of launch year)
	#define INTER_DES_YEAR_NUMBER   	11 // Field 5.  Size 3.  International designator (launch number of the year)
	#define INTER_DES_PLACE_LAUNCH  	14 // Field 6.  Size 3.  International designator (piece of the launch)
	#define EPOCH_YEAR              	18 // Field 7.  Size 2.  (last two digits of year)
	#define EPOCH_DAY_YEAR_FRAC     	20 // Field 8.  Size 12. (day of the year and fractional portion of the day)
	#define FIRST_DERIV_MEAN_MOTION		33 // Field 9.  Size 10. First Derivative of Mean Motion aka the Ballistic Coefficient
	#define SECOND_DERIV_MEAN_MOTION	44 // Field 10. Size 8.  Second Derivative of Mean Motion (decimal point assumed)
	#define DRAG_TERM					53 // Field 11. Size 8.  Drag Term aka Radiation Pressure Coefficient or BSTAR (decimal point assumed)
	#define EPHEMERIS_TYPE				62 // Field 12. Size 1.  Ephemeris type (internal use only - always zero in distributed TLE data)
	#define ELEM_SET_NUMBER				64 // Field 13. Size 4.  Element set number. Incremented when a new TLE is generated for this object.
 
// Line 2
	#define INTER_DES_LAUNCH_YEAR   	9  // Field 2.  Size 5.  Satellite Catalog number
	#define INTER_DES_LAUNCH_YEAR   	9  // Field 3.  Size 7.  Inclination (degrees)
	#define INTER_DES_LAUNCH_YEAR   	9  // Field 4.  Size 8.  Right Ascension of the Ascending Node (degrees)
	#define INTER_DES_YEAR_NUMBER   	11 // Field 5.  Size 7.  Eccentricity (decimal point assumed)
	#define INTER_DES_PLACE_LAUNCH  	14 // Field 6.  Size 8.  Argument of Perigee (degrees)
	#define EPOCH_YEAR              	18 // Field 7.  Size 8.  Mean Anomaly (degrees)
	#define EPOCH_DAY_YEAR_FRAC     	20 // Field 8.  Size 11. Mean Motion (revolutions per day)
	#define FIRST_DERIV_MEAN_MOTION		33 // Field 9.  Size 5.  Revolution number at epoch (revolutions)
	
#endif
