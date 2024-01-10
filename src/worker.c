#include <pebble_worker.h>
// #include "math.h"
    
#define SAMPLE_BUF    25
#define THRESHOLD     25000000 // 25 000 000 > 2.8g


double norme_2(AccelData data)
{
    return (data.x * data.x + data.y * data.y + data.z * data.z);
}

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
            //show_main_layout();
            APP_LOG(APP_LOG_LEVEL_INFO, "Fall detected, launching window app");
            worker_launch_app();
        }
    }
}

static void worker_init() {
  // Use the TickTimer Service as a data source
  //tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  accel_data_service_subscribe(SAMPLE_BUF, accel_data_handler);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_100HZ);
}

static void worker_deinit() {
  // Stop using the TickTimerService
  // tick_timer_service_unsubscribe();
  accel_data_service_unsubscribe();
}

int main(void) {
  worker_init();
  worker_event_loop();
  worker_deinit();
}