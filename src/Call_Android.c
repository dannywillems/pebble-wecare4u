#include <pebble.h>
#include "Call_Android.h"

void call_android(){
    
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    Tuplet value = TupletInteger(1, 42);
    dict_write_tuplet(iter, &value);
    app_message_outbox_send();
    //window_stack_pop(true);
  
}