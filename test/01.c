int f1(void) {
  return 10;
}
#if 0
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
  int x = 1, y = 2, z = x + y;
  return x + y + z;
}
int f6(void) {
  int x = 0;
  {
    int x = 1;
    {
      int x = 2;
    }
  }
  return x;
}
int g5, g6 = 6, g7;
int g8 = 8, g9;
int f7(void) {
  int x = g7;
  {
    int x = g8;
    {
      int x = g9;
    }
  }
  return x;
}
int g1;
int g2, g3;
int g4 = 4;
#endif
