from multiprocessing import Pool


def solvePt1():
    lowestSpot = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    for seed in seeds:
        ind = seed
        for elem in maps:
            for key in elem:
                if ind in key:
                    ind = elem[key].start + key.index(ind)
                    break
        lowestSpot = min(lowestSpot, ind)
    print(lowestSpot)


def findLowestSpot(seed):
    lowestSpot = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    for i in seed:
        ind = i
        for elem in maps:
            for key in elem:
                if ind in key:
                    ind = elem[key].start + key.index(ind)
                    break
        lowestSpot = min(lowestSpot, ind)
    print("processed", seed)
    return lowestSpot


def solvePt2():
    ranges = [range(seeds[i], sum(seeds[i:i + 2]), 1) for i in range(0, len(seeds), 2)]
    # split all ranges into 32 chunks
    ranges = [range(r.start + i * (r.stop - r.start) // 32, r.start + (i + 1) * (r.stop - r.start) // 32, 1) for r in
              ranges for i in range(32)]
    print(len(ranges))
    #  brute force for all ranges in parallel, should do path compression, but I'm lazy
    with Pool() as p:
        lowestSpot = min(p.map(findLowestSpot, ranges))
    print(lowestSpot)


if __name__ == '__main__':
    with open("input.txt", "r") as f:
        lines = f.readlines()
        seeds = [int(num) for num in lines[0].split(":")[1].split()]

        maps: list[dict[range, range]] = [{}, {}, {}, {}, {}, {}, {}]
        currMap = 0
        for line in lines[3:]:
            if line.startswith("\n"):
                continue
            if ":" in line:
                currMap += 1
                continue
            dest, src, l = map(int, line[:-1].split(" "))
            maps[currMap][range(src, src + l, 1)] = range(dest, dest + l, 1)

    solvePt1()
    solvePt2()
