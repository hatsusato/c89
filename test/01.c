int f1(void) {
  return 10;
}
int f2(void) {
  int x;
  x = 2;
  return x;
}
int f3(void) {
  int x;
  x = 2;
  x = x + 3;
  x = x + 4 + 5 + 6;
  return 1 + 2 + 3 + x;
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
int g8;
int g15;
int g1 = 1;
int g2 = 2;
int g10, g16, g9;
int g3 = 3, g11, g4 = 4;
int g5 = 5, g6 = 6, g7 = 7;
int f7(void) {
  int x1 = g8;
  int x2 = g1;
  int x4 = g9;
  int x3 = g10;
  int x6 = g11;
  int x5 = g3;
  int x7 = g7;
  return g5;
}
int g17;
int g12 = 12;
int g18, g19;
int g13 = 13, g14 = 14;
