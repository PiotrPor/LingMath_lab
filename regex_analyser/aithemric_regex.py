import re

liczby = "25.2\n150\n-3\n0.05"
dzialanie = "20+1"
#my_regex = "(\d+)(\.\d+)?"
my_regex = "[\-]?[0-9]+[\.[0-9]+]?[[\+\-\*\/][\-]?[0-9]+[\.[0-9]+]?]*"
wynik = re.findall(my_regex, dzialanie)
print(dzialanie)
print("--------")
print(wynik)
