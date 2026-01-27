# ask user for height
while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
    except ValueError:
        pass

# print column
for i in range(height):
    # print spaces for left pyramid
    for j in range(height - i - 1):
        print(" ", end="")
    # print bricks for left pyramid
    for k in range(i + 1):
        print("#", end="")
    # print two spaces to separate
    print("  ", end="")
    # print bricks for right pyramid
    print("#" * (i + 1))
