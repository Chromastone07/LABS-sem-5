data = input("Enter dataword: ")
poly = input("Enter polynomial: ")

data = data + "0"*(len(poly)-1)

def xor(a, b):
    result = ""
    for i in range(1, len(b)):
        result += "0" if a[i] == b[i] else "1"
    return result

temp = data[0:len(poly)]
i = len(poly)

while i < len(data):
    if temp[0] == "1":
        temp = xor(poly, temp) + data[i]
    else:
        temp = xor("0"*len(poly), temp) + data[i]
    i += 1

if temp[0] == "1":
    temp = xor(poly, temp)

print("CRC remainder:", temp)
print("Transmitted frame:", data[:len(data)-(len(poly)-1)] + temp)
