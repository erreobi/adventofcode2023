import sys
import time

NOTHING = 0b00000000
RIGHT = 0b11000000
LEFT = 0b00110000
DOWN = 0b00001100
UP = 0b00000011

EMPTY_SPACE = "."
MIRROR_RX = "/"
MIRROR_SX = "\\"
SPLIT_V = "|"
SPLIT_H = "-"


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


# given a position and a direction, it returns the new position.
def getDirection(row, col, direction):
    if (direction & UP) == UP:
        return ((row - 1), col)
    elif (direction & DOWN) == DOWN:
        return ((row + 1), col)
    elif (direction & LEFT) == LEFT:
        return (row, (col - 1))
    elif (direction & RIGHT) == RIGHT:
        return (row, (col + 1))

    return (row, col)


# diven a mirron, a direction and position, it returns the new position and direction
def mirroring(row, col, mirror, direction):
    if mirror == MIRROR_RX:  # /
        if (direction & UP) == UP:
            return (row, col + 1, RIGHT)
        elif (direction & DOWN) == DOWN:
            return (row, col - 1, LEFT)
        elif (direction & LEFT) == LEFT:
            return (row + 1, col, DOWN)
        elif (direction & RIGHT) == RIGHT:
            return (row - 1, col, UP)
    elif mirror == MIRROR_SX:  # \
        if (direction & UP) == UP:
            return (row, col - 1, LEFT)
        elif (direction & DOWN) == DOWN:
            return (row, col + 1, RIGHT)
        elif (direction & LEFT) == LEFT:
            return (row - 1, col, UP)
        elif (direction & RIGHT) == RIGHT:
            return (row + 1, col, DOWN)

    return row, col, direction


totCell = 0


def beams_recursive(startRow, startCol, direction):
    global empty_grid
    global grid
    global totCell

    row = startRow
    col = startCol

    if row < 0 or row >= len(grid):
        return

    if col < 0 or col >= len(grid[0]):
        return

    if (empty_grid[row][col] & direction) != 0:
        return  # it already passed here

    if empty_grid[row][col] == NOTHING:
        totCell += 1

    empty_grid[row][col] |= direction

    if grid[row][col] == EMPTY_SPACE:
        row, col = getDirection(startRow, startCol, direction)
        beams(row, col, direction)
    elif grid[row][col] == MIRROR_RX or grid[row][col] == MIRROR_SX:
        row, col, newDirection = mirroring(row, col, grid[row][col], direction)
        beams(row, col, newDirection)
    elif grid[row][col] == SPLIT_H:
        if (direction & LEFT) == LEFT or (direction & RIGHT) == RIGHT:
            row, col = getDirection(startRow, startCol, direction)
            beams(row, col, direction)
        else:
            beams(row, col - 1, LEFT)
            beams(row, col + 1, RIGHT)
    else:  ##grif[row][col] == SPLIT_V:
        if (direction & UP) == UP or (direction & DOWN) == DOWN:
            row, col = getDirection(startRow, startCol, direction)
            beams(row, col, direction)
        else:
            beams(row - 1, col, UP)
            beams(row + 1, col, DOWN)


def beams(startRow, startCol, startDirection):
    global empty_grid
    global grid
    global totCell

    row = startRow
    col = startCol
    direction = startDirection

    while (
        row >= 0
        and row < len(grid)
        and col >= 0
        and col < len(grid[row])
        and ((empty_grid[row][col] & direction) == 0)
    ):
        if empty_grid[row][col] == NOTHING:
            totCell += 1

        empty_grid[row][col] |= direction

        if grid[row][col] == EMPTY_SPACE:
            row, col = getDirection(row, col, direction)
        elif grid[row][col] == MIRROR_RX or grid[row][col] == MIRROR_SX:
            row, col, direction = mirroring(row, col, grid[row][col], direction)
        elif grid[row][col] == SPLIT_H:
            if (direction & LEFT) == LEFT or (direction & RIGHT) == RIGHT:
                row, col = getDirection(row, col, direction)
            else:
                beams(row, col - 1, LEFT)
                beams(row, col + 1, RIGHT)
        else:  ##grif[row][col] == SPLIT_V:
            if (direction & UP) == UP or (direction & DOWN) == DOWN:
                row, col = getDirection(row, col, direction)
            else:
                beams(row - 1, col, UP)
                beams(row + 1, col, DOWN)


empty_grid = []
grid = []


def main():
    global empty_grid
    global grid

    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)

    grid = [
        list(row) for row in (testo.strip().split("\n"))
    ]  # Convert strings to lists
    stampa_matrice(grid)

    print(f"RIGTH: {RIGHT} {bin(RIGHT)}")
    print(f"LEFT:  {LEFT} {bin(LEFT)}")
    print(f"DOWN:  {DOWN} {bin(DOWN)}")
    print(f"UP:    {UP} {bin(UP)}")

    for index in range(len(grid)):
        empty_grid.append([NOTHING] * len(grid[index]))

    stampa_matrice(empty_grid)

    start = time.process_time()

    beams(0, 0, RIGHT)

    stampa_matrice(empty_grid)

    print(f"ONE BEAM: {time.process_time()-start}")

    print(f"Max rows: {len(grid)}")
    print(f"Max col: {len(grid[0])}")

    print(f"Energised cells is {totCell}")


if __name__ == "__main__":
    main()
