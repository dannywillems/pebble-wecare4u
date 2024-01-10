#include "home_page.h"
#include <pebble.h>

static void handle_window_load();    

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(0, 65, 144, 40));
  text_layer_set_text(s_textlayer_1, "WeCare4U");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE
/*
static bool isFalling(AccelData *data)
{
    int i;
    double min;
    double max;
    double tmp;
    
    min = norme_2(data[0]);
    max = norme_2(data[0]);
    for (i = 1;i < SAMPLE_BUF;i++)
    {
        tmp = norme_2(data[i]);
        if (min > tmp)
            min = tmp;
        else if (max < tmp)
            max = tmp;
    }

    return (max - min > THRESHOLD);
}

static void accel_data_handler(AccelData *data, uint32_t num_samples)
{
    if (num_samples <= SAMPLE_BUF)
    {
        //APP_LOG(APP_LOG_LEVEL_DEBUG, "récolte des données.");

        if (isFalling(data))
        {
            //APP_LOG(APP_LOG_LEVEL_DEBUG, "Fall");
            
            // accel_data_service_unsubscribe();
            // tick_timer_service_unsubscribe();
            
            show_main_layout();
        }
    }
}
*/

static void handle_window_load()
{            
    // accel_data_service_subscribe(SAMPLE_BUF, accel_data_handler);
    // accel_service_set_sampling_rate(ACCEL_SAMPLING_100HZ);
}
  
static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_home_page(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
      .load   = handle_window_load,
      .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_home_page(void) {
  window_stack_remove(s_window, true);
}