

def encode_7_4(data_bits):
    d1, d2, d3, d4 = data_bits
    p1 = d1 ^ d2 ^ d4        
    p2 = d1 ^ d3 ^ d4        
    p4 = d2 ^ d3 ^ d4        
    code = [p1, p2, d1, p4, d2, d3, d4]
    return code

def syndrome_for(code):
    p1, p2, d1, p4, d2, d3, d4 = code
    s1 = p1 ^ d1 ^ d2 ^ d4  
    s2 = p2 ^ d1 ^ d3 ^ d4   
    s4 = p4 ^ d2 ^ d3 ^ d4  
    syndrome = (s4 << 2) | (s2 << 1) | s1
    return syndrome, (s1, s2, s4)

def flip_bit(code, position):
    idx = position - 1
    code[idx] = 0 if code[idx] == 1 else 1

def input_4bits(prompt="Enter 4-bit data (e.g. 1011): "):
    while True:
        s = input(prompt).strip()
        if len(s) == 4 and all(ch in "01" for ch in s):
            return [int(ch) for ch in s]
        print("Invalid input. Enter exactly 4 bits (0/1).")

def main():
    print("Hamming (7,4) Encoder + Decoder\n")
    data = input_4bits()
    print("Data bits (d1 d2 d3 d4):", " ".join(map(str, data)))

    code = encode_7_4(data)
    print("Encoded Hamming (positions 1..7):", " ".join(map(str, code)))

    choice = input("\nDo you want to inject an error? (y/n) [n]: ").strip().lower() or "n"
    if choice == "y":
        mode = input("Choose 'm' manual flip or 'r' random flip [r]: ").strip().lower() or "r"
        if mode == "m":
            while True:
                pos = input("Enter bit position to flip (1-7): ").strip()
                if pos.isdigit() and 1 <= int(pos) <= 7:
                    pos = int(pos)
                    break
                print("Enter a number 1..7.")
        else:
            import random
            pos = random.randint(1,7)
        flip_bit(code, pos)
        print(f"Injected error: flipped bit at position {pos}")
        print("Corrupted code:", " ".join(map(str, code)))
    else:
        print("No error injected. Transmitted code is clean.")

    syndrome, (s1, s2, s4) = syndrome_for(code)
    print("\nReceiver computes syndrome bits (s1,s2,s4):", s1, s2, s4)
    if syndrome == 0:
        print("Syndrome = 0 -> No error detected.")
        corrected = code[:] 
    else:
        print("Syndrome (decimal) =", syndrome, "-> Error at position", syndrome)
        corrected = code[:]
        flip_bit(corrected, syndrome)
        print("Corrected code:", " ".join(map(str, corrected)))

    
    d1 = corrected[2]
    d2 = corrected[4]
    d3 = corrected[5]
    d4 = corrected[6]
    print("\nRecovered data bits (d1 d2 d3 d4):", d1, d2, d3, d4)
    print("Done.")

if __name__ == "__main__":
    main()
