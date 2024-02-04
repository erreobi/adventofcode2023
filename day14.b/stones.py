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

def moveRockNorth (platform, row, col, train_of_rock):
    for indexRock in range(0, len(train_of_rock)):
        for searchIndex in range(row, train_of_rock[indexRock]):
            if (searchIndex >= train_of_rock[indexRock]):
                return; #if therearent any point between NOTHING and the last ROUNDROCK, it can be stopped
            if(platform[searchIndex][col] == NOTHING ):
                platform[searchIndex][col] = ROUNDED_ROCK
                platform[train_of_rock[indexRock]][col] = NOTHING
                # stampa_matrice(platform)
                break;

def moveRockSouth (platform, row, col, train_of_rock):
    for indexRock in range(0, len(train_of_rock)):
        for searchIndex in reversed(range(train_of_rock[indexRock], row+1)):
            if (searchIndex <= train_of_rock[indexRock]):
                return; #if therearent any point between NOTHING and the last ROUNDROCK, it can be stopped
            if(platform[searchIndex][col] == NOTHING ):
                platform[searchIndex][col] = ROUNDED_ROCK
                platform[train_of_rock[indexRock]][col] = NOTHING
                # stampa_matrice(platform)
                break;

def moveRockWest (platform, row, col, train_of_rock):
    for indexRock in range(0, len(train_of_rock)):
        for searchIndex in range(col, train_of_rock[indexRock]):
            if (searchIndex >= train_of_rock[indexRock]):
                return; #if therearent any point between NOTHING and the last ROUNDROCK, it can be stopped
            if(platform[row][searchIndex] == NOTHING ):
                platform[row][searchIndex] = ROUNDED_ROCK
                platform[row][train_of_rock[indexRock]] = NOTHING
                # stampa_matrice(platform)
                break;

def moveRockEast (platform, row, col, train_of_rock):
    for indexRock in range(0, len(train_of_rock)):
        for searchIndex in reversed(range(train_of_rock[indexRock],col+1)):
            if (searchIndex <= train_of_rock[indexRock]):
                return; #if therearent any point between NOTHING and the last ROUNDROCK, it can be stopped
            if(platform[row][searchIndex] == NOTHING ):
                platform[row][searchIndex] = ROUNDED_ROCK
                platform[row][train_of_rock[indexRock]] = NOTHING
                # stampa_matrice(platform)
                break;

def cicle (platform):
    train_of_rock=[] #list of index of rock that need to moved
    # stampa_matrice(stdscr,platform)
   
#    moving north
    for col in range(0, len(platform[0])):
     for row in reversed(range(0,len(platform))):
        if (row == 0):
                moveRockNorth(platform, row, col, train_of_rock)
                train_of_rock.clear()
        else:
            if (platform[row][col]==SQUARE_ROCK):
                #flush all the rocke there
                    moveRockNorth(platform, row+1, col, train_of_rock)
                    train_of_rock.clear();
            else:  
                if (platform[row][col]==ROUNDED_ROCK):
                    #remember his index
                    train_of_rock.append(row)

    # stampa_matrice(platform)

    #    moving west
    for row in range(0,len(platform)):
        for col in reversed(range(0, len(platform[row]))):
            if (col == 0):
                    moveRockWest(platform, row, col, train_of_rock)
                    train_of_rock.clear()
            else:
                if (platform[row][col]==SQUARE_ROCK):
                    #flush all the rocke there
                        moveRockWest(platform, row, col+1, train_of_rock)
                        train_of_rock.clear();
                else:  
                    if (platform[row][col]==ROUNDED_ROCK):
                        #remember his index
                        train_of_rock.append(col)

    # stampa_matrice(platform)

    # moving sourh
    for col in range(0, len(platform[0])):
     for row in (range(0,len(platform))):
        if (row == (len(platform)-1)):
                moveRockSouth(platform, row, col, train_of_rock)
                train_of_rock.clear()
        else:
            if (platform[row][col]==SQUARE_ROCK):
                #flush all the rocke there
                    moveRockSouth(platform, row-1, col, train_of_rock)
                    train_of_rock.clear();
            else:  
                if (platform[row][col]==ROUNDED_ROCK):
                    #remember his index
                    train_of_rock.append(row)

    # stampa_matrice(platform)

        #    moving west
    for row in range(0,len(platform)):
        for col in range(0, len(platform[row])):
            if (col == (len(platform[row])-1)):
                    moveRockEast(platform, row, col, train_of_rock)
                    train_of_rock.clear()
            else:
                if (platform[row][col]==SQUARE_ROCK):
                    #flush all the rocke there
                        moveRockEast(platform, row, col-1, train_of_rock)
                        train_of_rock.clear();
                else:  
                    if (platform[row][col]==ROUNDED_ROCK):
                        #remember his index
                        train_of_rock.append(col)

    # stampa_matrice(platform)


def main():
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)
    print(testo)

    platform = testo.strip().split('\n')  # Dividi le matrici usando le linee vuote come separatore
    platform = [list(row) for row in platform]  # Convert strings to lists
    platform_originale = testo.strip().split('\n')
    platform_originale = [list(row) for row in platform_originale] 

    platformCache = dict({})

    repeation = 0
    for time in range(1,1000000001):

        # print(f'{time+1}')
        cicle(platform)
        cachedP = platformCache.get(tuple(tuple(sub) for sub in platform))
        if (cachedP is not None):
            print(f'YUPPPYYYYYY --> the indx {time} has repetead the index {cachedP}')
            repeation = (1000000000 - cachedP) % (time - cachedP)
            break
            # stampa_matrice(platform)
            
        else:
            platformCache[tuple(tuple(sub) for sub in platform)]=time
        
    for time in range(0,repeation):
        cicle(platform)



    stampa_matrice(platform)

    tot = 0
    for row in range(0, len(platform)):
        for col in range(0, len(platform[row])):
            if (platform[row][col]==ROUNDED_ROCK):
                tot += len(platform)-row

    print(f'LOAD: {tot}')

if __name__ == "__main__":
   main()
