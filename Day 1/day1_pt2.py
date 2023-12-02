import regex as re

numberMap = {"one": "1", "two": "2", "three": "3", "four": "4", "five": "5", "six": "6", "seven": "7", "eight": "8",
             "nine": "9"}
numberWords = '|'.join(numberMap.keys())
words = f"(\d)|({numberWords})"

sumOfAll = 0
with open("input.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        matches = re.findall(words, line, overlapped=True)
        line = "".join(["".join(m) for m in matches])
        number = re.sub(numberWords, lambda m: numberMap[m.group(0)], line)
        sumOfAll += 10 * int(number[0]) + int(number[-1])

print(sumOfAll)
