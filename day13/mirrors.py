import sys

 
print("FileName: ", sys.argv[1])


def leggi_file(nome_file):
    with open(nome_file, 'r') as file:
        contenuto = file.read()
    return contenuto


def stampa_matrice(matrice):
    for riga in matrice:                    
        print(''.join(riga))


def isFullReflection(matrice, row):
    #it is a full reflection is the mirror reflect it till the end
    found=True
    for indexRow in range(0, len(matrice)//2):
        indexleft = row - indexRow
        indexRight = row+1+indexRow
        if indexleft < 0:
            break;
        if indexRight >= len(matrice):
            break;
        found &= (matrice[indexleft] == matrice[indexRight])

    return found

def findReflection(matrice):
    for row in range(len(matrice)-1):
        if (matrice[row] == matrice[row+1]):
            found = isFullReflection(matrice,row)
            if (found):
                return row

    return -1;

def main():
   
    nome_file = sys.argv[1]  # Sostituisci con il nome del tuo file
    testo = leggi_file(nome_file)

    righe = testo.strip().split('\n\n')  # Dividi le matrici usando le linee vuote come separatore
    
    Total = 0;

    for indexRighe in range(0, len(righe), 1):
        # For each pattern it search for horizontal mirrorin and vertical mirroring. 
        # instead to write 2 differnt algoritm, I'm goint to transpond the pattern a reapply the same algoritm. 

        horizontal = [list(riga) for riga in righe[indexRighe].split('\n')]
        
        print(" Pattern:")
        stampa_matrice(horizontal)
        tempTot = 0
        hRefl = findReflection(horizontal)
        if hRefl >= 0:
            tempTot += 100*(hRefl+1);
        else:
            vertical = list(zip(*horizontal))
            print(" Pattern 'transponded':")
            stampa_matrice(vertical)
            vRefl = findReflection(vertical)
            if vRefl >= 0:
                tempTot += vRefl+1

        print(f" Reflection temp TOT: {tempTot} - TOT: {Total}")

        Total += tempTot
    
    print("Super Tot: ", Total)

if __name__ == "__main__":
    main()
