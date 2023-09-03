#include "tests.h"

int main() {
  Suite* suites[] = {affine_transformation_suite(), parse_file_suite(), NULL};

  for (int i = 0; suites[i]; ++i) {
    SRunner* srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }

  return 0;
}
