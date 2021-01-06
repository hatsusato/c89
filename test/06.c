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
