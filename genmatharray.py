import math
import matplotlib.pyplot as plt

def gen_array(func):
    for n in range(1024):
        n = round(func((float(n) / 1024.0)*math.pi*2) * 2**16)
        if n > 2**31 - 1 :
            n = 2**32 - 1
        if n < -(2**31) :
            n = -(2**31)
        if n < 0 :
            n += 2**32
        
        yield hex(n)

h = open("matharrays.h","w")

h.write(
"""#ifndef H_MATH_ARRAYS 
#define H_MATH_ARRAYS
#include <stdint.h>
#include <stddef.h>
""")

h.write("extern int32_t tan_a[1024];\n")

h.write("extern int32_t cot_a[1024];\n")

h.write("extern int32_t sin_a[1024];\n")

h.write("extern int32_t cos_a[1024];\n")

h.write("#endif")

h.close()

c = open("matharrays.c","w")

c.write(
"""#include <stdint.h>\n""")

c.write("int32_t tan_a[1024] = {")
c.write(", ".join(list(gen_array(lambda a: math.tan(a)))))
c.write("};\n")

c.write("int32_t cot_a[1024] = {")
c.write(", ".join(list(gen_array(lambda a: 1/math.tan(a) if math.tan(a) != 0 else 0xFFFFFFFF))))
c.write("};\n")

c.write("int32_t sin_a[1024] = {")
c.write(", ".join(list(gen_array(lambda a: math.sin(a)))))
c.write("};\n")

c.write("int32_t cos_a[1024] = {")
c.write(", ".join(list(gen_array(lambda a: math.cos(a)))))
c.write("};\n")

c.close()
