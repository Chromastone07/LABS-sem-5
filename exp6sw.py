
import random

def go_back_n(frames, window):
    print("\n--- Go-Back-N ---")
    base = 0
    while base < frames:
        end = min(base + window, frames)
        print(f"\nSending frames {list(range(base, end))}")

        lost = random.randint(base, end - 1)
        print(f"Frame {lost} lost!")

        print(f"Retransmitting from frame {lost}")
        base = lost + 1   

    print("GBN: All frames delivered.\n")


def selective_repeat(frames, window):
    print("\n--- Selective Repeat ---")
    received = [False] * frames
    i = 0

    while not all(received):
        end = min(i + window, frames)
        print(f"\nWindow: {list(range(i, end))}")

        for f in range(i, end):
            if received[f]:
                continue
            if random.choice([True, False]):
                print(f"Frame {f} lost! Retransmitting later.")
            else:
                print(f"Frame {f} received ✓")
                received[f] = True

        while i < frames and received[i]:
            i += 1

    print("SR: All frames delivered.\n")


frames = int(input("Enter number of frames: "))
window = int(input("Enter window size: "))

go_back_n(frames, window)
selective_repeat(frames, window)
