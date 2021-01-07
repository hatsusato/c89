void f1(void) {
  int x = 3;
  x = x + x;
}
void f2(void) {
  int x = 3;
  x = x + x;
  return;
}
void f3(void) {
  int x = 3;
  if (x) {
    return;
  } else {
    return;
  }
}
long f4(void) {
  char c = 1;
  short s = 2;
  int i = 3;
  long l = 4;
  switch (c) {
  case 1:
    return c;
  case 2:
    return s;
  case 3:
    return i;
  case 4:
    return l;
  default:
    return 0;
  }
}
