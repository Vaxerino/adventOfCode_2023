sumOfAll = 0
with open("input.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        firstDigit = 0
        secondDigit = 0
        for c in line:
            if 0 <= ord(c) - ord('0') <= 9:
                firstDigit = ord(c) - ord('0')
                break
        for c in reversed(line):
            if 0 <= ord(c) - ord('0') <= 9:
                secondDigit = ord(c) - ord('0')
                break
        sumOfAll += firstDigit * 10 + secondDigit
print(sumOfAll)
