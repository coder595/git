/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

static const struct arg args[] = {
    /* function      format                  argument */
    { wifi_perc,     " [  %3s%% ] ",           "wlp7s0" },
    { temp,          "[  %s°C ] ",            "/sys/class/thermal/thermal_zone0/temp" },
    { ram_perc,      "[  %s%% ] ",            NULL },
    { cpu_perc,      "[  %s%% ] ",            NULL },
    { datetime,      "[  %s ",              "%a %b %d" },
    { datetime,      "  %s] ",               "%r" },
};
