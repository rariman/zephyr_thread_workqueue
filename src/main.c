#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

void work_handler_led2(struct k_work *work);
void work_handler_led3(struct k_work *work);
K_WORK_DELAYABLE_DEFINE(my_work_led2, work_handler_led2);
K_WORK_DELAYABLE_DEFINE(my_work_led3, work_handler_led3);

void work_handler_led2(struct k_work *work)
{
    k_work_reschedule(&my_work_led2, K_MSEC(250));
    gpio_pin_toggle_dt(&led2);
}

void work_handler_led3(struct k_work *work)
{
    k_work_reschedule(&my_work_led3, K_MSEC(750));
    gpio_pin_toggle_dt(&led3);
}


void thread_led0(void)
{
    while (1) {
        gpio_pin_toggle_dt(&led0);
        k_msleep(500);
    }
}

void thread_led1(void)
{
    while (1) {
        gpio_pin_toggle_dt(&led1);
        k_msleep(1000);
    }
}

K_THREAD_DEFINE(led0_thread_id, CONFIG_STACK_SIZE, thread_led0, NULL, NULL, NULL, CONFIG_PRIORITY, 0, 0);
K_THREAD_DEFINE(led1_thread_id, CONFIG_STACK_SIZE, thread_led1, NULL, NULL, NULL, CONFIG_PRIORITY, 0, 0);

int main(void)
{
        if (!device_is_ready(led0.port) || !device_is_ready(led1.port) || !device_is_ready(led2.port) || !device_is_ready(led3.port)) {
                return -ENODEV;
        }

        gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
        gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
        gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
        gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);

        k_work_reschedule(&my_work_led2, K_MSEC(250));
        k_work_reschedule(&my_work_led3, K_MSEC(750));

        return 0;
}
