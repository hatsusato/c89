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
