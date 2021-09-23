#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define TRIGGER        "trigger"
#define LED_PATH        "/sys/class/leds/"
#define LED_STATUS        "brightness"
#define TRIGGER_NONE    "none"
int main(int argc, char** argv) {
    char path[50] = {0}, data[2] = {0};
    int fd = 0, ret = 0, flag = 0;
    if (argv[1] == NULL) {
        printf("usage: ./led led-xx\n");    // led-err or led-run @ EPC-6G2C-L
        return 0;
    }
    strcpy(path, LED_PATH);
    strcat(path, argv[1]);
    strcat(path, "/" LED_STATUS);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    for (;;) {
        data[0] = flag ? '0' : '1';
        ret = write(fd, data, 1);
        if (ret < 0) {
            perror("write");
            return -1;
        }
        flag = !flag;
        sleep(1);
    }
    return 0;
}
