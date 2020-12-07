int f1(void) {
  int x = 1;
  switch (x) {
  default:
    break;
  }
  return x;
}
int f2(void) {
  int x = 1;
  switch (x) {
  default:
    return x;
  }
}
int f3(void) {
  int x = 1;
  switch (x) {
  case 0:
    return x;
  }
  return 0;
}
int f4(void) {
  int x = 1;
  switch (x) {
  case 0:
    break;
  }
  return 0;
}
int f5(void) {
  int x = 1;
  switch (x) {
  case 0:
    break;
  case 1:
    break;
  }
  return 0;
}
int f6(void) {
  int x = 1;
  switch (x) {
  case 0:
  case 1:
    x = x + 1;
    x = x + 1;
  case 2:
  case 3:
    x = x + 1;
    break;
  }
  return 0;
}
int f7(void) {
  int x = 1;
  switch (x) {
  case 0:
  case 1:
    x = x + 1;
    x = x + 1;
  case 2:
  default:
  case 3:
    x = x + 1;
    break;
  }
  return 0;
}
int f8(void) {
  int x = 1;
  switch (x) {
  case 0:
  default:
  case 1:
    return x;
  }
}
