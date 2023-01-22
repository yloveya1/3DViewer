#include "./c_code.h"

float readNumberFl(char** begin) {
  setlocale(LC_NUMERIC, "C");
  char** end = begin;
  float out = strtof(
      *begin,
      end);  // Прокручивает строку до первого символа после считанного числа
  *begin = (begin != end) ? *end : (*begin + 1);
  return out;
}

unsigned int readNumberInt(char** begin) {
  setlocale(LC_NUMERIC, "C");
  char** end = begin;
  long int out = strtol(
      *begin, end,
      10);  // Прокручивает строку до первого символа после считанного числа
  *begin = (begin != end) ? *end : (*begin + 1);
  return out;
}

int numberOfVertices(FILE* fp) {
  char str[100] = "";
  while (!(str[0] == 'v' && str[1] == ' ')) fgets(str, 100, fp);
  int count = 0;
  do {
    count++;
    fgets(str, 100, fp);
  } while (str[0] == 'v' && str[1] == ' ');
  return count;
}

int numberOfPolygons(FILE* fp) {
  char str[100] = "";
  while (!(str[0] == 'f' && str[1] == ' ')) fgets(str, 100, fp);
  int count = 0;
  int endfile = 0;
  do {
    count++;
    fgets(str, 100, fp);
    endfile = feof(fp);
  } while (str[0] == 'f' && endfile == 0);
  fseek(fp, 0, SEEK_SET);
  return count;
}

void formingVerticesData(FILE* fp, obj* obj_data) {
  char str[100] = "";
  while (!(str[0] == 'v' && str[1] == ' ')) fgets(str, 100, fp);
  for (unsigned int i = 0; i < obj_data->index_v; i++) {
    char* begin = str + 1;
    obj_data->xyz[XI] = (readNumberFl(&begin));
    obj_data->xyz[YI] = (readNumberFl(&begin));
    obj_data->xyz[ZI] = (readNumberFl(&begin));

    if (fabs(obj_data->xyz[XI]) > obj_data->max_size)
      obj_data->max_size = fabs(obj_data->xyz[XI]);
    if (fabs(obj_data->xyz[YI]) > obj_data->max_size)
      obj_data->max_size = fabs(obj_data->xyz[YI]);
    if (fabs(obj_data->xyz[ZI]) > obj_data->max_size)
      obj_data->max_size = fabs(obj_data->xyz[ZI]);
    fgets(str, 100, fp);
  }
}

void formingPolygonsData(FILE* fp, obj* obj_data) {
  char str[100] = "";
  while (str[0] != 'f') fgets(str, 100, fp);
  for (unsigned int i = 0; i < obj_data->index_p; i++) {
    char* begin = str + 1;
    obj_data->index_triangles[XI] = readNumberInt(&begin) - 1;
    begin--;
    while (*begin != ' ') begin++;
    obj_data->index_triangles[YI] = readNumberInt(&begin) - 1;
    begin--;
    while (*begin != ' ') begin++;
    obj_data->index_triangles[ZI] = readNumberInt(&begin) - 1;
    fgets(str, 100, fp);
  }
}
