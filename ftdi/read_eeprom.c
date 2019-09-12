#include <stdio.h>
#include <libftdi1/ftdi.h>
#include <stdlib.h>

#include "ftdi_struct.h"

int main()
{
	struct ftdi_context *ftdi_device;

	if ((ftdi_device = ftdi_new()) == 0) {
		fprintf(stderr, "Failed ftdi_new(): %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	if (ftdi_usb_open(ftdi_device, 0x0403, 0x6001) < 0) {
		fprintf(stderr, "Failed to open FTDI device: %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	if (ftdi_read_eeprom(ftdi_device) < 0) {
		fprintf(stderr, "Failed to read FTDI device eeprom: %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	if (ftdi_eeprom_decode(ftdi_device, 1) < 0) {
		fprintf(stderr, "Failed to decode FTDI device eeprom: %s", ftdi_get_error_string(ftdi_device));
		return EXIT_FAILURE;
	}

	ftdi_free(ftdi_device);

	return 0;
}
