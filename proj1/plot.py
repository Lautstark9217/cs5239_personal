#!/usr/bin/python3

import matplotlib.pyplot as plt


def main():
	# TODO: for each compression level in {0, 1, ..., 9}:
	#			fill real_time [ms]
	#			fill archive_size [bytes]
	level        = list(range(10))
	real_time    = [ ]
	archive_size = [ ]

	archive_size = [it / 1024 for it in archive_size]

	# plot data
	fix, axs = plt.subplots(2)

	axs[0].plot(level, real_time,    'bo-')
	axs[1].plot(level, archive_size, 'ro-')

	axs[0].set_xticks(level)
	axs[1].set_xticks(level)

	axs[0].grid(True, which='both')
	axs[1].grid(True, which='both')

	axs[0].set_xlabel('Compression level')
	axs[1].set_xlabel('Compression level')

	axs[0].set_ylabel('Time [ms]')
	axs[1].set_ylabel('Archive size [byte]')

	plt.show()


if __name__ == '__main__':
	main()