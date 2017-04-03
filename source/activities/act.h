/*
 * act.h
 *
 * Created: 2012-11-22 3:38:31 PM
 *  Author: Justin
 */ 


#ifndef ACT_H_
#define ACT_H_

// Declare application activity ID
// Range from 0x0001 to 0x6FFF
// Range 0x70000 onward are for system activities (DO NOT USED)

//
// Local Activities ID
//
#define ACT_MAINSCREEN_ID		0x0001

//
// Loca Activites Main Functinos
//
extern unsigned char act_mainscreen_process(unsigned short acitivity_code, unsigned char* activity_data, int activity_data_len);

#endif /* ACT_H_ */