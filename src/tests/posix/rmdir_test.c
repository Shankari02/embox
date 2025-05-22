/**
 * @file
 * @brief
 *
 * @date May 19, 2025
 * @author Shankari Anand
 */

#include <embox/test.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

EMBOX_TEST_SUITE("Test for rmdir");

#define RMDIR_TEST_MOUNTPOINT "/mnt"
#define RMDIR_TEST_CREAT_MODE 0777

TEST_CASE("Remove empty directory") {
	static const char dir[] = RMDIR_TEST_MOUNTPOINT "/rmdir_test_dir";

	test_assert_zero(mkdir(dir, RMDIR_TEST_CREAT_MODE));

	test_assert_zero(rmdir(dir));
}

TEST_CASE("Remove non-empty directory (should fail)") {
	static const char parent[] = RMDIR_TEST_MOUNTPOINT "/rmdir_test_non_empty";
	static const char child[]  = RMDIR_TEST_MOUNTPOINT "/rmdir_test_non_empty/child";

	test_assert_zero(mkdir(parent, RMDIR_TEST_CREAT_MODE));
	test_assert_zero(mkdir(child, RMDIR_TEST_CREAT_MODE));

	test_assert_not_equal(0, rmdir(parent));

	// Clean up
	test_assert_zero(rmdir(child));
	test_assert_zero(rmdir(parent));
}

TEST_CASE("Remove same directory twice (second should fail)") {
	static const char dir[] = RMDIR_TEST_MOUNTPOINT "/rmdir_test_twice";

	test_assert_zero(mkdir(dir, RMDIR_TEST_CREAT_MODE));
	test_assert_zero(rmdir(dir));

	test_assert_not_equal(0, rmdir(dir));
}

TEST_CASE("Remove non-existent directory (should fail)") {
	static const char dir[] = RMDIR_TEST_MOUNTPOINT "/rmdir_test_noexist";

	test_assert_not_equal(0, rmdir(dir));
}
