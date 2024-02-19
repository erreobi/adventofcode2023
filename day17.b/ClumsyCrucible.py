import sys
import heapq

city_map = []
path_heath_end = int(sys.maxsize)
GOAL = (0, 0)
passed_for_here_already_list = {}


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


def stampa_mappa():
    mappa = []
    for index in range(len(city_map)):
        mappa.append(["***"] * len(city_map[index]))

    for x in passed_for_here_already_list.keys():
        row = int(x[0])
        col = int(x[1])
        value = passed_for_here_already_list.get(x)

        if value is not None:
            if mappa[row][col] == "***" or value < int(mappa[row][col]):
                mappa[row][col] = f"{value:03d}"

    print("--------")
    for row in range(len(mappa)):
        to_string = f"{row} |  "
        for col in range(len(mappa[row])):
            to_string += mappa[row][col] + " "
        print(to_string)


NO_DIR = -1
LEFT = 0
RIGHT = 1
DOWN = 2
UP = 3


def maxValue(row, col):
    max_row = len(city_map) - row - 1
    max_col = len(city_map[0]) - col - 1
    return max_row + max_col


def move_to(
    routes_to_check,
    new_row,
    new_col,
    old_direction,
    new_direction,
    number_steps,
    cost_so_far,
):
    global city_map
    global path_heath_end
    global passed_for_here_already_list

    # print(f" -> Possible path: { (new_row, new_col, new_direction, number_steps)}")

    path_heath_to = cost_so_far + city_map[new_row][new_col]

    if (new_row, new_col) == GOAL:
        if path_heath_to < path_heath_end:
            path_heath_end = path_heath_to
            passed_for_here_already_list[
                (new_row, new_col, new_direction, number_steps)
            ] = path_heath_to
        # print("  --> FOUND  a SOLUTION ")
        return

    max_end_value_so_far = path_heath_end - cost_so_far
    if max_end_value_so_far < 0:
        #   print(
        #       f"The value is already bigger than the max end value. {cost_so_far} > path_heath_end"
        # )
        return

    if old_direction == new_direction:
        number_steps += 1
    else:
        number_steps = 1

    passed_already_there = passed_for_here_already_list.get(
        (new_row, new_col, new_direction, number_steps)
    )

    if passed_already_there is None or passed_already_there > path_heath_to:
        passed_for_here_already_list[
            (new_row, new_col, new_direction, number_steps)
        ] = path_heath_to
    else:
        #   print(
        #   f"Passed already there BUT I have a worst value{(new_row,new_col,new_direction, number_steps)} = {passed_already_there}"
        # )Best Heath Path is 742 with 213593848 cicles
        # Best Heath Path is 742 with   41705763 ciclesi
        return
    # print(
    #    f"Adding it to the list of path: {(new_row, new_col, number_steps, new_direction, path_heath_to)}"
    # )
    heapq.heappush(
        routes_to_check, (new_row, new_col, number_steps, new_direction, path_heath_to)
    )

    # routes_to_check.append(
    #    (new_row, new_col, number_steps, new_direction, path_heath_to)
    # )


def main():
    global city_map
    global path_heath_end
    global GOAL

    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)

    city_map = [
        [int(char) for char in row] for row in (testo.strip().split("\n"))
    ]  # Convert strings to lists
    stampa_matrice(city_map)

    GOAL = (len(city_map) - 1, len(city_map[0]) - 1)

    routes_to_check = [
        (0, 1, 1, RIGHT, city_map[0][1]),
        (1, 0, 1, DOWN, city_map[1][0]),
    ]

    passed_for_here_already_list[(0, 0, NO_DIR, 0)] = 2
    passed_for_here_already_list[(0, 1, RIGHT, 1)] = city_map[0][1]
    passed_for_here_already_list[(1, 0, DOWN, 1)] = city_map[1][0]

    path_heath_end = int(sys.maxsize)

    how_many_routes_I_m_counting: int = 0
    while len(routes_to_check) > 0:
        how_many_routes_I_m_counting += 1
        # row = routes_to_check[0][0]
        # col = routes_to_check[0][1]
        # same_direction_steps = routes_to_check[0][2]
        # direction = routes_to_check[0][3]
        # cost_so_far = routes_to_check[0][4]

        # routes_to_check.pop(0)
        x = heapq.heappop(routes_to_check)

        # print(f"Condiring this path: {x}")

        row = x[0]
        col = x[1]
        same_direction_steps = x[2]
        direction = x[3]
        cost_so_far = x[4]

        if cost_so_far >= path_heath_end:
            # print(" --> Too big ... continue ")
            continue

        if col < 0 or row < 0:
            continue

        if col >= len(city_map[row]) or row >= len(city_map):
            continue

        can_go_left = False
        can_go_right = False
        can_go_up = False
        can_go_down = False

        if direction == LEFT:
            if same_direction_steps < 4:
                if (col - 4 + same_direction_steps) > 0:
                    can_go_left = True
            else:
                if same_direction_steps < 10:
                    # I can consider all the 4 direction.
                    if col > 0:
                        can_go_left = True

                if (row - 4) >= 0:
                    can_go_up = True

                if (row + 4) <= (len(city_map) - 1):
                    can_go_down = True

                can_go_right = False

        elif direction == RIGHT:
            if same_direction_steps < 4:
                if (col + 4 - same_direction_steps) <= (len(city_map[row]) - 1):
                    can_go_right = True
            else:
                if same_direction_steps < 10:
                    # I can consider all the 4 direction.
                    if col < (len(city_map[row]) - 1):
                        can_go_right = True

                if (row - 4) >= 0:
                    can_go_up = True

                if (row + 4) <= (len(city_map) - 1):
                    can_go_down = True

                can_go_left = False

        elif direction == UP:
            if same_direction_steps < 4:
                if (row - 4 + same_direction_steps) >= 0:
                    can_go_up = True
            else:
                if same_direction_steps < 10:
                    # I can consider all the 4 direction.
                    if row > 0:
                        can_go_up = True

                if (col + 4) <= (len(city_map[row]) - 1):
                    can_go_right = True

                if (col - 4) >= 0:
                    can_go_left = True

                can_go_down = False

        elif direction == DOWN:
            if same_direction_steps < 4:
                if (row + 4 - same_direction_steps) <= (len(city_map) - 1):
                    can_go_down = True
            else:
                if same_direction_steps < 10:
                    # I can consider all the 4 direction.
                    if row < (len(city_map) - 1):
                        can_go_down = True

                if (col + 4) <= (len(city_map[row]) - 1):
                    can_go_right = True

                if (col - 4) >= 0:
                    can_go_left = True

                can_go_up = False

        if can_go_right:
            move_to(
                routes_to_check,
                row,
                col + 1,
                direction,
                RIGHT,
                same_direction_steps,
                cost_so_far,
            )
        if can_go_down:
            move_to(
                routes_to_check,
                row + 1,
                col,
                direction,
                DOWN,
                same_direction_steps,
                cost_so_far,
            )
        if can_go_left:
            move_to(
                routes_to_check,
                row,
                col - 1,
                direction,
                LEFT,
                same_direction_steps,
                cost_so_far,
            )
        if can_go_up:
            move_to(
                routes_to_check,
                row - 1,
                col,
                direction,
                UP,
                same_direction_steps,
                cost_so_far,
            )

        # stampa_matrice_dir(city_routes)
        # stampa_mappa()

    print("-----------")
    print(
        f"Best Heath Path is {path_heath_end} with {how_many_routes_I_m_counting} cicles"
    )


if __name__ == "__main__":
    main()
