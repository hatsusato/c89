int f1(void) {
  return 10;
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
  int x = 1, y = 2, z;
  z = x + y;
  return x + y + z;
}
