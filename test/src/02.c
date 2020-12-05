int f1(void) {
  int x;
  x = 1;
  if (x) {
    x = x + 2;
  }
  x = x + 3;
  return x;
}
int f2(void) {
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
int f3(void) {
  int x;
  x = 1;
  if (x) {
    x = x + 2;
  } else {
    x = x + 3;
  }
  return x;
}
int f4(void) {
  int x = 1;
  int y = x + 2;
  int z = y + 3;
  return z;
}
int f5(void) {
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
