//Elsa Gonsiorowski
//September 3, 2015

#ifndef _suspend_h
#define _suspend_h

#include "ross.h"

//Example enumeration of message type... could also use #defines
typedef enum {
  HELLO,
  GOODBYE,
} message_type;

//Message struct
//   this contains all data sent in an event
typedef struct {
  message_type type;
  double contents;
  tw_lpid sender;
} message;


//State struct
//   this defines the state of each LP
typedef struct {
  int rcvd_count_H;
  int rcvd_count_G;
  double value;
} state;


//Command Line Argument declarations
extern unsigned int setting_1;

//Global variables used by both main and driver
// - this defines the LP types
extern tw_lptype suspend_lps[];

//Function Declarations
// defined in suspend_driver.c:
extern void suspend_init(state *s, tw_lp *lp);
extern void suspend_event(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void suspend_event_reverse(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void suspend_final(state *s, tw_lp *lp);
// defined in suspend_map.c:
extern tw_peid suspend_map(tw_lpid gid);

/*
//Custom mapping prototypes
void suspend_cutom_mapping(void);
tw_lp * suspend_mapping_to_lp(tw_lpid lpid);
tw_peid suspend_map(tw_lpid gid);
*/

#endif
