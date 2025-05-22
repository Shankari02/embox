/**
 * @file
 * @brief remove directories
 *
 * @date 19.05.25
 * @author Shankari Anand
 */

#include <unistd.h>
#include <dirent.h> 
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <libgen.h>

static void print_usage(void) {
	printf("Usage: rmdir [-v] [-p] [--ignore-fail-on-non-empty] DIR ...\n");
}

static int is_dir_empty(const char *path) {
	DIR *dir = opendir(path);
	struct dirent *entry;

	if (!dir) {
		return -1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") != 0 &&
		    strcmp(entry->d_name, "..") != 0) {
			closedir(dir);
			return 0;
		}
	}

	closedir(dir);
	return 1;
}

int main(int argc, char **argv) {
	int opt;
	int verbose = 0;
	int remove_parents = 0;
	int ignore_fail = 0;
	int i;

    if (argc < 2) {
		printf("%s: missing operand\n", argv[0]);
		return 0;
	}

	if (argc > 1 && strcmp(argv[1], "--ignore-fail-on-non-empty") == 0) {
		ignore_fail = 1;
		argv++; argc--;
	}

	while ((opt = getopt(argc, argv, "hvp")) != -1) {
		switch (opt) {
		case 0:
			break;
		case 'h':
			print_usage();
			return 0;
		case 'v':
			verbose = 1;
			break;
		case 'p':
			remove_parents = 1;
			break;
		default:
			print_usage();
			return -EINVAL;
		}
	}

	if (optind >= argc) {
		printf("%s: missing operand\n", argv[0]);
		print_usage();
		return -EINVAL;
	}

	for (i = optind; i < argc; i++) {
		char *dir = argv[i];
		char temp[PATH_MAX];
		strncpy(temp, dir, sizeof(temp));
		temp[sizeof(temp) - 1] = '\0';

		do {
			int empty = is_dir_empty(temp);
			if (empty == 0 && !ignore_fail) {
				fprintf(stderr, "rmdir: failed to remove '%s': Directory not empty\n", temp);
				break;
			} else if (empty == -1) {
				perror("rmdir");
				break;
			}

			if (rmdir(temp) == -1) {
				perror("rmdir");
				break;
			} else if (verbose) {
				printf("rmdir: removed directory '%s'\n", temp);
			}

			if (!remove_parents) {
				break;
			}

			// Move up to parent
			char *parent = dirname(temp);
			if (!parent || strcmp(parent, "/") == 0 || strcmp(parent, ".") == 0) {
				break;
			}
			strncpy(temp, parent, sizeof(temp));
			temp[sizeof(temp) - 1] = '\0';

		} while (remove_parents);
	}

	return 0;
}
