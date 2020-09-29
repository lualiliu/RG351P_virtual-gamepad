#include <linux/uinput.h>
#include <linux/input.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#define XBOX_TYPE_BUTTON    0x01
#define XBOX_TYPE_AXIS      0x02
 
#define XBOX_BUTTON_A       0x00
#define XBOX_BUTTON_B       0x01
#define XBOX_BUTTON_X       0x02
#define XBOX_BUTTON_Y       0x03
#define XBOX_BUTTON_LB      0x04
#define XBOX_BUTTON_RB      0x05
#define XBOX_BUTTON_START   0x06
#define XBOX_BUTTON_BACK    0x07
#define XBOX_BUTTON_LO	     0x08
#define XBOX_BUTTON_RO      0x09
#define XBOX_BUTTON_L2      0x0a
#define XBOX_BUTTON_R2      0x0b
 
#define XBOX_BUTTON_ON      0x01
#define XBOX_BUTTON_OFF     0x00
 
#define XBOX_AXIS_LX        0x00
#define XBOX_AXIS_LY        0x01
#define XBOX_AXIS_RX        0x02
#define XBOX_AXIS_RY        0x03
#define XBOX_AXIS_XX        0x05
#define XBOX_AXIS_YY        0x06
 
#define XBOX_AXIS_VAL_UP        -32767
#define XBOX_AXIS_VAL_DOWN      32767
#define XBOX_AXIS_VAL_LEFT      -32767
#define XBOX_AXIS_VAL_RIGHT     32767
 
#define XBOX_AXIS_VAL_MIN       -32767
#define XBOX_AXIS_VAL_MAX       32767
#define XBOX_AXIS_VAL_MID       0x00

struct js_event {
        __u32 time; /* event timestamp in milliseconds */
        __s16 value; /* value */
        __u8 type; /* event type */
        __u8 number; /* axis/button number */
};
    
typedef struct xbox_map
{
    int     time;
    int     a;
    int     b;
    int     x;
    int     y;
    int     lb;
    int     rb;
    int     start;
    int     back;
    int     home;
    int     lo;
    int     ro;
 
    int     lx;
    int     ly;
    int     rx;
    int     ry;
    int     lt;
    int     rt;
    int     xx;
    int     yy;
 
}xbox_map_t;

void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}

