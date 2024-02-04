import sys

# mywindow = curses.initscr()

def leggi_file(nome_file):
    with open(nome_file, 'r') as file:
        contenuto = file.read()
    return contenuto

ROUNDED_ROCK='O'
SQUARE_ROCK='#'
NOTHING='.'

def stampa_matrice(matrice):
    print('\n')
    for riga in matrice:                    
        print(''.join(riga))

# def stampa_matrice(stdscr, matrice):
#     # stdscr.clear()
#     for y, riga in enumerate(matrice):
#         for x, cella in enumerate(riga):
#             stdscr.addch(y, x, cella)
#     stdscr.refresh()

def moveRockDown (platform, row, col, train_of_rock):
    for indexRock in range(0, len(train_of_rock)):
        for searchIndex in range(row, train_of_rock[indexRock]):
            if (searchIndex >= train_of_rock[indexRock]):
                return; #if therearent any point between NOTHING and the last ROUNDROCK, it can be stopped
            if(platform[searchIndex][col] == NOTHING ):
                platform[searchIndex][col] = ROUNDED_ROCK
                platform[train_of_rock[indexRock]][col] = NOTHING
                stampa_matrice(platform)
                break;

def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)
    print(testo)

    platform = testo.strip().split('\n')  # Dividi le matrici usando le linee vuote come separatore
    platform = [list(row) for row in platform]  # Convert strings to lists
    train_of_rock=[] #list of index of rock that need to moved
    # stampa_matrice(stdscr,platform)
   
    for col in range(0, len(platform[0])):
     for row in reversed(range(0,len(platform))):
        if (row == 0):
                moveRockDown(platform, row, col, train_of_rock)
                train_of_rock.clear()
        else:
            if (platform[row][col]==SQUARE_ROCK):
                #flush all the rocke there
                    moveRockDown(platform, row+1, col, train_of_rock)
                    train_of_rock.clear();
            else:  
                if (platform[row][col]==ROUNDED_ROCK):
                    #remember his index
                    train_of_rock.append(row)

    stampa_matrice(platform)

    tot = 0
    for row in range(0, len(platform)):
        for col in range(0, len(platform[row])):
            if (platform[row][col]==ROUNDED_ROCK):
                tot += len(platform)-row

    print(f'LOAD: {tot}')

if __name__ == "__main__":
   main()
