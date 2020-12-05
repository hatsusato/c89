int f1(void) {
  return 100;
}
int f2(void) {
  int x;
  x = 2;
  return 1 + x + 3;
}
int f3(void) {
  int x;
  x = 2;
  x = 1 + x + 3;
  return x + 4;
}
int f4(void) {
  int x;
  int y;
  int z;
  x = 1;
  y = 2 + x;
  z = x + y;
  return x + y + z;
}
int f5(void) {
  int x;
  x = 1;
  if (x) {
    x = x + 2;
  }
  x = x + 3;
  return x;
}
int f6(void) {
  int x;
  x = 1;
  if (x) {
    x = x + 2;
    if (x) {
      x = x + 3;
    }
  }
  x = x + 4;
  return x;
}
int f7(void) {
  int x;
  x = 1;
  if (x) {
    x = x + 2;
  } else {
    x = x + 3;
  }
  return x;
}
int f8(void) {
  int x = 1;
  int y = x + 2;
  int z = y + 3;
  return z;
}
int f9(void) {
  int x = 1;
  if (x) {
    int y = x + 2;
    if (y) {
      int z = y + 3;
      return z;
    }
    return y;
  }
  return x;
}
