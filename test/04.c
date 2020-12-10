int f1(void) {
  int i = 0, s = 0;
  while (i - 10) {
    s = s + i;
    i = i + 1;
  }
  while (i) i = i - 1;
  return s;
}
int f2(void) {
  int i = 0, s = 0;
  do {
    s = s + i;
    i = i + 1;
  } while (i - 10);
  do i = i - 1; while (i);
  return s;
}
int f3(void) {
  int i = 0, s = 0;
  for (i = 0; i - 10; i = i + 1) {
    s = s + i;
  }
  return s;
}
