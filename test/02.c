int f1(void) {
  int x = 1;
  if (x) {
    x = x + 2;
    if (x) {
      x = x + 3;
    }
    x = x + 4;
  }
  x = x + 5;
  return x;
}
int f2(void) {
  int x = 0;
  if (x) {
    x = x + 1;
  } else {
    x = x + 2;
  }
  x = x + 3;
  return x;
}
int f3(void) {
  int x = 0;
  if (x) {
    x = x + 1;
  } else if (x) {
    x = x + 2;
  } else {
    x = x + 3;
  }
  x = x + 4;
  return x;
}
int f4(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    if (x) {
      x = x + 2;
      return x + 3;
    }
    x = x + 4;
  }
  x = x + 5;
  return x + 6;
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
int f6(void) {
  int x = 1;
  if (x) {
    int y = x + 2;
    if (y) {
      int z = y + 3;
      return z;
    }
    return y;
  } else {
    return x;
  }
}
int f7(void) {
  int x = 1;
  if (x) {
    int y = x + 2;
    int x = y + 2;
    if (y) {
      int z = y + 3;
      int x = z + 3;
      return x;
    }
    return x;
  } else {
    return x;
  }
}
