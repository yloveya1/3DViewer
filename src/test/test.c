#include <check.h>

#include "../back/c_code.h"

START_TEST(move_X) {
  float arr[12] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
  float check[12] = {5, 0, 0, 6, 1, 1, 7, 2, 2, 8, 3, 3};

  moveX(arr, 5, 4);

  for (int i = 0; i < 12; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(move_Y) {
  float arr[12] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
  float check[12] = {0, 5, 0, 1, 6, 1, 2, 7, 2, 3, 8, 3};

  moveY(arr, 5, 4);

  for (int i = 0; i < 12; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(move_Z) {
  float arr[12] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
  float check[12] = {0, 0, 5, 1, 1, 6, 2, 2, 7, 3, 3, 8};

  moveZ(arr, 5, 4);

  for (int i = 0; i < 12; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(rotate_X) {
  float arr[3] = {1, 1, 1};
  float check[3] = {1, 1, -1};

  rotateX(arr, 1, 90);

  for (int i = 0; i < 3; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(rotate_Y) {
  float arr[3] = {1, 1, 1};
  float check[3] = {1, 1, -1};

  rotateY(arr, 1, 90);

  for (int i = 0; i < 3; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(rotate_Z) {
  float arr[3] = {1, 1, 1};
  float check[3] = {1, -1, 1};

  rotateZ(arr, 1, 90);

  for (int i = 0; i < 3; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(scale_Model) {
  float arr[3] = {1, 1, 1};
  float check[3] = {2, 2, 2};

  scaleModel(arr, 1, 2);

  for (int i = 0; i < 3; i++) {
    ck_assert_float_eq_tol(arr[i], check[i], 1e-6);
  }
}
END_TEST

START_TEST(number_v) {
  FILE *f;
  f = fopen("obj/1.obj", "r");
  int count_v = 4, res_v = 0;
  if (f) {
    res_v = numberOfVertices(f);
    fclose(f);
  }
  ck_assert_int_eq(count_v, res_v);
}

START_TEST(number_p) {
  FILE *f;
  f = fopen("obj/1.obj", "r");
  int count_p = 2, res_p = 0;
  if (f) {
    res_p = numberOfPolygons(f);
    fclose(f);
  }
  ck_assert_int_eq(count_p, res_p);
}

START_TEST(form_vertices) {
  FILE *f;
  f = fopen("obj/1.obj", "r");
  obj data = {0};
  float check_data[12] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0};
  data.index_v = 4;
  data.xyz = calloc(data.index_v * 3, sizeof(float));
  if (f) {
    formingVerticesData(f, &data);
    for (int i = 0; i < 12; i++) {
      ck_assert_float_eq_tol(data.xyz[i], check_data[i], 1e-6);
    }
    fclose(f);
  }
  free(data.xyz);
}

START_TEST(form_polygones) {
  FILE *f;
  f = fopen("obj/1.obj", "r");
  obj data = {0};
  int check_data[6] = {0, 1, 2, 1, 2, 3};
  data.index_p = 2;
  data.index_triangles = calloc(data.index_p * 3, sizeof(int));
  if (f) {
    formingPolygonsData(f, &data);
    for (int i = 0; i < 6; i++) {
      ck_assert_int_eq(data.index_triangles[i], check_data[i]);
    }
    fclose(f);
  }
  free(data.index_triangles);
}

int main(void) {
  Suite *s1 = suite_create("Test_calculator");
  TCase *tc1 = tcase_create("Test_calculator");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1);
  tcase_add_test(tc1, move_X);
  tcase_add_test(tc1, move_Y);
  tcase_add_test(tc1, move_Z);
  tcase_add_test(tc1, rotate_X);
  tcase_add_test(tc1, rotate_Y);
  tcase_add_test(tc1, rotate_Z);
  tcase_add_test(tc1, scale_Model);
  tcase_add_test(tc1, number_v);
  tcase_add_test(tc1, number_p);
  tcase_add_test(tc1, form_vertices);
  tcase_add_test(tc1, form_polygones);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
