void init_board(void (*button1)(void), void (*button2)(void), void (*button3)(void));

void sensors_read(int *sens);

void motors_set_speed(int motor1_speed, int motor2_speed);

void debug_led_set_state(int state);

void delay(int ms);
