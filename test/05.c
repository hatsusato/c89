int f1(void) {
  int i = 0, s = 0;
begin:
  if (i - 10)
    goto end;
  else {
    s = s + i;
    i = i + 1;
    goto begin;
  }
end:
  return s;
}
int f2(void) {
  int i, j, c = 0;
  for (i = 0; i - 10; i = i + 1) {
    for (j = 0; j - 10; j = j + 1) {
      c = c + 1;
      if (c - 50) goto end;
    }
  }
end:
  return c;
}
int f3(void) {
  int x = 0;
  if (x) {
    goto error;
  }
  x = x + 1;
  if (x) {
    goto error;
  }
  x = x + 1;
  if (x) {
    goto error;
  }
  x = x + 1;
  return x;
error:
  return 0;
}
int f4(void) {
  int x = 0;
  switch (x) {
  case 0:
    goto case1;
  case 1:
    goto case2;
  case 2:
    goto case1;
  default:
    goto case2;
  case1:
    x = 1;
    break;
  case2:
    x = 2;
    break;
  }
  return x;
}
int f5(void) {
  int x = 0;
  switch (x) {
  case 0:
    goto case1;
  case 1:
    goto case2;
  case 2:
    goto case1;
  default:
    goto case2;
  case1:
    x = 1;
    goto end1;
  case2:
    x = 2;
    goto end2;
  }
end1:
  return x;
end2:
  return x;
}
