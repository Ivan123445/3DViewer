#include "tests.h"

START_TEST(parse_success) {
    FILE* file = fopen("test.obj", "w");
    fprintf(file,
            "v 0 0 0 #v1\n"
            "v 0 0 1 #v2\n"
            "v 0 1 1 #v3\n"
            "v 0 1 0 #v4\n"
            "f 1 2 3 4"
            "#full line comment\n");
    fclose(file);
    obj_data_t data;
    status_t result = parse_file("test.obj", &data);
    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(data.points);
    ck_assert_ptr_nonnull(data.surfaces);
    ck_assert_int_eq(data.count_points, 4);
    ck_assert_int_eq(data.count_surfaces, 1);
//    free_obj_data(&data);
}

START_TEST(parse_failure) {
    FILE* file = fopen("test.obj", "w");
    fprintf(file,
            "v 0 0 0 #v1\n"
            "v 0 0 1 #v2\n"
            "v 0 1 1 #v3\n"
            "v 0 1 0 #v4\n"
            "r 1 2 3 4"
            "#full line comment\n");
    fclose(file);
    obj_data_t data;
    status_t result = parse_file( "test.obj", &data);
    ck_assert_int_eq(result, FORMAT_FILE_ERR);
}

START_TEST(parse_missing) {
    obj_data_t data;
    status_t result = parse_file("not_exist.obj", &data);
    ck_assert_int_eq(result, OPEN_FILE_ERR);
}

START_TEST(parse_wrong_input) {
    FILE* file = fopen("test.obj", "w");
    fprintf(file,
            "v 0a0 0 0 #v1\n"
            "f 1 2 3 4\n");
    fclose(file);
    obj_data_t data;
    status_t result = parse_file("test.obj", &data);
    ck_assert_int_eq(result, FORMAT_FILE_ERR);
}

Suite* parse_file_suite() {
    Suite* s = suite_create("parse_file_suite");

    TCase* parse_file_cases = tcase_create("parse_file_cases");

    suite_add_tcase(s, parse_file_cases);

    tcase_add_test(parse_file_cases, parse_success);
    tcase_add_test(parse_file_cases, parse_failure);
    tcase_add_test(parse_file_cases, parse_missing);
    tcase_add_test(parse_file_cases, parse_wrong_input);

    return s;
}