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
#if 0
int f3(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    break;
  case 2:
    x = 2;
    break;
  case 3:
    x = 3;
    break;
  }
  return 0;
}
int f4(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    break;
  case 2:
    x = 2;
    break;
  default:
    x = 5;
    break;
  case 3:
    x = 3;
    break;
  case 4:
    x = 4;
    break;
  }
  return 0;
}
int f5(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
  case 2:
  default:
  case 3:
    x = 3;
    break;
  case 4:
    x = 4;
  }
  return 0;
}
int f6(void) {
  int x = 0;
  switch (x) {
  default:
    x = 1;
    return x;
  }
}
int f7(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    return x;
  }
  return 0;
}
int f8(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    break;
  case 2:
    x = 2;
    return x;
  case 3:
    x = 3;
    break;
  }
  return 0;
}
int f9(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
    return x;
  case 2:
    x = 2;
    return x;
  default:
    x = 5;
    return x;
  case 3:
    x = 3;
    return x;
  case 4:
    x = 4;
    return x;
  }
}
int f10(void) {
  int x = 0;
  switch (x) {
  case 1:
    x = 1;
  case 2:
  default:
  case 3:
    x = 3;
    return x;
  case 4:
    x = 4;
  }
  return 0;
}
#endif
