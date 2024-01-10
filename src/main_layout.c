#include "main_layout.h"
#include <pebble.h>

static void up_button_handler();
static int current_value = 1;
static int countDown = WAITING_TIME;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_42_bold;
static TextLayer *s_textlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_textlayer_1 = text_layer_create(GRect(-3, 7, 148, 161));
  text_layer_set_text(s_textlayer_1, "Besoin d'aide ?");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE

static void count_down_handler(struct tm *tick_time, TimeUnits units_changed){

  if(countDown-- <= WAITING_TIME)
  {
    if (current_value == 0)
        text_layer_set_text(s_textlayer_1, "  OUI->                NON->");
    else
        text_layer_set_text(s_textlayer_1, "Besoin d'aide ?");
    current_value = countDown % NB_SECOND == 0 ? (current_value + 1) % 2 : current_value;
    vibes_short_pulse();
  }
    
  if (countDown == 0)
  {
     /*
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    Tuplet value = TupletInteger(1, 42);
    dict_write_tuplet(iter, &value);
    app_message_outbox_send();
    vibes_long_pulse();
    */
    up_button_handler();
  }
}
static void window_load(Window *window)
{
    tick_timer_service_subscribe(SECOND_UNIT, count_down_handler);
    count_down_handler(NULL, SECOND_UNIT);
    countDown = WAITING_TIME;
  
    const uint32_t inbound_size = 64;
    const uint32_t outbound_size = 64;
    app_message_open(inbound_size, outbound_size);
  
  
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    Tuplet value = TupletInteger(1, 12);
    dict_write_tuplet(iter, &value);
    app_message_outbox_send();
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void up_button_handler()
{
    text_layer_set_text(s_textlayer_1, "Alerte donnée");
    call_android();
    tick_timer_service_unsubscribe();
    //hide_main_layout();
}

static void down_button_handler()
{
    tick_timer_service_unsubscribe();
    window_stack_pop(true);
}
static void click_config_provider(void *contect)
{
    window_single_click_subscribe(BUTTON_ID_UP, up_button_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_button_handler);
}

void show_main_layout(void) {
  initialise_ui();
  window_set_click_config_provider(s_window, click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) 
  {
    .load   = window_load,
    .unload = handle_window_unload,
  });
  
  window_stack_push(s_window, true);
}

void hide_main_layout(void) 
{
  window_stack_remove(s_window, true);
}