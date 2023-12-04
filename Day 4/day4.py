def part1():
    sumOfAll = 0
    with open("input.txt", "r") as f:
        lines = f.readlines()
        for line in lines:
            winning, yours = line.split(":")[1].split("|")
            winning = [int(num) for num in winning.split()]
            yours = [int(num) for num in yours.split() if int(num) in winning]
            sumOfAll += 2 ** (len(yours) - 1) if len(yours) > 0 else 0
    print(sumOfAll)


def part2():
    with open("input.txt", "r") as f:
        lines = f.readlines()
        lines = [[1, line] for line in lines]
        for i, line in enumerate(lines):
            winning, yours = line[1].split(":")[1].split("|")
            winning = [int(num) for num in winning.split()]
            yours = [int(num) for num in yours.split() if int(num) in winning]
            for card in lines[i + 1:i + len(yours) + 1]:
                card[0] += line[0]

        print(sum([count for count, _ in lines]))


if __name__ == '__main__':
    part1()
    part2()
