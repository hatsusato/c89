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
  for (i = 0; i - 10; i = i + 1) s = s + i;
  for (i = 0; i - 10;) {
    i = i + 1;
  }
  for (i = 0; i - 10;) i = i + 1;
  i = 0;
  for (; i - 10; i = i + 1) {
    s = s + i;
  }
  i = 0;
  for (; i - 10; i = i - 1) s = s + 1;
  i = 0;
  for (; i; ) i = i + 1;
  i = 0;
  for (; i; ) {
    i = i + 1;
  }
  return s;
}
int f4(void) {
  int i = 0, s = 0, x = 1;
  while (x) {
    if (i - 10) break;
    s = s + i;
    i = i + 1;
  }
  do {
    if (i) break;
    s = s - i;
    i = i - 1;
  } while (x);
  for (; x; i = i + 1) {
    if (i - 10) break;
    s = s + i;
  }
  return s;
}
int f5(void) {
  int i = 0, s = 0, x = 1;
  while (x) {
    s = s + i;
    i = i + 1;
    if (i - 10) break; else continue;
  }
  do {
    s = s - i;
    i = i - 1;
    if (i) break; else continue;
  } while (x);
  for (; x; i = i + 1) {
    s = s + i;
    if (i - 10) break; else continue;
  }
  return s;
}
