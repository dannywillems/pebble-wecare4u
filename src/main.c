#include <pebble.h>
#include "home_page.h"
    
void handle_init(void) 
{
    light_enable(true);
    show_home_page();
}

void handle_deinit(void) 
{
    hide_home_page();
}
/*
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
*/

int main(void) {
  // Check to see if the worker is currently active
  bool running = app_worker_is_running();

  AppWorkerResult result;
  if(running) // le worker est en cours de fonctionnement
  { 
    result = app_worker_kill();
    if(result == APP_WORKER_RESULT_SUCCESS) {
      // text_layer_set_text(s_ticks_layer, "Worker stopped!");
      APP_LOG(APP_LOG_LEVEL_INFO, "Worker stopped!  +--> Result: %d", result);
    } else {
      // text_layer_set_text(s_ticks_layer, "Error killing worker!");
      APP_LOG(APP_LOG_LEVEL_INFO, "Error killing worker!  +--> Result: %d", result);
    }
  // init();
  // app_event_loop();
  // deinit();
  handle_init();
  app_event_loop();
  handle_deinit();

  }
  
  else { // le worker n'est pas encore démarré
    result = app_worker_launch();
    if(result == APP_WORKER_RESULT_SUCCESS) {
      // text_layer_set_text(s_ticks_layer, "Worker launched!");
      APP_LOG(APP_LOG_LEVEL_INFO, "Worker launched!  --> Result: %d", result);
    } else {
      // text_layer_set_text(s_ticks_layer, "Error launching worker!");
      APP_LOG(APP_LOG_LEVEL_INFO, "Error launching worker!  --> Result: %d", result);
    }
  }

}