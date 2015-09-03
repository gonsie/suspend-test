//Elsa Gonsiorowski
//September 3, 2015

#include <stdio.h>
#include "ross.h"
#include "suspend.h"

//Init function
// - called once for each LP
// ! LP can only send messages to itself during init !
void increment_init (state *s, tw_lp *lp) {
  int self = lp->gid;

  // init state data
  s->increment_value = 1;
  s->round_count = 0;

  // Init message to myself
  tw_event *e = tw_event_new(self, 1, lp);
  message *msg = tw_event_data(e);
  msg->type = WAKEUP;
  tw_event_send(e);
}

//Forward event handler
void increment_event (state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
  int self = lp->gid;

  if (in_msg->type != WAKEUP) {
    tw_error(TW_LOC, "Increment LP received wrong message type")
  }

  s->round_count++;

  int i;
  for (i = 0; i < total_receivers; i++) {
    tw_event *e = tw_event_new(i+2, 1, lp);
    message *msg = tw_event_data(e);
    msg->type = INCREMENT;
    msg->value = s->increment_value;
    tw_event_send(e);
  }
}

//Reverse Event Handler
void increment_event_reverse (state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
  // there is nothing to do here
  return;
}

//report any final statistics for this LP
void increment_final (state *s, tw_lp *lp){
  int self = lp->gid;
  printf("%d sent %d rounds of increment messages, each with value %d\n", self, s->round_count, s->increment_value);
}
