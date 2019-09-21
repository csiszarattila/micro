#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libftdi1/ftdi.h>

#include "ftdi_struct.h"

#define LED_PIN 0x01 // 0x01 = TX

int main()
{
	unsigned char c = 0x00;
	struct ftdi_context *ftdi_device;

	if ((ftdi_device = ftdi_new()) == 0) {
		fprintf(stderr, "Failed ftdi_new(): %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	if (ftdi_usb_open(ftdi_device, 0x0403, 0x6001) < 0) {
		fprintf(stderr, "Failed to open FTDI device: %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	if (ftdi_set_bitmode(ftdi_device, 0xff, BITMODE_BITBANG) <0) {
		fprintf(stderr, "Failed to set bitbang mode: %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	for(;;) {
		c ^= LED_PIN;
		fprintf(stdout, "Sending... 0x%02X\n", c);
		int s = ftdi_write_data(ftdi_device, &c, 1);
		fprintf(stdout, "Bytes: %d", s);
		sleep(1);
	}

	if (ftdi_usb_close(ftdi_device) < 0) {
		fprintf(stderr, "Failed to close FTDI device: %s", ftdi_get_error_string(ftdi_device));
		ftdi_free(ftdi_device);
		return EXIT_FAILURE;
	}

	ftdi_free(ftdi_device);

	return EXIT_SUCCESS;
}
