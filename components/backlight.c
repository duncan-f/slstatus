/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

#if defined(__linux__)
	#include <limits.h>
	#include <stdint.h>
	#include <unistd.h>

	const char *
	backlight_perc(const char *interface)
	{
		float curr, max;
		char path[PATH_MAX];

		if (esnprintf(path, sizeof(path),
		              "/sys/class/backlight/%s/brightness", interface) < 0) {
			return NULL;
		}
		if (pscanf(path, "%f", &curr) != 1) {
			return NULL;
		}

		if (esnprintf(path, sizeof(path),
		              "/sys/class/backlight/%s/max_brightness", interface) < 0) {
			return NULL;
		}
		if (pscanf(path, "%f", &max) != 1) {
			return NULL;
		}

		return bprintf("%.0f", curr/max*100);
	}
#endif
