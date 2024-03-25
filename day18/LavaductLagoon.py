import sys


def leggi_file(nome_file):
    with open(nome_file, "r") as file:
        contenuto = file.read()
    return contenuto


def stampa_matrice(matrice):
    for riga in matrice:
        if isinstance(riga[0], str):
            print("".join(riga))
        else:
            print(riga)


istructionsDirectionMap = {"R": (1, 0), "L": (-1, 0), "D": (0, 1), "U": (0, -1)}


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)

    print(testo)

    digPlan = testo.split("\n")

    position = (0, 0)

    stepCornerList = []

    perimeter = 0

    for step in digPlan:
        istructions = step.split(" ")
        print(istructions)

        numberSteps = int(istructions[1])

        directions = istructionsDirectionMap[istructions[0]]

        # for _ in range(numberSteps):
        #    position = (
        #        position[0] + (directions[0]),
        #        position[1] + (directions[1]),
        #    )

        #   stepCornerList.append(position)

        perimeter += numberSteps

        # position = (
        #    position[0] + (directions[0]),
        #    position[1] + (directions[1]),
        # )
        # stepCornerList.append(position)

        position = (
            position[0] + (directions[0] * (numberSteps)),
            position[1] + (directions[1] * (numberSteps)),
        )
        stepCornerList.append(position)

    stampa_matrice(stepCornerList)
    print(f"Perimeter: {perimeter}")
    stepCornerList.append(stepCornerList[0])

    ##Showlace formula
    sumA = 0
    sumB = 0
    for indexA in range(0, len(stepCornerList) - 1):
        indexB = indexA + 1
        sumA += stepCornerList[indexA][0] * stepCornerList[indexB][1]
        sumB += stepCornerList[indexA][1] * stepCornerList[indexB][0]

    area = abs(sumA - sumB) * 0.5 + (perimeter // 2) + 1

    print(f"Area is {area}")


if __name__ == "__main__":
    main()
