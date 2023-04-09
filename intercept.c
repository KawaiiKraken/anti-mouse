#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <errno.h>
#include <xdo.h>

#define EXIT_KEY  KEY_ESC
#define SCR_LOCK  70 
#define BREAK_KEY 119
#define UNGRAB    0
#define GRAB      1


int i;
xdo_t* xdo;
int qwerty_keycodes[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 30, 31, 32, 33, 34, 35, 36, 37, 38, 44, 45, 46, 47, 48, 49, 50, 57, 14, 28, 59, 60 ,61, 62, 63, 64, 65, 66, 67, 68, 87, 88, 99, 70, 119, 41, 110, 102, 104, 15, 26, 27, 43, 111, 107, 109, 58, 39, 40, 42, 51, 52, 53, 54, 29, 125, 56, 100, 127, 97, 105, 103, 106, 108 };
// https://gitlab.com/cunidev/gestures/-/wikis/xdotool-list-of-key-codes
char qwerty[][30] = {"Escape","1","2","3","4","5","6","7","8","9","0","minus","equal","q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n","m","space","BackSpace","Enter","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","3270_PrintScreen","Scroll_Lock","Break","grave","Insert","Home","Page_Up","Tab","bracketleft","bracketright","backslash","Delete","End","Page_Down","Caps_Lock","semicolon","apostrophe","Shift_L","comma","period","slash","Shift_R","Control_L","Super_L","Alt_L","Alt_R","Menu","Control_R","Left","Up","Right","Down"};
char cyrillic[][30] = {"Escape","1","2","3","4","5","6","7","8","9","0","minus","equal","Cyrillic_ze","Cyrillic_ve","Cyrillic_ie","Cyrillic_er","Cyrillic_te","Cyrillic_yeru","Cyrillic_u","Cyrillic_i","Cyrillic_o","Cyrillic_pe","Cyrillic_a","Cyrillic_es","Cyrillic_de","Cyrillic_ef","Cyrillic_ghe","Cyrillic_ha","Cyrillic_shorti","Cyrillic_ka","Cyrillic_el","Cyrillic_zhe","Cyrillic_ze","Cyrillic_tse","Cyrillic_ve","Cyrillic_be","Cyrillic_en","Cyrillic_em","space","BackSpace","Enter","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","3270_PrintScreen","Scroll_Lock","Break","grave","Insert","Home","Page_Up","Tab","bracketleft","bracketright","backslash","Delete","End","Page_Down","Caps_Lock","semicolon","apostrophe","Shift_L","comma","period","slash","Shift_R","Control_L","Super_L","Alt_L","Alt_R","Menu","Control_R","Left","Up","Right","Down"};
char cyrillicExtra[][30] = {"Cyrillic_yu", "Cyrillic_ya", "Cyrillic_softsign", "Cyrillic_ze", "Cyrillic_sha", "Cyrillic_e", "Cyrillic_shcha", "Cyrillic_che", "Cyrillic_hardsign" };
bool mode_normal = true;
char command[200];

int keycode_to_keyname(int scancode){
  for (i = 0; i < sizeof(qwerty_keycodes) / sizeof(qwerty_keycodes[0]); i++){
    if (qwerty_keycodes[i] == scancode){
      break;
    }
  }
  return 0;
}

void xdotool(int keystate){
  xdo = xdo_new(NULL);
  if (keystate == 0) {
    xdo_send_keysequence_window_up(xdo, CURRENTWINDOW, qwerty[i], 0);
  } else if ( keystate == 1) {
    xdo_send_keysequence_window_down(xdo, CURRENTWINDOW, qwerty[i], 0);
  }
  xdo_free(xdo);
}

void xdo_cyrillic(int last_index){
  xdo = xdo_new(NULL);
  printf("i = %d\n", i);
  if (last_index == 29 && i == 23){ // case j a 
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "BackSpace", 0);
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "Cyrillic_ya", 0);
  }
  else if (last_index == 20 && i == 23){ // case i a 
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "BackSpace", 0);
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "Cyrillic_ya", 0);
  }
  else if (last_index == 34 && i == 32){ // case c z 
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "BackSpace", 0);
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "Cyrillic_che", 0);
  }
  else if (last_index == 24 && i == 32){ // case s z
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "BackSpace", 0);
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "Cyrillic_sha", 0);
  }
  else if (last_index == 29 && i == 19){ // case j u
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "BackSpace", 0);
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "Cyrillic_yu", 0);
  }
  else if (last_index == 20 && i == 19){ // case i u 
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "BackSpace", 0);
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, "Cyrillic_yu", 0);
  } else if ((i != 39) & (i != 40) & (i != 42)){
    xdo_send_keysequence_window(xdo, CURRENTWINDOW, cyrillic[i], 0);
  }
  xdo_free(xdo);
}


int last_index = -1;
void xdotool_cyrillic(int keystate){
  if ((i == 39 ) | (i == 40) | (i == 71)){
    xdotool(keystate);
  } else if (keystate == 1) {
    xdo_cyrillic(last_index);
  }
  last_index = i;
}


// ------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
  char* kbd_device = "/dev/input/event256"; //replace with keyboard device 
  if (argc > 1){
    if ((strcmp(argv[1], "--help") == 0) | (strcmp(argv[1], "-h") == 0)){
      printf("print help\n");
      exit(0);
    } else {
      printf("settigns kbd_device to argv[1]\n");
      kbd_device = argv[1];
    }
  } else {
    printf("please provide at least one arg\nrunning with fallback %s\n", kbd_device);
  }

  usleep(150000);
  int device = open(kbd_device, O_RDONLY);
  if(device == -1){
    printf("Cannot open %s. %s.\n", kbd_device, strerror(errno));
    printf("Run me as root!\n");
    return -1;
  }

  if(ioctl(device, EVIOCGRAB, GRAB))
    printf("Couldn't grab %s. %s.\n", kbd_device, strerror(errno));
  else
    printf("Grabbed %s\n", kbd_device);

  while(true){
    struct input_event event;
    read(device, &event, sizeof(event));
    if (event.type == EV_KEY && event.value >= 0 && event.value <= 2){
      if(event.code == BREAK_KEY){
        ioctl(device, EVIOCGRAB, UNGRAB);
        close(device);
        return 0;
      }
      if (event.code == SCR_LOCK && event.value == 1) {
        if (mode_normal == true ){
          mode_normal = false;
          printf("mode = %d\n", mode_normal);
        } else if (mode_normal == false ){
          mode_normal = true;
          printf("mode = %d\n", mode_normal);
        }
      }

      if (event.value != 2){
        printf("code %d\n", event.code);
        keycode_to_keyname(event.code);
        if (mode_normal == true){
          xdotool(event.value);
        } else if (mode_normal == false){
          xdotool_cyrillic(event.value);
        }  
      }
    }
  }
}
