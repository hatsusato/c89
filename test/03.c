int f1(void) {
  int x = 0;
  switch (x) {
  default:
    x = 1;
    break;
  }
  return 0;
}
int f2(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    break;
  }
  return 0;
}
int f3(void) {
  int x = 0;
  switch (x) {
  default:
    x = 10;
  case 1:
    x = 1;
    return x;
  case 2:
    x = 2;
    break;
  case 3:
    x = 3;
  }
  return 0;
}
int f4(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
  case 2:
  case 3:
  case 4:
  default:
  case 5:
    x = 5;
  }
  return 0;
}
int f5(void) {
  int x = 0;
  switch (x) {
  default:
    x = 1;
    return x;
  }
  return 0;
}
int f6(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    return x;
  }
  return 0;
}
int f7(void) {
  int x = 0;
  switch (x) {
  default:
    x = 10;
  case 1:
    x = 1;
    return x;
  case 2:
    x = 2;
  case 3:
    x = 3;
    return x;
  }
  return 0;
}
int f8(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
  case 2:
  case 3:
  case 4:
  default:
  case 5:
    x = 5;
    return x;
  }
  return 0;
}
