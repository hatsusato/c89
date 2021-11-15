int f1(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    if (x) {
      x = x + 2;
    }
    x = x + 3;
  }
  x = x + 4;
  return x;
}
int f2(void) {
  int x = 0;
  if (x) {
    x = x + 1;
  } else {
    x = x + 2;
  }
  return x;
}
int f3(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    if (x) {
      x = x + 2;
    } else {
      x = x + 3;
    }
  }
  return x;
}
int f4(void) {
  int x = 0;
  if (x) {
    x = x + 1;
  } else if (x) {
    x = x + 2;
  } else {
    x = x + 3;
  }
  return x;
}
int f5(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    if (x) {
      x = x + 2;
      return x;
    }
    x = x + 3;
  }
  x = x + 4;
  return x;
}
int f6(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    if (x) {
      x = x + 2;
    } else {
      x = x + 3;
      return x;
    }
  }
  return x;
}
int f7(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    return x;
  } else {
    x = x + 2;
    return x;
  }
}
int f8(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    return x;
  } else if (x) {
    x = x + 2;
    return x;
  } else {
    x = x + 3;
    return x;
  }
}
int f9(void) {
  int x = 0;
  if (x) {
    x = x + 1;
    if (x) {
      x = x + 2;
      if (x) {
        x = x + 4;
      } else {
        return x;
      }
      return x;
    } else {
      if (x) {
        x = x + 4;
        return x;
      } else {
        return x;
      }
    }
  } else {
    if (x) {
      x = x + 2;
      if (x) {
        x = x + 4;
      } else {
        return x;
      }
    } else {
      if (x) {
        x = x + 4;
      } else {
        return x;
      }
      return x;
    }
  }
  return x;
}
