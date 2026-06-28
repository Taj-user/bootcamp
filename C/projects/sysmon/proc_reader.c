#include <stdio.h>
#include "sysmon.h"

int read_uptime(SysUptime *uptime) {
        FILE *f = fopen("/proc/uptime", "r");
        if(f == NULL) {
                return -1;
        }
        double first;
        double second;
        int items_read = fscanf(f, "%lf %lf", &first, &second);
        if(items_read != 2) {
                fclose(f);
                return -1;
        }
        fclose(f);
        uptime->uptime_seconds = (uint64_t)first;
        uptime->idle_seconds = (uint64_t)second;
        return 0;
}
