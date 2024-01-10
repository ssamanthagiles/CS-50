# implementing this while loop, in order to ensure that the input the user enters is between 1 & 8
# this while loop prompts the user again if the height they input is above 8 or below 1
while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        continue


# prints a right aligned triangle depending on the HEIGHT that is inputed by the user
for i in range(height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1))

# startded during section on 10/25 and finished on 10/25