int joy_open(char *file_name)
{
    int joy_fd;
 
    joy_fd = open(file_name, O_RDONLY);
    if (joy_fd < 0)
    {
        perror("open error");
        return -1;
    }
 
    return joy_fd;
}
void map_read(int joy_fd,int fd,xbox_map_t *map)
{
    int len, type, number, value;
    struct js_event js;
 
    len = read(joy_fd, &js, sizeof(struct js_event));
    
    if (len < 0)
    {
        perror("read error");
    }
 
    type = js.type;
    number = js.number;
    value = js.value;
 
    map->time = js.time;
    printf("type:%d number:%d\n",type,number);
    if (type == XBOX_TYPE_BUTTON)
    {
        switch (number)
        {
            case XBOX_BUTTON_A:
		 emit(fd, EV_KEY, BTN_EAST, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_EAST, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_B:
		 emit(fd, EV_KEY, BTN_SOUTH, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_SOUTH, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_X:
		 emit(fd, EV_KEY, BTN_NORTH, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_NORTH, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_Y:
		 emit(fd, EV_KEY, BTN_WEST, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_WEST, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_LB:
		 emit(fd, EV_KEY, BTN_TL, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_TL, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_RB:
		 emit(fd, EV_KEY, BTN_TR, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_TR, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_START:
		 emit(fd, EV_KEY, BTN_START, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_START, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_BACK:
		 emit(fd, EV_KEY, BTN_SELECT, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_SELECT, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_LO:
		 emit(fd, EV_KEY, BTN_THUMBL, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_THUMBL, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_RO:
		 emit(fd, EV_KEY, BTN_THUMBR, 1);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_KEY, BTN_THUMBR, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
                
             case XBOX_BUTTON_L2:
		 emit(fd, EV_ABS, ABS_Z, 255);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_ABS, ABS_Z, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_BUTTON_R2:
		 emit(fd, EV_ABS, ABS_RZ, 255);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
		 emit(fd, EV_ABS, ABS_RZ, 0);
		 emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
            default:
                break;
        }
    }
    else if (type == XBOX_TYPE_AXIS)
    {
        switch(number)
        {
            case XBOX_AXIS_LX:
		emit(fd, EV_ABS, ABS_X, -value);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_ABS, ABS_X, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_AXIS_LY:
		emit(fd, EV_ABS, ABS_Y, -value);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_ABS, ABS_Y, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_AXIS_RX:
		emit(fd, EV_ABS, ABS_RX, value);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_ABS, ABS_RX, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_AXIS_RY:
		emit(fd, EV_ABS, ABS_RY, value);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_ABS, ABS_RY, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_AXIS_XX:
		emit(fd, EV_ABS, ABS_HAT0X, value);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_ABS, ABS_HAT0X, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            case XBOX_AXIS_YY:
		emit(fd, EV_ABS, ABS_HAT0Y, value);
		emit(fd, EV_SYN, SYN_REPORT, 0);
		emit(fd, EV_ABS, ABS_HAT0Y, 0);
		emit(fd, EV_SYN, SYN_REPORT, 0);
                break;
 
            default:
                break;
        }
    }
    else
    {
        /* Init do nothing */
    }
 
}
 
void joy_close(int joy_fd)
{
    close(joy_fd);
    return;
}


int main(void)
{
   struct uinput_setup usetup;


   int fd = open("/dev/uinput",  O_RDWR | O_NDELAY);
   
   int xbox_fd;
   xbox_map_t map;
   int len, type;
   int axis_value, button_value;
   int number_of_axis, number_of_buttons ;
 
   memset(&map, 0, sizeof(xbox_map_t));


   /*
    * The ioctls below will enable the device that is about to be
    * created, to pass key events, in this case the space key.
    */
   ioctl(fd, UI_SET_EVBIT, EV_KEY);
   ioctl(fd, UI_SET_EVBIT, EV_ABS);
   ioctl(fd, UI_SET_KEYBIT, BTN_EAST);
   ioctl(fd, UI_SET_KEYBIT, BTN_SOUTH);
   ioctl(fd, UI_SET_KEYBIT, BTN_NORTH);
   ioctl(fd, UI_SET_KEYBIT, BTN_WEST);
   ioctl(fd, UI_SET_KEYBIT, BTN_TL);
   ioctl(fd, UI_SET_KEYBIT, BTN_TR);
   ioctl(fd, UI_SET_KEYBIT, BTN_START);
   ioctl(fd, UI_SET_KEYBIT, BTN_SELECT);
   ioctl(fd, UI_SET_KEYBIT, BTN_THUMBL);
   ioctl(fd, UI_SET_KEYBIT, BTN_THUMBR);
   
   ioctl(fd, UI_SET_ABSBIT, ABS_Z);
   ioctl(fd, UI_SET_ABSBIT, ABS_RZ);
   ioctl(fd, UI_SET_ABSBIT, ABS_X);
   ioctl(fd, UI_SET_ABSBIT, ABS_Y);
   ioctl(fd, UI_SET_ABSBIT, ABS_RX);
   ioctl(fd, UI_SET_ABSBIT, ABS_RY);
   ioctl(fd, UI_SET_ABSBIT, BTN_START);
   ioctl(fd, UI_SET_ABSBIT, BTN_SELECT);
   ioctl(fd, UI_SET_ABSBIT, ABS_HAT0X);
   ioctl(fd, UI_SET_ABSBIT, ABS_HAT0Y);
   
   memset(&usetup, 0, sizeof(usetup));
   usetup.id.bustype = BUS_USB;
   usetup.id.vendor = 0x0001; /* sample vendor */
   usetup.id.product = 0x0001; /* sample product */
   strcpy(usetup.name, "RG351P Virtual Gamepad");

   ioctl(fd, UI_DEV_SETUP, &usetup);
   ioctl(fd, UI_DEV_CREATE);
 
   xbox_fd = joy_open("/dev/input/js0");
   if(xbox_fd < 0)
   {
       return -1;
   }
   /*
    * On UI_DEV_CREATE the kernel will create the device node for this
    * device. We are inserting a pause here so that userspace has time
    * to detect, initialize the new device, and can start listening to
    * the event, otherwise it will not notice the event we are about
    * to send. This pause is only needed in our example code!
    */
   /* Key press, report the event, send key release, and report again */

    while(1)
    {
        map_read(xbox_fd,fd, &map);
    }
   /*
    * Give userspace some time to read the events before we destroy the
    * device with UI_DEV_DESTOY.
    */

   ioctl(fd, UI_DEV_DESTROY);
   close(fd);

   return 0;
}
