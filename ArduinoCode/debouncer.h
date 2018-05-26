#ifndef _DEBOUNCERH_
#define _DEBOUNCERH_

boolean debouncehunger(boolean last, int *button)
{
  boolean current=digitalRead(*button);
  if (last!=current)
  {
    delay(5);
    current=digitalRead(*button);
  }
  return current;
}

#endif
