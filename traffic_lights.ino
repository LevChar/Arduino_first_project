typedef unsigned int Uint;

//Setup of variables describing the output channels
const Uint led_entry_direction_red = 3;
const Uint led_entry_direction_green = 4;
const Uint led_exit_direction_red = 5;
const Uint led_exit_direction_green = 6;

//This yellow light is used to indicate the current priority state
const Uint led_priority_yellow = 7;

//Setup of variables describing the input channels
const Uint button_entry = 11;
const Uint button_exit = 12;
const Uint button_priority_switch = 13;

//Setup of additional variables
bool switching = false;
bool entry_priority = false;
Uint active_button;

void setup()
{
  //Declare All the LEDs as output
  pinMode(led_entry_direction_red, OUTPUT);
  pinMode(led_entry_direction_green, OUTPUT);
  pinMode(led_exit_direction_red, OUTPUT);
  pinMode(led_exit_direction_green, OUTPUT);
  pinMode(led_priority_yellow, OUTPUT);

  //Declare All the BUTTONs as input
  pinMode(button_entry, INPUT_PULLUP);
  pinMode(button_exit, INPUT_PULLUP);
  pinMode(button_priority_switch, INPUT_PULLUP);

  if (entry_priority)
  {
    activate_light(led_entry_direction_green);
    activate_light(led_exit_direction_red);
    active_button = button_exit;
  }
  else
  {
    activate_light(led_exit_direction_green);
    activate_light(led_entry_direction_red);
    active_button = button_entry;
  }
}

void activate_light(Uint i_light_to_activate)
{
  digitalWrite(i_light_to_activate, HIGH);
  shut_down_light(i_light_to_activate);
}

void shut_down_light(Uint i_opposite_to_shutdown)
{
  Uint light_to_shut = (i_opposite_to_shutdown == led_entry_direction_green) ? led_entry_direction_red :
                       (i_opposite_to_shutdown == led_entry_direction_red) ? led_entry_direction_green :
                       (i_opposite_to_shutdown == led_exit_direction_green) ? led_exit_direction_red :
                       led_exit_direction_green;

  digitalWrite(light_to_shut, LOW);
}

void loop()
{
  int active_button_state = digitalRead(active_button);
  int switch_priority_button_state = digitalRead(button_priority_switch);

  if (!switching)
  {
    if (active_button_state == LOW)
    {
      switch_traffic_lights(true);
    }

    if (switch_priority_button_state == LOW)
    {
      switch_priority();
    }
  }
  
  delay(200);
}

void switch_traffic_lights(bool restore_after_switch)
{
  switching = true;
  
  Uint red_to_start_on_restore, ignore_res;

  if (entry_priority)
  {
    red_to_start_on_restore = switch_lights(led_entry_direction_red, true);
  }
  else
  {
    red_to_start_on_restore = switch_lights(led_exit_direction_red, true);
  }


  if (restore_after_switch)
  {
    ignore_res = switch_lights(red_to_start_on_restore, false);
  }

  switching = false;
}

//start by switching the current green light to red light
Uint switch_lights(Uint i_light_to_start_with, bool wait_befor_restore)
{
  activate_light(i_light_to_start_with);
  delay(3000);

  Uint green_to_turn_on = (i_light_to_start_with == led_entry_direction_red) ?
                          led_exit_direction_green :  led_entry_direction_green;

  activate_light(green_to_turn_on);

  if (wait_befor_restore)
  {
    delay(5000);
  }

  return (i_light_to_start_with == led_entry_direction_red) ? 
    led_exit_direction_red : led_entry_direction_red;
}

void switch_priority()
{
  switching = true;

  Uint priority_to_write = (entry_priority == false) ? HIGH : LOW;
  digitalWrite(led_priority_yellow, priority_to_write);

  active_button = (entry_priority == false) ? button_exit : button_entry;

  switch_traffic_lights(false);

  entry_priority = (entry_priority == false) ? true : false;

  switching = false;
}