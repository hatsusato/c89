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
