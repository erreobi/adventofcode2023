import sys

 
print("FileName: ", sys.argv[1])


def leggi_file(nome_file):
    with open(nome_file, 'r') as file:
        contenuto = file.read()
    return contenuto


def stampa_matrice(matrice):
    for riga in matrice:                    
        print(''.join(riga))


def isFullReflection(matrice, row, usedSmudge=False):
    #it is a full reflection is the mirror reflect it till the end
    found=True
    usedInternalSmudge=False
    for indexRow in range(1, len(matrice)):
        indexleft = row - indexRow
        indexRight = row+1+indexRow
        if indexleft < 0:
            break;
        if indexRight >= len(matrice):
            break;
    
        diff = countDifferences(matrice[indexleft],matrice[indexRight])
        if (usedInternalSmudge or usedSmudge):
            found &= (diff == 0) 
            # and (usedInternalSmudge or usedSmudge)
        else:
            found &= (diff == 0 or diff ==1) 
            # and (usedInternalSmudge or usedSmudge)
            if diff == 1:
                usedInternalSmudge=True
        
        # if (matrice[indexleft] != matrice[indexRight]):
        #     if usedSmudge == False and usedInternalSmudge == False:
        #         diff = countDifferences(matrice[indexleft],matrice[indexRight])
        #         if (diff == 1):
        #             print(f'Found a smudge in the row {indexleft} and {indexRight}')
        #             print(matrice[indexleft])
        #             print(matrice[indexRight])
        #             usedInternalSmudge = True
        #             found &= True
        #     else:
        #         found &= False           
        # else:      
        #     found &= (matrice[indexleft] == matrice[indexRight])

    return found and (usedInternalSmudge or usedSmudge)

def findReflection(matrice):

    for row in range(len(matrice)-1):
        diff = countDifferences(matrice[row],matrice[row+1])

        if (diff == 1 or diff == 0):
            found = isFullReflection(matrice,row, diff==1)
            if (found):
                return row
        # else:
        #     diff = countDifferences(matrice[row],matrice[row+1])
        #     if (diff == 1):
        #         print(f'Found a smudge in the row {row} and {row+1}')
        #         print(matrice[row])
        #         print(matrice[row+1])
        #         found = isFullReflection(matrice,row, True)
        #         if (found):
        #             return row

    return -1;

def countDifferences(vectorA, vectorB):
    result = 0;
    
    for index in range ( min ( len(vectorA), len(vectorB))):
        if (vectorA[index] != vectorB[index]):
            result += 1

    if (result == 1):
        print('FOUND!!!')

    return result;


def correctSmudge(matrice):
    resultMatrix = matrice.copy()
    for row in range(len(matrice)-1):
        for indexRowSmudge in range(row+1, len(matrice)):
            diff = countDifferences(matrice[row],matrice[indexRowSmudge])
            if (diff == 1):
                for smudgeRow in range(indexRowSmudge, len(matrice)):
                    for index, (first, second) in enumerate(zip(matrice[row], matrice[smudgeRow])):
                        if first != second:
                            print (f'Corrected the pattern at index [{row},{index}] with the value {matrice[smudgeRow][index]} at the iindex[{smudgeRow},{index}]')
                            resultMatrix[row][index]=matrice[smudgeRow][index]
                            return resultMatrix
    
    return resultMatrix
                    


def main():
   
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)

    righe = testo.strip().split('\n\n')  # Dividi le matrici usando le linee vuote come separatore
    
    Total = 0;

    for indexRighe in range(0, len(righe), 1):
        # For each pattern it search for horizontal mirrorin and vertical mirroring. 
        # instead to write 2 differnt algoritm, I'm goint to transpond the pattern a reapply the same algoritm. 

        pattern  = [list(riga) for riga in righe[indexRighe].split('\n')]
        print("------------")
        print(" Pattern:")
        stampa_matrice(pattern)

        horizontal = pattern.copy()
        print("AFTER HORIZONTAL SMUDGE:")
        # horizontal = correctSmudge(horizontal)
        stampa_matrice(horizontal)

        tempTot = 0
        hRefl = findReflection(horizontal)
        if hRefl >= 0:
            tempTot += 100*(hRefl+1);
        else:
            vertical = [list(ele) for ele in list(zip(*pattern))]
            print("AFTER VERTICAL SMUDGE:")
            # vertical = correctSmudge(vertical)
            stampa_matrice(vertical)

            vRefl = findReflection(vertical)
            if vRefl >= 0:
                tempTot += vRefl+1

        print(f" Reflection temp TOT: {tempTot} - TOT: {Total}")

        Total += tempTot
    
    print("Super Tot: ", Total)

if __name__ == "__main__":
    main()
